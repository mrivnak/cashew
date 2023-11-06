#include "catch2/catch_test_macros.hpp"
#include "libcashew/lexer.hpp"
#include "util.hpp"

using namespace cashew::parser;

TEST_CASE("tokenize_invalid (missing_closing_quote.nut)", "[token][invalid]")
{
    auto input = readFileToStream("../tests/examples/parser/invalid/missing_closing_quote.nut");

    REQUIRE_THROWS_AS(tokenize(input), InvalidTokenException);
}