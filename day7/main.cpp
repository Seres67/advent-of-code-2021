//
// Created by Laurent on 12/7/2021.
//

#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <execution>
#include "Utils.hpp"

int part1(std::vector<int> &vals)
{
    std::sort(std::execution::par, vals.begin(), vals.end());
    double moveTo = (vals[(vals.size() - 1) / 2] + vals[vals.size() / 2]) / 2.0;
    int count = 0;

    for (auto &val: vals)
        count += (int) std::abs(moveTo - val);
    return count;
}

long long part2(std::vector<int> &vals)
{
    std::sort(std::execution::par,vals.begin(), vals.end());
    double moveTo = std::accumulate(vals.begin(), vals.end(), (int) 0) / double(vals.size());
    int count = 0;

    for (auto &val: vals)
    {
        int tmp = std::abs(static_cast<int>(moveTo) - val);
        count += tmp * (tmp + 1) / 2;
    }
    return count;
}

int main()
{
    auto input = Utils::readFile("day7");
    std::vector<int> parsedInput(std::count(input[0].begin(), input[0].end(), ',') + 1, 0);
    std::string::size_type pos;
    int i;

    for (i = 0, pos = input[0].find(','); pos != std::string::npos; pos = input[0].find(','), ++i)
    {
        parsedInput[i] = std::stoi(input[0].substr(0, pos));
        input[0].erase(0, pos + 1);
    }
    parsedInput[i] = std::stoi(input[0]);

    std::cout << "part1: " << part1(parsedInput) << std::endl;
    std::cout << "part2: " << part2(parsedInput) << std::endl;
}