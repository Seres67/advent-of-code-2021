//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <execution>
#include "Utils.hpp"

struct score_s
{
    char c;
    int n;
};

using score = struct score_s;

std::string getOpeningCharacters()
{
    return "([{<";
}

std::string getClosingCharacters()
{
    return ")]}>";
}

auto getScores()
{
    static const std::map<char, int> scores{{')', 3},
                                            {']', 57},
                                            {'}', 1197},
                                            {'>', 25137}};
    return scores;
}

auto getScoresPart2()
{
    static const std::map<char, int> scores{{')', 1},
                                            {']', 2},
                                            {'}', 3},
                                            {'>', 4}};
    return scores;
}

int part1(const std::vector<std::string> &input)
{
    std::vector<char> opening;
    std::vector<char> wrong_closing;
    int score = 0;
    std::string::size_type pos;

    for (auto &line: input)
    {
        for (const char i: line)
        {
            if (getOpeningCharacters().find(i) != std::string::npos)
                opening.emplace_back(i);
            else if ((pos = getClosingCharacters().find(i)) != std::string::npos)
            {
                char c = opening.back();
                if (c == getOpeningCharacters()[pos])
                    opening.erase(opening.end() - 1);
                else
                {
                    wrong_closing.emplace_back(i);
                    break;
                }
            }
        }
    }
    for (const char c: wrong_closing)
    {
        auto scores = getScores();
        score += scores[c];
    }
    return score;
}

long long part2(std::vector<std::string> &input)
{
    std::vector<char> opening;
    std::vector<char> closing;
    std::vector<long long> scores;
    long long score;
    bool error;

    for (auto &line: input)
    {
        closing.clear();
        opening.clear();
        score = 0;
        error = false;
        for (const char i: line)
        {
            std::string::size_type pos;
            if (getOpeningCharacters().find(i) != std::string::npos)
                opening.emplace_back(i);
            else if ((pos = getClosingCharacters().find(i)) != std::string::npos)
            {
                char c = opening.back();
                if (c == getOpeningCharacters()[pos])
                    opening.erase(opening.end() - 1);
                else
                {
                    error = true;
                    break;
                }
            }
        }
        if (error)
            continue;
        for (int i = opening.size() - 1; i >= 0; --i)
        {
            auto pos = getOpeningCharacters().find(opening[i]);
            closing.emplace_back(getClosingCharacters()[pos]);
        }
        for (const char c: closing)
        {
            auto tmp = getScoresPart2();
            score = score * 5 + tmp[c];
        }
        scores.emplace_back(score);
    }
    std::sort(std::execution::par, scores.begin(), scores.end());
    return scores[scores.size() / 2];
}

int main()
{
    auto input = Utils::readFile("day10");

    std::cout << "part1: " << part1(input) << std::endl;
    std::cout << "part2: " << part2(input) << std::endl;
}