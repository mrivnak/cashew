#include <catch2/catch_test_macros.hpp>
#include <libcashew_parser/exceptions.hpp>
#include <libcashew_parser/lexer.hpp>

#include "util.hpp"

using namespace cashew::parser;

TEST_CASE("tokenize_invalid (missing_closing_quote.nut)", "[token][invalid]")
{
    auto input = readFileToStream("../tests/examples/parser/invalid/missing_closing_quote.nut");

    REQUIRE_THROWS_AS(tokenize(input), InvalidTokenException);
}

TEST_CASE("tokenize_invalid (invalid_int_literal_1.nut)", "[token][invalid]")
{
    auto input = readFileToStream("../tests/examples/parser/invalid/invalid_int_literal_1.nut");

    REQUIRE_THROWS_AS(tokenize(input), InvalidTokenException);
}

TEST_CASE("tokenize_invalid (invalid_int_literal_2.nut)", "[token][invalid]")
{
    // This will tokenize since "_5" is a valid identifier, but it will fail in the parser
    auto input = readFileToStream("../tests/examples/parser/invalid/invalid_int_literal_2.nut");
    std::vector<Token> expected = {// let a = _5
                                   {TokenType::TOKEN_LET},        {TokenType::TOKEN_IDENTIFIER, "a"},
                                   {TokenType::TOKEN_ASSIGNMENT}, {TokenType::TOKEN_IDENTIFIER, "_5"},
                                   {TokenType::TOKEN_NEWLINE},    {TokenType::TOKEN_END_OF_FILE}};
    auto tokens = tokenize(input);

    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        REQUIRE(tokens[i].type == expected[i].type);
        REQUIRE(tokens[i].value == expected[i].value);
    }
}

TEST_CASE("tokenize_invalid (invalid_float_literal_1.nut)", "[token][invalid]")
{
    auto input = readFileToStream("../tests/examples/parser/invalid/invalid_float_literal_1.nut");

    REQUIRE_THROWS_AS(tokenize(input), InvalidTokenException);
}

TEST_CASE("tokenize_invalid (invalid_float_literal_2.nut)", "[token][invalid]")
{
    auto input = readFileToStream("../tests/examples/parser/invalid/invalid_float_literal_3.nut");

    REQUIRE_THROWS_AS(tokenize(input), InvalidTokenException);
}

TEST_CASE("tokenize_invalid (invalid_float_literal_3.nut)", "[token][invalid]")
{
    auto input = readFileToStream("../tests/examples/parser/invalid/invalid_float_literal_3.nut");

    REQUIRE_THROWS_AS(tokenize(input), InvalidTokenException);
}