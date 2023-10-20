#include <cashew_parser.hpp>
#include <catch2/catch_test_macros.hpp>

#include <fstream>
#include <sstream>

#include <iostream>

TEST_CASE("tokenize (assignment_0.nut)", "[token]")
{
    std::ifstream input("../tests/libcashew-parser/examples/assignment_0.nut");
    if (!input.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
    }

    std::stringstream buffer;
    buffer << input.rdbuf();

    std::vector<std::string> expected = {"let", "a", "=", "5", "\n"};
    std::cout << "buffer: " << buffer.str() << std::endl;
    auto tokens = cashew::parser::tokenize(buffer);
    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
        REQUIRE(tokens[i].value == expected[i]);
    input.close();
}

TEST_CASE("tokenize (assignment_1.nut)", "[token]")
{
    std::ifstream input("../tests/libcashew-parser/examples/assignment_1.nut");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::vector<std::string> expected = {"let", "a", "=", "5", "\n", "let", "mut", "b", "=", "6", "\n"};
    auto tokens = cashew::parser::tokenize(buffer);
    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
        REQUIRE(tokens[i].value == expected[i]);
}

TEST_CASE("tokenize (assignment_2.nut)", "[token]")
{
    std::ifstream input("../tests/libcashew-parser/examples/assignment_2.nut");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::vector<std::string> expected = {"let", "a", "=", "5", "\n", "let", "mut", "b", "=", "6"};
    auto tokens = cashew::parser::tokenize(buffer);
    REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
        REQUIRE(tokens[i].value == expected[i]);
}

TEST_CASE("tokenize (comment_0.nut)", "[token]")
{
    std::ifstream input("../tests/libcashew-parser/examples/comment_0.nut");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::vector<std::string> expected = {"\n", "let", "a", "=", "5", "\n"};
    auto tokens = cashew::parser::tokenize(buffer);
    // REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
        REQUIRE(tokens[i].value == expected[i]);
}

TEST_CASE("tokenize (comment_1.nut)", "[token]")
{
    std::ifstream input("../tests/libcashew-parser/examples/comment_1.nut");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::vector<std::string> expected = {"let", "a", "=", "5", "\n"};
    auto tokens = cashew::parser::tokenize(buffer);
    // REQUIRE(tokens.size() == expected.size());
    for (size_t i = 0; i < tokens.size(); ++i)
        REQUIRE(tokens[i].value == expected[i]);
}
