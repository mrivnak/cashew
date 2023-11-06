#include "util.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::stringstream readFileToStream(const std::string &path)
{
    std::ifstream input(path.c_str());
    if (!input.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
    }

    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    return buffer;
}
