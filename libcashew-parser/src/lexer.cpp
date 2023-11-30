#include <format>
#include <regex>
#include <set>
#include <sstream>
#include <string>

#include "libcashew_parser/exceptions.hpp"
#include "libcashew_parser/lexer.hpp"

const std::regex IDENTIFIER_REGEX = std::regex("^[a-zA-Z_][a-zA-Z0-9_<>]*$");
const std::regex INTEGER_LITERAL_REGEX = std::regex("^(?:[0-9]{1,2}|[0-9][0-9_]+[0-9])(?:_[ui](?:8|16|32|64|size))?$");
const std::regex FLOAT_LITERAL_REGEX =
    std::regex("^(?:[0-9]{1,2}|[0-9][0-9_]+[0-9])\\.(?:[0-9]{0,2}|[0-9][0-9_]+[0-9])(?:_f(?:32|64))?$");

namespace cashew::parser
{
Token resolveToken(std::string token)
{
    if (token.starts_with("\"") && token.ends_with("\""))
    {
        return Token{TOKEN_STRING_LITERAL, token};
    }
    if (token == "let")
    {
        return Token{TOKEN_LET, token};
    }
    if (token == "mut")
    {
        return Token{TOKEN_MUT, token};
    }
    if (token == "if")
    {
        return Token{TOKEN_IF, token};
    }
    if (token == "then")
    {
        return Token{TOKEN_THEN, token};
    }
    if (token == "else")
    {
        return Token{TOKEN_ELSE, token};
    }
    if (token == "true")
    {
        return Token{TOKEN_TRUE, token};
    }
    if (token == "false")
    {
        return Token{TOKEN_FALSE, token};
    }
    if (token == "=")
    {
        return Token{TOKEN_ASSIGNMENT, token};
    }
    if (token == "+")
    {
        return Token{TOKEN_PLUS, token};
    }
    if (token == "-")
    {
        return Token{TOKEN_MINUS, token};
    }
    if (token == "*")
    {
        return Token{TOKEN_STAR, token};
    }
    if (token == "/")
    {
        return Token{TOKEN_SLASH, token};
    }
    if (token == "%")
    {
        return Token{TOKEN_MOD, token};
    }
    if (token == "(")
    {
        return Token{TOKEN_LEFT_PAREN, token};
    }
    if (token == ")")
    {
        return Token{TOKEN_RIGHT_PAREN, token};
    }
    if (token == "+=")
    {
        return Token{TOKEN_PLUS_EQUAL, token};
    }
    if (token == "-=")
    {
        return Token{TOKEN_MINUS_EQUAL, token};
    }
    if (token == "*=")
    {
        return Token{TOKEN_STAR_EQUAL, token};
    }
    if (token == "/=")
    {
        return Token{TOKEN_SLASH_EQUAL, token};
    }
    if (token == "%=")
    {
        return Token{TOKEN_MOD_EQUAL, token};
    }
    if (token == "==")
    {
        return Token{TOKEN_EQUAL_EQUAL, token};
    }
    if (token == "!=")
    {
        return Token{TOKEN_NOT_EQUAL, token};
    }
    if (token == ">")
    {
        return Token{TOKEN_GREATER, token};
    }
    if (token == ">=")
    {
        return Token{TOKEN_GREATER_EQUAL, token};
    }
    if (token == "<")
    {
        return Token{TOKEN_LESS, token};
    }
    if (token == "<=")
    {
        return Token{TOKEN_LESS_EQUAL, token};
    }
    if (token == "!")
    {
        return Token{TOKEN_NOT, token};
    }
    if (isdigit(token.front()))
    {
        if (std::regex_match(token, INTEGER_LITERAL_REGEX))
        {
            return Token{TOKEN_INTEGER_LITERAL, token};
        }
        if (std::regex_match(token, FLOAT_LITERAL_REGEX))
        {
            return Token{TOKEN_FLOAT_LITERAL, token};
        }
        throw InvalidTokenException("Invalid numeric literal");
    }

    if (!std::regex_match(token, IDENTIFIER_REGEX))
    {
        throw InvalidTokenException(std::format("Invalid identifier : {}", token));
    }
    return Token{TOKEN_IDENTIFIER, token};
}

std::vector<Token> tokenize(std::istream &input)
{
    std::vector<Token> tokens;
    std::stringstream token;

    bool inString = false;
    bool inComment = false;

    char character;
    char prevCharacter = '\0';
    while (input.get(character))
    {
        if (inComment)
        {
            // end comment on newline
            if (character == '\n')
            {
                inComment = false;
                tokens.emplace_back(TOKEN_NEWLINE);
            }
            continue; // ignore all other characters in comment
        }
        switch (character)
        {
        case '\n':
            if (inString) // error if newline before closing quote
            {
                throw InvalidTokenException("Missing closing quote.");
            }

            // add the token
            if (!token.str().empty())
            {
                tokens.push_back(resolveToken(token.str()));
                token.str("");
            }

            // also add a newline token
            tokens.emplace_back(TOKEN_NEWLINE);

            break;
        case '"':
            // ignore escaped quotes
            if (prevCharacter != '\\')
            {
                inString = !inString;
            }

            // add the quote to the token
            token << character;

            // if string is closed, add the token
            if (!inString)
            {
                tokens.push_back(resolveToken(token.str()));
                token.str("");
            }

            break;

        case ' ':
            [[fallthrough]];
        case '\t':
            if (inString) // include whitespace in string literals
            {
                token << character;
            }
            else // otherwise, add the token
            {
                if (!token.str().empty())
                {
                    tokens.push_back(resolveToken(token.str()));
                    token.str("");
                }
            }
            break;
        case '/':
            if (prevCharacter == '/')
            {
                // Remove previous slash token
                tokens.pop_back();

                token.str("");
                inComment = true;
                break;
            }
            [[fallthrough]];
        case '+':
            [[fallthrough]];
        case '-':
            [[fallthrough]];
        case '*':
            [[fallthrough]];
        case '%':
            [[fallthrough]];
        case '(':
            [[fallthrough]];
        case ')':
            if (!token.str().empty())
            {
                tokens.push_back(resolveToken(token.str()));
                token.str("");
            }
            tokens.push_back(resolveToken(std::string(1, character)));
            break;
        case ':':
            if (prevCharacter == ':')
            {
                // Single colon has already been added, remove it
                tokens.pop_back();

                tokens.emplace_back(TOKEN_DOUBLE_COLON);
            }
            else
            {
                // Add the previous token
                tokens.push_back(resolveToken(token.str()));
                token.str("");

                // Add the colon token
                tokens.emplace_back(TOKEN_COLON);
            }
            break;
        case '=':
            if (std::set{'+', '-', '*', '/', '%', '='}.contains(prevCharacter))
            {
                // Remove previous token
                tokens.pop_back();

                // Add new
                tokens.push_back(resolveToken(std::string(1, prevCharacter) + character));
                token.str(""); // TODO: maybe not needed
            }
            else
            {
                // Add the token
                tokens.emplace_back(TOKEN_ASSIGNMENT);
                token.str("");
            }
            break;
        default:
            token << character;
            break;
        }

        prevCharacter = character;
    }

    // Handle no trailing newline
    if (!token.str().empty())
    {
        tokens.push_back(resolveToken(token.str()));
        token.str("");
    }

    tokens.emplace_back(TOKEN_END_OF_FILE);

    return tokens;
}
} // namespace cashew::parser
