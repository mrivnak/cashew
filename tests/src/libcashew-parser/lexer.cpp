#include <catch2/catch_test_macros.hpp>
#include <libcashew_parser/lexer.hpp>

#include "util.hpp"

using namespace cashew::parser;

TEST_CASE("tokenize (assignment_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/assignment_1.nut");

    std::vector<Token> expected = {// let a = 5
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (assignment_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/assignment_2.nut");

    std::vector<Token> expected = {// let a = 5
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_NEWLINE},
                                   // let mut b = 6
                                   {TOKEN_LET},
                                   {TOKEN_MUT},
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "6"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (comment_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/comment_1.nut");

    std::vector<Token> expected = {// // this is a comment
                                   {TOKEN_NEWLINE},
                                   // let a = 5
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (comment_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/comment_2.nut");

    std::vector<Token> expected = {// let a = 5 // this is also a comment
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_NEWLINE},
                                   // let b = 6
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "6"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (string_literal_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/string_literal_1.nut");

    std::vector<Token> expected = {// let a = "hello"
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_STRING_LITERAL, "\"hello\""},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (string_literal_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/string_literal_2.nut");

    std::vector<Token> expected = {// let a = "hello world"
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_STRING_LITERAL, "\"hello world\""},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (int_literal_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_1.nut");

    std::vector<Token> expected = {// let a = 5
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (int_literal_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_2.nut");

    std::vector<Token> expected = {// let a = 5_000
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_INTEGER_LITERAL, "5_000"},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (int_literal_3.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_3.nut");

    std::vector<Token> expected = {// let a = 5_u8
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_u8"},
                                   {TOKEN_NEWLINE},
                                   // let b = 5_u16
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_u16"},
                                   {TOKEN_NEWLINE},
                                   // let c = 5_u32
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "c"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_u32"},
                                   {TOKEN_NEWLINE},
                                   // let d = 5_u64
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "d"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_u64"},
                                   {TOKEN_NEWLINE},
                                   // let e = 5_usize
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "e"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_usize"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (int_literal_4.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/int_literal_4.nut");

    std::vector<Token> expected = {// let a = 5_i8
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_i8"},
                                   {TOKEN_NEWLINE},
                                   // let b = 5_i16
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_i16"},
                                   {TOKEN_NEWLINE},
                                   // let c = 5_i32
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "c"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_i32"},
                                   {TOKEN_NEWLINE},
                                   // let d = 5_i64
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "d"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_i64"},
                                   {TOKEN_NEWLINE},
                                   // let e = 5_isize
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "e"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5_isize"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (float_literal_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_1.nut");

    std::vector<Token> expected = {// let a = 5.0
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_FLOAT_LITERAL, "5.0"},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (float_literal_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_2.nut");

    std::vector<Token> expected = {// let a = 5_000.000_1
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_FLOAT_LITERAL, "5_000.000_1"},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (float_literal_3.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_3.nut");

    std::vector<Token> expected = {// let a = 5.
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT}, {TOKEN_FLOAT_LITERAL, "5."},
                                   {TOKEN_NEWLINE},    {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (float_literal_4.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/float_literal_4.nut");

    std::vector<Token> expected = {// let a = 5.0_f32
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_FLOAT_LITERAL, "5.0_f32"},
                                   {TOKEN_NEWLINE},
                                   // let b = 5.0_f64
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_FLOAT_LITERAL, "5.0_f64"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (arithmetic_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/arithmetic_1.nut");

    std::vector<Token> expected = {// let a = 5 + 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_PLUS},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let b = 5 - 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_MINUS},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let c = 5 * 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "c"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_STAR},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let d = 5 / 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "d"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_SLASH},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let e = 5 % 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "e"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_MOD},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (arithmetic_2.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/arithmetic_2.nut");

    std::vector<Token> expected = {// let a = 5 + 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_PLUS},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let b = 5 - 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_MINUS},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let c = 5 * 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "c"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_STAR},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let d = 5 / 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "d"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_SLASH},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // let e = 5 % 2
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "e"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_MOD},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (arithmetic_3.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/arithmetic_3.nut");

    std::vector<Token> expected = {// let a = (5 + 2) * 3
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_LEFT_PAREN},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_PLUS},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_RIGHT_PAREN},
                                   {TOKEN_STAR},
                                   {TOKEN_INTEGER_LITERAL, "3"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (arithmetic_4.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/arithmetic_4.nut");

    std::vector<Token> expected = {// let a = ((5 + 2) * 3) - 4
                                   {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},      {TOKEN_ASSIGNMENT},
                                   {TOKEN_LEFT_PAREN}, {TOKEN_LEFT_PAREN},           {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_PLUS},       {TOKEN_INTEGER_LITERAL, "2"}, {TOKEN_RIGHT_PAREN},
                                   {TOKEN_STAR},       {TOKEN_INTEGER_LITERAL, "3"}, {TOKEN_RIGHT_PAREN},
                                   {TOKEN_MINUS},      {TOKEN_INTEGER_LITERAL, "4"}, {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (no_trailing_newline.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/no_trailing_newline.nut");

    std::vector<Token> expected = {// let a = 5
                                   {TOKEN_LET},
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_ASSIGNMENT},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (explicit_type.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/explicit_type.nut");

    std::vector<Token> expected = {
        // let a: i32 = 1
        {TOKEN_LET},        {TOKEN_IDENTIFIER, "a"},      {TOKEN_COLON},   {TOKEN_IDENTIFIER, "i32"},
        {TOKEN_ASSIGNMENT}, {TOKEN_INTEGER_LITERAL, "1"}, {TOKEN_NEWLINE}, {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (arithmetic_assignment_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/arithmetic_assignment_1.nut");

    std::vector<Token> expected = {// a += 1
                                   {TOKEN_IDENTIFIER, "a"},
                                   {TOKEN_PLUS_EQUAL},
                                   {TOKEN_INTEGER_LITERAL, "1"},
                                   {TOKEN_NEWLINE},
                                   // b -= 2
                                   {TOKEN_IDENTIFIER, "b"},
                                   {TOKEN_MINUS_EQUAL},
                                   {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_NEWLINE},
                                   // c *= 3
                                   {TOKEN_IDENTIFIER, "c"},
                                   {TOKEN_STAR_EQUAL},
                                   {TOKEN_INTEGER_LITERAL, "3"},
                                   {TOKEN_NEWLINE},
                                   // d /= 4
                                   {TOKEN_IDENTIFIER, "d"},
                                   {TOKEN_SLASH_EQUAL},
                                   {TOKEN_INTEGER_LITERAL, "4"},
                                   {TOKEN_NEWLINE},
                                   // e %= 5
                                   {TOKEN_IDENTIFIER, "e"},
                                   {TOKEN_MOD_EQUAL},
                                   {TOKEN_INTEGER_LITERAL, "5"},
                                   {TOKEN_NEWLINE},
                                   {TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize (if_else_1.nut)", "[token]")
{
    auto input = readFileToStream("../tests/examples/parser/if_else_1.nut");

    std::vector<Token> expected = {// if x > 2 then true else false
                                   {TOKEN_IF},      {TOKEN_IDENTIFIER, "x"},
                                   {TOKEN_GREATER}, {TOKEN_INTEGER_LITERAL, "2"},
                                   {TOKEN_THEN},    {TOKEN_TRUE},
                                   {TOKEN_ELSE},    {TOKEN_FALSE},
                                   {TOKEN_NEWLINE}, {TOKEN_END_OF_FILE}};

    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        if (!expected[i].value.empty())
            REQUIRE(tokens[i].value == expected[i].value);
    }
}
