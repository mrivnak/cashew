/*!
 * @file lexer.hpp
 */
#pragma once

#include <string>
#include <vector>

/*!
 * @namespace cashew::parser
 * @brief The Cashew parser namespace
 */
namespace cashew::parser
{
/*!
 * @enum TokenType
 * @brief Types of tokens
 */
enum TokenType
{
    // Containers
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,

    // Arithmetic operators
    TOKEN_MINUS,
    TOKEN_PLUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_MOD,

    // Comparison operators
    TOKEN_NOT_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,

    // Logical operators
    TOKEN_NOT,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_BIT_AND,
    TOKEN_BIT_OR,

    // Assignment operators
    TOKEN_ASSIGNMENT,

    // Literals
    TOKEN_IDENTIFIER,
    TOKEN_STRING_LITERAL,
    TOKEN_INTEGER_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_TYPE_IDENTIFIER,

    // Keywords
    TOKEN_ELSE,
    TOKEN_FALSE,
    TOKEN_FOR,
    TOKEN_IF,
    TOKEN_LET,
    TOKEN_MATCH,
    TOKEN_MUT,
    TOKEN_TRUE,
    TOKEN_WHILE,

    // Misc syntax
    TOKEN_COMMENT,
    TOKEN_COMMA,
    TOKEN_COLON_COLON,
    TOKEN_DOT,

    // Language features
    TOKEN_ENUM,
    TOKEN_FUNCTION,
    TOKEN_STRUCT,
    TOKEN_IMPORT,
    TOKEN_NAMESPACE,
    TOKEN_ERROR_PROPAGATION,

    // Other
    TOKEN_NEWLINE,
    TOKEN_END_OF_FILE,
    TOKEN_UNKNOWN,
};

/*!
 * @struct Token
 * @brief Token structure
 * @var Token::type The type of token
 * @var Token::value The value of the token, if applicable
 */
struct Token
{
    TokenType type;
    std::string value;
};

/*!
 * @fn std::vector<Token> tokenize(std::istream &input)
 * @brief Split an input stream into tokens
 * @param input Input stream
 * @return Vector of tokens
 */
std::vector<Token> tokenize(std::istream &input);
} // namespace cashew::parser