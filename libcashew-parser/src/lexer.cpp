#include <format>
#include <regex>
#include <sstream>

#include "libcashew_parser/exceptions.hpp"
#include "libcashew_parser/lexer.hpp"

const std::regex IDENTIFIER_REGEX = std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
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
        return Token{TOKEN_LET};
    }
    if (token == "mut")
    {
        return Token{TOKEN_MUT};
    }
    if (token == "=")
    {
        return Token{TOKEN_ASSIGNMENT};
    }
    if (token == "+")
    {
        return Token{TOKEN_PLUS};
    }
    if (token == "-")
    {
        return Token{TOKEN_MINUS};
    }
    if (token == "*")
    {
        return Token{TOKEN_STAR};
    }
    if (token == "/")
    {
        return Token{TOKEN_SLASH};
    }
    if (token == "%")
    {
        return Token{TOKEN_MOD};
    }
    if (token == "(")
    {
        return Token{TOKEN_LEFT_PAREN};
    }
    if (token == ")")
    {
        return Token{TOKEN_RIGHT_PAREN};
    }
    if (isdigit(token.front()) || token.front() == '-')
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
    char isMath = false;
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
        case '/':
            if (prevCharacter == '/')
            {
                token.str("");
                inComment = true;
            }
            else
            {
                // add the previous token
                if (!token.str().empty())
                {
                    tokens.push_back(resolveToken(token.str()));
                    token.str("");
                }

                // add the token, mark as math for handling unary operators
                token << character;
                isMath = true;
            }
            break;
        case ' ':
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
        case '+':
        case '-':
        case '*':
        case '%':
            if (!token.str().empty())
            {
                tokens.push_back(resolveToken(token.str()));
                token.str("");
            }
            token << character;
            isMath = true;
            break;
        case '(':
        case ')':
            if (!token.str().empty())
            {
                tokens.push_back(resolveToken(token.str()));
                token.str("");
            }
            tokens.push_back(resolveToken(std::string(1, character)));
            break;
        default:
            if (isMath)
            {
                if (!token.str().empty())
                {
                    tokens.push_back(resolveToken(token.str()));
                    token.str("");
                }
                isMath = false;
            }
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
