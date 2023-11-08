#include <catch2/catch_test_macros.hpp>
#include <libcashew_parser/lexer.hpp>

#include "util.hpp"

using namespace cashew::parser;

TEST_CASE("tokenize (assignment_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/assignment_1.nut");

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
    auto input = readFileToStream("../tests/examples/parser/assignment_2.nut");

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
    auto input = readFileToStream("../tests/examples/parser/comment_1.nut");

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
    auto input = readFileToStream("../tests/examples/parser/comment_2.nut");

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

TEST_CASE("tokenize (string_literal_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/string_literal_1.nut");

    std::vector<Token> expected = {// let a = "hello"
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_STRING_LITERAL, "\"hello\""},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (string_literal_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/string_literal_2.nut");

    std::vector<Token> expected = {// let a = "hello world"
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_STRING_LITERAL, "\"hello world\""},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (int_literal_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_1.nut");

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

TEST_CASE("tokenize (int_literal_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_2.nut");

    std::vector<Token> expected = {// let a = 5_000
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_INTEGER_LITERAL, "5_000"},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (int_literal_3.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_3.nut");

    std::vector<Token> expected = {// let a = 5_u8
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_u8"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let b = 5_u16
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "b"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_u16"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let c = 5_u32
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "c"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_u32"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let d = 5_u64
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "d"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_u64"},
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

TEST_CASE("tokenize (int_literal_4.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_4.nut");

    std::vector<Token> expected = {// let a = 5_u8
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_i8"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let b = 5_u16
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "b"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_i16"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let c = 5_u32
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "c"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_i32"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let d = 5_u64
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "d"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_INTEGER_LITERAL, "5_i64"},
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

TEST_CASE("tokenize (float_literal_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_1.nut");

    std::vector<Token> expected = {// let a = 5.0
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_FLOAT_LITERAL, "5.0"},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (float_literal_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_2.nut");

    std::vector<Token> expected = {// let a = 5_000.000_1
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_FLOAT_LITERAL, "5_000.000_1"},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (float_literal_3.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_3.nut");

    std::vector<Token> expected = {// let a = 5.
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_FLOAT_LITERAL, "5."},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (float_literal_4.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_4.nut");

    std::vector<Token> expected = {// let a = 5.0_f32
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_FLOAT_LITERAL, "5.0_f32"},
                                   {TokenType::TOKEN_NEWLINE},
                                   // let b = 5.0_f64
                                   {TokenType::TOKEN_LET},
                                   {TokenType::TOKEN_IDENTIFIER, "b"},
                                   {TokenType::TOKEN_ASSIGNMENT},
                                   {TokenType::TOKEN_FLOAT_LITERAL, "5.0_f64"},
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
