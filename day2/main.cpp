//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include "Utils.hpp"

void forward(int *pos, int *depth, int aim, int i)
{
    *pos += i;
    *depth += aim * i;
}

void down(int *depth, int i)
{

    *depth += i;
}

void up(int *depth, int i)
{
    *depth -= i;
}

int part1(const std::vector<std::string> &vals)
{
    int pos = 0;
    int depth = 0;
    int dummy = 0;

    for (auto &i: vals)
    {
        int value = std::stoi(i.substr(i.find(' '), std::string::npos));

        if (i.rfind("forward", 0) == 0)
            forward(&pos, &dummy, 0, value);
        else if (i.rfind("down", 0) == 0)
            down(&depth, value);
        else if (i.rfind("up") == 0)
            up(&depth, value);
    }
    return depth * pos;
}

int part2(const std::vector<std::string> &vals)
{
    int pos = 0;
    int depth = 0;
    int aim = 0;

    for (auto &i: vals)
    {
        int value = std::stoi(i.substr(i.find(' '), std::string::npos));

        if (i.rfind("forward", 0) == 0)
            forward(&pos, &depth, aim, value);
        else if (i.rfind("down", 0) == 0)
            down(&aim, value);
        else if (i.rfind("up") == 0)
            up(&aim, value);
    }
    return depth * pos;
}

int main()
{
    auto input = Utils::readFile("day2");
    std::cout << "part1: " << part1(input) << std::endl;
    std::cout << "part2: " << part2(input) << std::endl;
}