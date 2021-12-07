//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <algorithm>
#include "Utils.hpp"

struct data_s
{
    int x1;
    int y1;
    int x2;
    int y2;
};
using data = struct data_s;

void diagonal_draw(std::vector<std::vector<int>> &buffer, data s)
{
    if (s.x2 - s.x1 > 0 && s.y2 - s.y1 > 0)
    {
        for (int i = s.y1, j = s.x1; i < s.y2 + 1 && j < s.x2 + 1; ++i, ++j)
            buffer[i][j] += 1;
    } else
    {
        if (s.x1 - s.x2 > 0 && s.y1 - s.y2 > 0)
            for (int i = s.y2, j = s.x2; i < s.y1 + 1 && j < s.x1 + 1; ++i, ++j)
                buffer[i][j] += 1;
        else if (s.x1 - s.x2 > 0)
        {
            for (int i = s.y1, j = s.x1; i < s.y2 + 1 && j > s.x2 - 1; ++i, --j)
                buffer[i][j] += 1;
        }
        else if (s.y1 - s.y2 > 0)
            for (int i = s.y1, j = s.x1; i > s.y2 - 1 && j < s.x2 + 1; --i, ++j)
                buffer[i][j] += 1;
    }

}

void vertical_draw(std::vector<std::vector<int>> &buffer, data s)
{
    for (int i = s.y1; i < s.y2 + 1; ++i)
        buffer[i][s.x1] += 1;
}

void horizontal_draw(std::vector<std::vector<int>> &buffer, data s)
{
    for (int i = s.x1; i < s.x2 + 1; ++i)
        buffer[s.y1][i] += 1;
}

int part1(const std::vector<data> &vals, int max)
{
    std::vector<std::vector<int>> buffer(max + 1, std::vector<int>(max + 1));
    for (auto &val: vals)
    {
        int startX, startY, endX, endY;
        int vertical = val.x1 - val.x2;
        int horizontal = val.y1 - val.y2;

        if (vertical > 0 || horizontal > 0)
        {
            startX = val.x2;
            startY = val.y2;
            endX = val.x1;
            endY = val.y1;
        } else if (vertical < 0 || horizontal < 0)
        {
            startX = val.x1;
            startY = val.y1;
            endX = val.x2;
            endY = val.y2;
        } else
            continue;
        if (!vertical)
            vertical_draw(buffer, {startX, startY, endX, endY});
        else if (!horizontal)
            horizontal_draw(buffer, {startX, startY, endX, endY});
    }

    int count = 0;
    for (auto &line: buffer)
        for (auto &value: line)
            if (value > 1)
                ++count;
    return count;
}

int part2(const std::vector<data> &vals, int max)
{
    std::vector<std::vector<int>> buffer(max + 1, std::vector<int>(max + 1));
    for (auto &val: vals)
    {
        int startX, startY, endX, endY;
        int vertical = val.x1 - val.x2;
        int horizontal = val.y1 - val.y2;

        if (vertical > 0 || horizontal > 0)
        {
            startX = val.x2;
            startY = val.y2;
            endX = val.x1;
            endY = val.y1;
        } else if (vertical < 0 || horizontal < 0)
        {
            startX = val.x1;
            startY = val.y1;
            endX = val.x2;
            endY = val.y2;
        } else
            continue;
        if (std::abs(vertical) > 0 && std::abs(vertical) == std::abs(horizontal))
            diagonal_draw(buffer, {startX, startY, endX, endY});
        else if (!vertical)
            vertical_draw(buffer, {startX, startY, endX, endY});
        else
            horizontal_draw(buffer, {startX, startY, endX, endY});
    }

    int count = 0;
    for (auto &line: buffer)
        for (auto &value: line)
            if (value > 1)
                ++count;
    return count;
}

int main()
{
    auto input = Utils::readFile("day5");
    std::vector<data> parsedInput(input.size());
    int max = 0;
    for (int i = 0; i < input.size(); ++i)
    {
        parsedInput[i].x1 = std::stoi(input[i]);
        auto pos = input[i].find(",");
        auto pos2 = input[i].find(" ");
        parsedInput[i].y1 = std::stoi(input[i].substr(pos + 1, pos2));
        input[i].erase(0, input[i].find("> ") + 2);
        pos = input[i].find(",");
        parsedInput[i].x2 = std::stoi(input[i].substr(0, pos));
        parsedInput[i].y2 = std::stoi(input[i].substr(pos + 1, std::string::npos));
        int tmp = std::max({parsedInput[i].x1, parsedInput[i].x2, parsedInput[i].y1, parsedInput[i].y2});
        if (tmp > max)
            max = tmp;
    }

    std::cout << "part1: " << part1(parsedInput, max) << std::endl;
    std::cout << "part2: " << part2(parsedInput, max) << std::endl;
}