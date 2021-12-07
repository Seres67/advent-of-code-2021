//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <bitset>
#include "Utils.hpp"

int mostCommonBitAtPos(int pos, const std::vector<std::string> &vals)
{
    int ones = 0;
    int zeros = 0;
    for (auto &j: vals)
    {
        if (j[pos] == '1')
            ++ones;
        else if (j[pos] == '0')
            ++zeros;
    }
    return ones >= zeros ? '1' : '0';
}

unsigned long part1(const std::vector<std::string> &vals)
{
    std::string gamma;
    std::string epsilon;
    for (int i = 0; i < vals[0].size(); ++i)
    {
        int ones = 0;
        int zeros = 0;
        for (auto &j: vals)
        {
            if (j[i] == '1')
                ++ones;
            else if (j[i] == '0')
                ++zeros;
        }
        gamma.push_back(ones > zeros ? '1' : '0');
    }
    epsilon = gamma;
    for (auto &c: epsilon)
    {
        if (c == '1')
            c = '0';
        else
            c = '1';
    }
    return std::stoi(gamma, nullptr, 2) * std::stoi(epsilon, nullptr, 2);
}

int part2(const std::vector<std::string> &vals)
{

    std::vector<std::string> oxygen_values;
    std::vector<std::string> co2_values;
    int common = mostCommonBitAtPos(0, vals);
    for (auto &val: vals)
    {
        if (val[0] == common)
            oxygen_values.emplace_back(val);
        else
            co2_values.emplace_back(val);
    }
    for (int j = 1; j < vals[0].size(); ++j)
    {
        common = mostCommonBitAtPos(j, oxygen_values);
        int common1 = mostCommonBitAtPos(j, co2_values);
        for (auto i = oxygen_values.begin(); i != oxygen_values.end();)
        {
            if (oxygen_values.size() == 1)
                break;
            if ((*i)[j] != common)
                i = oxygen_values.erase(i);
            else
                ++i;
        }
        for (auto i = co2_values.begin(); i != co2_values.end();)
        {
            if (co2_values.size() == 1)
                break;
            if ((*i)[j] == common1)
                i = co2_values.erase(i);
            else
                ++i;
        }
        if (oxygen_values.size() == 1 && co2_values.size() == 1)
            break;
    }
    return std::stoi(oxygen_values[0], nullptr, 2) * std::stoi(co2_values[0], nullptr, 2);

}

int main()
{
    auto input = Utils::readFile("day3");
    std::cout << "part1: " << part1(input) << std::endl;
    std::cout << "part2: " << part2(input) << std::endl;
}