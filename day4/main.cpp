//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <algorithm>
#include "Utils.hpp"

struct data_s
{
    int nb;
    bool checked;
};

using data = struct data_s;

bool checkWinVertical(std::vector<std::vector<data>> input, int posX, int posY)
{
    int count = 0;
    posY = posY - (posY % 5);
    if (posY < 0)
        posY = 0;
    for (int i = posY; i < posY + 5 && i < input.size(); ++i)
        if (input[i][posX].checked)
            ++count;
    return count == 5;
}

bool checkWinHorizontal(std::vector<data> input)
{
    return std::all_of(input.begin(), input.end(), [](data d)
    {
        return d.checked;
    });
}

int part1(std::vector<std::string> vals)
{
    std::vector<int> drawn_values;
    std::vector<std::vector<data>> boards(vals.size() - 2 - ((vals.size() - 2) / 6), {{0, false},
                                                                                      {0, false},
                                                                                      {0, false},
                                                                                      {0, false},
                                                                                      {0, false}});
    std::string token;
    char delimiter = ',';
    for (auto i = vals[0].find(delimiter); i != std::string::npos; i = vals[0].find(delimiter))
    {
        token = vals[0].substr(0, i);
        drawn_values.emplace_back(std::stoi(token));
        vals[0].erase(0, i + 1);
    }
    drawn_values.emplace_back(std::stoi(vals[0]));

    int offset = 2;
    delimiter = ' ';
    for (int i = 2; i < vals.size(); ++i)
    {
        if (vals[i].empty())
        {
            ++offset;
            continue;
        }
        if (vals[i][0] == ' ')
            vals[i].erase(vals[i].begin());
        for (int j = vals[i].find(delimiter), k = 0; j != std::string::npos; j = vals[i].find(delimiter), ++k)
        {
            if (vals[i][j] == ' ' && vals[i][j + 1] == ' ')
                vals[i].erase(vals[i].begin() + j + 1);
            token = vals[i].substr(0, j);
            boards[i - offset][k] = {std::stoi(token), false};
            vals[i].erase(0, j + 1);
        }
        boards[i - offset][4] = {std::stoi(vals[i]), false};
    }
    bool win = false;
    int board_n = 0;
    int win_value = 0;
    for (auto &val: drawn_values)
    {
        for (int i = 0; i < boards.size() && !win; ++i)
        {
            int j;
            for (j = 0; j < boards[i].size() && !win; ++j)
            {
                if (boards[i][j].nb == val)
                    boards[i][j].checked = true;
                if (checkWinHorizontal(boards[i]) || checkWinVertical(boards, j, i))
                {
                    win = true;
                    board_n = (i + 1) / 5;
                    win_value = val;
                }
            }

        }
        if (win)
            break;
    }
    int count = 0;
    for (int i = board_n * 5; i < (board_n * 5) + 5; ++i)
    {
        for (auto &j: boards[i])
            if (!j.checked)
                count += j.nb;
    }
    return count * win_value;
}

int part2(std::vector<std::string> vals)
{
    std::vector<int> drawn_values;
    std::vector<std::vector<data>> boards(vals.size() - 2 - ((vals.size() - 2) / 6), {{0, false},
                                                                                      {0, false},
                                                                                      {0, false},
                                                                                      {0, false},
                                                                                      {0, false}});
    std::string token;
    char delimiter = ',';
    for (auto i = vals[0].find(delimiter); i != std::string::npos; i = vals[0].find(delimiter))
    {
        token = vals[0].substr(0, i);
        drawn_values.emplace_back(std::stoi(token));
        vals[0].erase(0, i + 1);
    }
    drawn_values.emplace_back(std::stoi(vals[0]));

    int offset = 2;
    delimiter = ' ';
    for (int i = 2; i < vals.size(); ++i)
    {
        if (vals[i].empty())
        {
            ++offset;
            continue;
        }
        if (vals[i][0] == ' ')
            vals[i].erase(vals[i].begin());
        for (int j = vals[i].find(delimiter), k = 0; j != std::string::npos; j = vals[i].find(delimiter), ++k)
        {
            if (vals[i][j] == ' ' && vals[i][j + 1] == ' ')
                vals[i].erase(vals[i].begin() + j + 1);
            token = vals[i].substr(0, j);
            boards[i - offset][k] = {std::stoi(token), false};
            vals[i].erase(0, j + 1);
        }
        boards[i - offset][4] = {std::stoi(vals[i]), false};
    }
    std::vector<int> wins;
    bool stop = false;
    int board_n = 0;
    int win_value = 0;
    for (auto &val: drawn_values)
    {
        for (int i = 0; i < boards.size() && !stop; ++i)
        {
            for (auto &j: boards[i])
                if (j.nb == val)
                    j.checked = true;
            for (int j = 0; j < boards[i].size() && !stop; ++j)
            {
                if (std::none_of(wins.begin(), wins.end(), [i](int a)
                { return i / 5 == a; }))
                {
                    if (checkWinHorizontal(boards[i]) || checkWinVertical(boards, j, i))
                        wins.emplace_back(i / 5);
                    if (wins.size() >= ((boards.size()) / 5))
                    {
                        stop = true;
                        board_n = std::floor(i / 5);
                        win_value = val;
                    }
                }
            }
        }
        if (stop)
            break;
    }
    int count = 0;
    for (int i = board_n * 5; i < (board_n * 5) + 5; ++i)
    {
        for (auto &j: boards[i])
            if (!j.checked)
                count += j.nb;
    }
    return count * win_value;
}

int main()
{
    auto input = Utils::readFile("day4");
    std::cout << "part1: " << part1(input) << std::endl;
    std::cout << "part2: " << part2(input) << std::endl;
}