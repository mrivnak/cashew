#pragma once

#include <string>
#include <vector>

namespace cashew::parser {
    struct Token {
        std::string value;
    };

    std::vector<Token> tokenize(std::stringstream& input);
}