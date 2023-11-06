#include "libcashew/lexer.hpp"
#include "catch2/catch_test_macros.hpp"
#include "util.hpp"

using namespace cashew::parser;

TEST_CASE("tokenize (assignment_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/assignment_1.nut");

    std::vector<Token> expected = {// let a = 5
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_INTEGER_LITERAL, "5"},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (assignment_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/assignment_2.nut");

    std::vector<Token> expected = {// let a = 5
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let mut b = 6
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_MUT},
                                   {TokenType::TOKEN_IDENTIFIER, "b"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "6"},
                                   {TokenType::TOKEN_NEWLINE},
                                   {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (comment_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/comment_1.nut");

    std::vector<Token> expected = {// // this is a comment
                                   {TokenType::TOKEN_NEWLINE},
                                   // let a = 5
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5"},
                                   {TokenType::TOKEN_NEWLINE},
                                   {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (comment_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/comment_2.nut");

    std::vector<Token> expected = {// let a = 5 // this is also a comment
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let b = 6
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "b"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "6"},
                                   {TokenType::TOKEN_NEWLINE},
                                   {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}
