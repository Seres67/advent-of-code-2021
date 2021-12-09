//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <vector>
#include <numeric>
#include "Utils.hpp"

int part1(const std::vector<std::vector<int>> &input)
{
    std::vector<int> vals;
    bool up, down, left, right;
    for (int i = 0; i < input.size(); ++i)
        for (int j = 0; j < input[i].size(); ++j)
        {
            int current = input[i][j];
            left = j < 1 || current < input[i][j - 1];
            right = j > input[i].size() - 2 || current < input[i][j + 1];
            up = i < 1 || current < input[i - 1][j];
            down = i > input.size() - 2 || current < input[i + 1][j];
            if (up && down && left && right)
                vals.emplace_back(current);
        }
    return std::accumulate(vals.begin(), vals.end(), 0) + vals.size();
}

int part2(std::vector<std::vector<int>> &input)
{
    return 0;
}

int main()
{
    auto input = Utils::readFile("day9");
    std::vector<std::vector<int>> parsedInput(input.size(), std::vector<int>(input[0].size()));

    for (int i = 0; i < input.size(); ++i)
        for (int j = 0; j < input[i].size(); ++j)
            parsedInput[i][j] = input[i][j] - '0';

    std::cout << "part1: " << part1(parsedInput) << std::endl;
    std::cout << "part2: " << part2(parsedInput) << std::endl;
}