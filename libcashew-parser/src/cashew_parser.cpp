#include "cashew_parser.hpp"

#include <istream>
#include <sstream>

#include <iostream>

namespace cashew::parser
{
std::vector<Token> tokenize(std::stringstream &input)
{
    std::vector<Token> tokens;
    std::stringstream token;


    char character;
    char previous_character = '\0';
    bool in_comment = false;
    while (input.get(character))
    {
        if (in_comment)
        {
            if (character == '\n')
            {
                in_comment = false;
                tokens.push_back(Token{"\n"});
            }
            continue;
        }
        else {
            if (character == '/' && previous_character == '/')
            {
                in_comment = true;
                token.str("");
                token.clear();
                continue;
            }
        }
        // standard token delimiters
        if (character == ' ' || character == '\n')
        {
            tokens.push_back(Token{token.str()});
            token.str("");
            token.clear();
            if (character == '\n')
                tokens.push_back(Token{"\n"});
            continue;
        }
        token << character;
        previous_character = character;
    }
    if (tokens.back().value != "\n")
    {
        tokens.push_back(Token{token.str()});
    }

    return tokens;
}
} // namespace cashew::parser
