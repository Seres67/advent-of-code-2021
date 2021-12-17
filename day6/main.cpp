//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <array>
#include <numeric>
#include <execution>
#include "Utils.hpp"

int part1(const std::vector<int> &vals)
{
    std::array<int, 9> states{0};
    int tmp;

    for (auto &val: vals)
        ++states[val];
    for (int i = 0; i < 80; ++i)
    {
        tmp = states[0];
        std::rotate(std::execution::par, states.begin(), states.begin() + 1, states.end());
        states[6] += tmp;
    }
    return std::accumulate(states.begin(), states.end(), 0);
}

long long part2(const std::vector<int> &vals)
{
    std::array<long long, 9> states{0};
    long long tmp;

    for (auto &val: vals)
        ++states[val];
    for (int i = 0; i < 256; ++i)
    {
        tmp = states[0];
        std::rotate(std::execution::par, states.begin(), states.begin() + 1, states.end());
        states[6] += tmp;
    }
    return std::accumulate(states.begin(), states.end(), (long long) 0);
}

int main()
{
    auto input = Utils::readFile("day6");
    std::vector<int> parsedInput(1 + input[0].size() / 2, 0);
    parsedInput[0] = std::stoi(input[0].substr(0, 1));
    for (int i = 1; true; ++i)
    {
        if (input[0].size() >= 2)
            input[0].erase(0, 2);
        else
            break;
        parsedInput[i] = std::stoi(input[0].substr(0, 1));
    }

    std::cout << "part1: " << part1(parsedInput) << std::endl;
    std::cout << "part2: " << part2(parsedInput) << std::endl;
}