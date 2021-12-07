//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <Utils.hpp>

int part1(const std::vector<int> &vals)
{
    int count = 0;

    for (int i = 1; i < vals.size(); ++i)
        if (vals[i] - vals[i - 1] > 0)
            ++count;
    return count;
}

int part2(const std::vector<int> &vals)
{
    int count = 0;
    int tmp;
    int tmp2;

    for (int i = 1; i < vals.size() - 2; ++i)
    {
        tmp = 0;
        tmp2 = 0;
        for (int j = 0; j < 3; j++)
            tmp += vals[i + j - 1];
        for (int j = 0; j < 3; j++)
            tmp2 += vals[i + j];
        if (tmp2 - tmp > 0)
            ++count;
    }

    return count;
}

int main()
{
    auto input = Utils::readFile("day1");
    std::vector<int> vals;
    vals.reserve(input.size());
    for (auto &str: input)
        vals.emplace_back(std::stoi(str));
    std::cout << "part1: " << part1(vals) << std::endl;
    std::cout << "part2: " << part2(vals) << std::endl;
}