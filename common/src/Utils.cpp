//
// Created by Laurent on 12/7/2021.
//

#include <fstream>
#include "Utils.hpp"

std::vector<std::string> Utils::readFile(const std::string &day)
{
    std::vector<std::string> lines;
    std::ifstream file("../../" + day + "/input");
    std::string line;
    while (std::getline(file, line))
        lines.push_back(line);
    return lines;
}