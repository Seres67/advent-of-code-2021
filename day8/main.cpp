//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Utils.hpp"

int part1(const std::vector<std::vector<std::string>> &signals, const std::vector<std::vector<std::string>> &output)
{
    std::map<int, int> map;
    for (auto &signal: output)
        for (auto &signal2: signal)
        {
            if (signal2.size() == 2)
                ++map[1];
            else if (signal2.size() == 3)
                ++map[7];
            else if (signal2.size() == 4)
                ++map[4];
            else if (signal2.size() == 7)
                ++map[8];
        }
    return map[1] + map[4] + map[7] + map[8];
}

void findSegment(std::string &output, const std::string &toRemove, const std::string &toRemove2, std::string in)
{
    size_t pos;

    for (char i: toRemove)
    {
        pos = in.find(i);
        if (pos != std::string::npos)
            in.erase(pos, 1);
    }
    for (char i: toRemove2)
    {
        pos = in.find(i);
        if (pos != std::string::npos)
            in.erase(pos, 1);
    }
    output = in;
}

void findSegment(std::string &output, const std::string &toRemove, std::string input)
{
    size_t pos;

    for (char i: toRemove)
    {
        pos = input.find(i);
        if (pos != std::string::npos)
            input.erase(pos, 1);
    }
    output = input;
}

void findNumber(std::string &output, const std::string &input, const std::string &toRemove, const std::string &toRemove1, int sizeAtEnd)
{
    std::string tmp = input;
    size_t pos;

    for (char i: toRemove)
    {
        pos = tmp.find(i);
        if (pos != std::string::npos)
            tmp.erase(pos, 1);
    }
    for (char i: toRemove1)
    {
        pos = tmp.find(i);
        if (pos != std::string::npos)
            tmp.erase(pos, 1);
    }
    if (tmp.size() == sizeAtEnd)
        output = input;
}

void findNumber(std::string &output, const std::string &start, const std::string &toRemove, int sizeAtEnd)
{
    std::string three = start;
    size_t pos;

    for (char i: toRemove)
    {
        pos = three.find(i);
        if (pos != std::string::npos)
            three.erase(pos, 1);
    }
    if (three.size() == sizeAtEnd)
        output = start;
}

void findNumber(std::string &output, const std::string &toRemove, std::string in)
{
    size_t pos;

    for (char i: toRemove)
    {
        pos = in.find(i);
        if (pos != std::string::npos)
            in.erase(pos, 1);
    }
    output = in;
}

void compute(int i, int &j, std::vector<std::vector<std::string>> &input, std::map<int, std::string> &numbers, std::map<int, std::string> &segments)
{
    std::string tmp = input[i][j];
    std::sort(tmp.begin(), tmp.end());
    if (tmp.size() == 2 && numbers[1].empty())
    {
        numbers[1] = tmp;
        input[i].erase(input[i].begin() + j);
        --j;
    } else if (tmp.size() == 3 && numbers[7].empty())
    {
        numbers[7] = tmp;
        input[i].erase(input[i].begin() + j);
        --j;
    } else if (tmp.size() == 4 && numbers[4].empty())
    {
        numbers[4] = tmp;
        input[i].erase(input[i].begin() + j);
        --j;
    } else if (tmp.size() == 7 && numbers[8].empty())
    {
        numbers[8] = tmp;
        input[i].erase(input[i].begin() + j);
        --j;
    }
    ++j;
}

void compute2(int i, std::vector<std::vector<std::string>> &input, std::map<int, std::string> &numbers, std::map<int, std::string> &segments)
{
    for (auto tmp: input[i])
    {
        std::sort(tmp.begin(), tmp.end());
        if (tmp.size() == 5 && !numbers[4].empty() && !numbers[7].empty())
            findNumber(numbers[2], tmp, numbers[4], numbers[7], 2);
    }
    for (auto tmp: input[i])
    {
        std::sort(tmp.begin(), tmp.end());
        if (tmp.size() == 5 && !numbers[2].empty() && std::strcmp(tmp.c_str(), numbers[2].c_str()) != 0)
            findNumber(numbers[3], tmp, numbers[2], 1);
        if (tmp.size() == 5 && !numbers[2].empty() && std::strcmp(tmp.c_str(), numbers[2].c_str()) != 0)
            findNumber(numbers[5], tmp, numbers[2], 2);
    }
}

int digitToNb(const std::map<int, std::string> &numbers, const std::string &in)
{
    for (auto &num: numbers)
        if (std::strcmp(num.second.c_str(), in.c_str()) == 0)
            return num.first;
    return 0;
}

int computeCount(const std::map<int, std::string> &numbers, std::vector<std::string> &output)
{
    std::string tmp;
    for (auto digit: output)
    {
        std::sort(digit.begin(), digit.end());
        tmp += std::to_string(digitToNb(numbers, digit));
    }
    return std::stoi(tmp);
}

int part2(std::vector<std::vector<std::string>> &signals, std::vector<std::vector<std::string>> &output)
{
    std::map<int, std::string> numbers;
    std::map<int, std::string> segments;
    int count = 0;

    for (int i = 0; i < signals.size(); ++i)
    {
        numbers.clear();
        segments.clear();
        for (int j = 0; j < signals[i].size();)
            compute(i, j, signals, numbers, segments);
        compute2(i, signals, numbers, segments);
        if (!numbers[7].empty())
            findSegment(segments[0], numbers[1], numbers[7]);
        if (!numbers[2].empty() && !numbers[8].empty())
            findSegment(segments[1], numbers[1], numbers[2], numbers[8]);
        if (!segments[1].empty() && !numbers[4].empty())
            findSegment(segments[3], numbers[1], segments[1], numbers[4]);
        if (!numbers[2].empty() && !numbers[1].empty())
            findSegment(segments[5], numbers[2], numbers[1]);
        if (!segments[5].empty() && !numbers[1].empty())
            findSegment(segments[2], segments[5], numbers[1]);
        if (!segments[2].empty() && !numbers[8].empty())
            findNumber(numbers[6], segments[2], numbers[8]);
        if (!segments[3].empty() && !numbers[8].empty())
            findNumber(numbers[0], segments[3], numbers[8]);
        if (!numbers[5].empty() && !numbers[6].empty())
            findSegment(segments[4], numbers[5], numbers[6]);
        if (!segments[4].empty() && !numbers[8].empty())
            findNumber(numbers[9], segments[4], numbers[8]);
        count += computeCount(numbers, output[i]);
    }
    return count;
}

int main()
{
    auto input = Utils::readFile("day8");
    auto pos = input[0].find("|");
    std::string signals;
    std::vector<std::vector<std::string>> parsedSignals(input.size());
    std::string output;
    std::vector<std::vector<std::string>> parsedOutput(input.size());

    std::string delimiter = " ";

    size_t post = 0;
    std::string token;
    for (int i = 0; i < input.size(); ++i)
    {
        signals = input[i].substr(0, pos);
        output = input[i].substr(pos + 2, std::string::npos);
        while ((post = signals.find(delimiter)) != std::string::npos)
        {
            token = signals.substr(0, post);
            parsedSignals[i].emplace_back(token);
            signals.erase(0, post + delimiter.length());
        }

        while ((post = output.find(delimiter)) != std::string::npos)
        {
            token = output.substr(0, post);
            parsedOutput[i].emplace_back(token);
            output.erase(0, post + delimiter.length());
        }
        parsedOutput[i].emplace_back(output);
    }

    std::cout << "part1: " << part1(parsedSignals, parsedOutput) << std::endl;
    std::cout << "part2: " << part2(parsedSignals, parsedOutput) << std::endl;
}