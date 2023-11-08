#include <regex>
#include <sstream>

#include "libcashew_parser/exceptions.hpp"
#include "libcashew_parser/lexer.hpp"

const std::regex IDENTIFIER_REGEX = std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
const std::regex INTEGER_LITERAL_REGEX = std::regex("^[0-9_]+(?:u8|u16|u32|u64|i8|i16|i32|i64)?$");
const std::regex FLOAT_LITERAL_REGEX = std::regex("^[0-9_]+\\.[0-9_]*(?:f32|f64)?$");

namespace cashew::parser
{
Token resolveToken(std::string token)
{
    if (token.starts_with("\"") && token.ends_with("\""))
    {
        return Token{TokenType::TOKEN_STRING_LITERAL, token};
    }
    else if (token == "let")
    {
        return Token{TokenType::TOKEN_LET};
    }
    else if (token == "mut")
    {
        return Token{TokenType::TOKEN_MUT};
    }
    else if (token == "=")
    {
        return Token{TokenType::TOKEN_ASSIGNMENT};
    }
    else if (token == "+")
    {
        return Token{TokenType::TOKEN_PLUS};
    }
    else if (token == "-")
    {
        return Token{TokenType::TOKEN_MINUS};
    }
    else if (token == "*")
    {
        return Token{TokenType::TOKEN_STAR};
    }
    else if (token == "/")
    {
        return Token{TokenType::TOKEN_SLASH};
    }
    else if (token == "%")
    {
        return Token{TokenType::TOKEN_MOD};
    }
    else
    {
        if (isdigit(token.front()))
        {
            if (std::regex_match(token, INTEGER_LITERAL_REGEX))
            {
                return Token{TokenType::TOKEN_INTEGER_LITERAL, token};
            }
            if (std::regex_match(token, FLOAT_LITERAL_REGEX))
            {
                return Token{TokenType::TOKEN_FLOAT_LITERAL, token};
            }
            throw InvalidTokenException("Invalid numeric literal");
        }

        if (!std::regex_match(token, IDENTIFIER_REGEX))
        {
            throw InvalidTokenException("Invalid identifier");
        }
        return Token{TokenType::TOKEN_IDENTIFIER, token};
    }
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
                tokens.emplace_back(TokenType::TOKEN_NEWLINE);
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
            tokens.emplace_back(TokenType::TOKEN_NEWLINE);

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
                inComment = true;
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
        default:
            token << character;
            break;
        }

        prevCharacter = character;
    }

    tokens.emplace_back(TokenType::TOKEN_END_OF_FILE);

    return tokens;
}
} // namespace cashew::parser
