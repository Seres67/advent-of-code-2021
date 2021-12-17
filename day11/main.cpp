//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "Utils.hpp"

void step(std::vector<std::vector<int>> &input)
{
    for (auto &i: input)
    {
        std::transform(i.begin(), i.end(), i.begin(), [](int a)
        {
            return ++a;
        });
    }

}

void flash(std::vector<std::vector<int>> &input, int i, int j)
{
    if (input[i][j] == 11)
        return;
    input[i][j] = 11;
    for (int i2 = i - 1; i2 <= i + 1; ++i2)
    {
        if (i2 < 0 || i2 > input.size() - 1)
            continue;
        for (int j2 = j - 1; j2 <= j + 1; ++j2)
        {
            if (j2 < 0 || j2 > input[i2].size() - 1 || (i2 == i && j2 == j))
                continue;
            if (input[i2][j2] <= 9 && ++input[i2][j2] > 9)
                flash(input, i2, j2);
        }
    }
}

int part1(std::vector<std::vector<int>> &input)
{
    int count = 0;
    for (int k = 0; k < 100; ++k)
    {
        step(input);
        for (int i = 0; i < input.size(); ++i)
            for (int j = 0; j < input[i].size(); ++j)
                if (input[i][j] > 9)
                    flash(input, i, j);
        for (auto &i: input)
            for (auto &j: i)
                if (j > 10)
                {
                    ++count;
                    j = 0;
                }
    }
    return count;
}

long long part2(const std::vector<std::vector<int>> &input)
{
    return 0;
}

int main()
{
    auto input = Utils::readFile("day11");
    std::vector<std::vector<int>> vals;

    for (int i = 0; i < input.size(); ++i)
    {
        vals.emplace_back(input[i].size());
        for (int j = 0; j < input[i].size(); ++j)
            vals[i][j] = input[i][j] - '0';
    }

    std::cout << "part1: " << part1(vals) << std::endl;
    std::cout << "part2: " << part2(vals) << std::endl;
}