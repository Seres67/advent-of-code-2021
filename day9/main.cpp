//
// Created by Laurent on 12/7/2021.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <execution>
#include "Utils.hpp"

struct pos_s
{
public:
    int m_i;
    int m_j;

    pos_s(int i, int j) : m_i(i), m_j(j)
    {

    }

    bool operator==(const struct pos_s &p) const
    {
        return m_i == p.m_i && m_j == p.m_j;
    }
};

struct hash
{
    std::size_t operator()(const struct pos_s &p) const
    {
        return p.m_i * p.m_j;
    }
};

using pos = struct pos_s;

int lowest(const std::vector<std::vector<int>> &input, pos p)
{
    bool up, down, left, right;

    up = p.m_i - 1 < 0 || input[p.m_i - 1][p.m_j] > input[p.m_i][p.m_j];
    down = p.m_i + 1 > input.size() - 1 || input[p.m_i + 1][p.m_j] > input[p.m_i][p.m_j];
    left = p.m_j - 1 < 0 || input[p.m_i][p.m_j - 1] > input[p.m_i][p.m_j];
    right = p.m_j + 1 > input[p.m_i].size() - 1 || input[p.m_i][p.m_j + 1] > input[p.m_i][p.m_j];
    return up && down && left && right;
}

std::vector<pos> get_next(pos p)
{
    return {{p.m_i - 1, p.m_j},
            {p.m_i + 1, p.m_j},
            {p.m_i,     p.m_j - 1},
            {p.m_i,     p.m_j + 1}};
}

int part1(const std::vector<std::vector<int>> &input)
{
    std::vector<int> vals;
    for (int i = 0; i < input.size(); ++i)
        for (int j = 0; j < input[i].size(); ++j)
            if (lowest(input, {i, j}))
                vals.emplace_back(input[i][j]);
    return static_cast<int>(std::accumulate(vals.begin(), vals.end(), 0) + vals.size());
}

int part2(std::vector<std::vector<int>> &input)
{
    std::vector<pos> positions;
    for (int i = 0; i < input.size(); ++i)
        for (int j = 0; j < input[i].size(); ++j)
            if (lowest(input, {i, j}))
                positions.emplace_back(i, j);
    std::vector<int> sizes;
    for (const auto &p: positions)
    {
        std::queue<pos> queue;
        std::unordered_set<pos, hash> visited;
        int count = 0;

        queue.push(p);
        visited.insert(p);
        while (!queue.empty())
        {
            std::vector<pos> next = get_next(queue.front());
            queue.pop();
            for (const auto &n: next)
            {
                if (n.m_i >= 0 && n.m_j >= 0 && n.m_i < input.size() && n.m_j < input[0].size() && input[n.m_i][n.m_j] != 9 && visited.find(n) == visited.end())
                {
                    count++;
                    queue.push(n);
                    visited.insert(n);
                }
            }
        }
        sizes.emplace_back(count + 1);
    }
    std::sort(std::execution::par,std::begin(sizes), std::end(sizes));
    return sizes[sizes.size() - 1] * sizes[sizes.size() - 2] * sizes[sizes.size() - 3];
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