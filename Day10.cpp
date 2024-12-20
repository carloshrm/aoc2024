#include "Vector2.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

bool isInsideMap(const std::vector<std::vector<char>> &map, const Vector2 &pos)
{
    return pos.x >= 0 && pos.y >= 0 && pos.x < map.front().size() && pos.y < map.size();
};

int walkTrailhead(const std::vector<std::vector<char>> &map, const Vector2 &pos, std::vector<Vector2> &visited)
{
    // if (std::find(visited.begin(), visited.end(), pos) != visited.end())
    //     return 0;
    // else
    //     visited.push_back(std::move(pos));

    if (map[pos.y][pos.x] == '9')
        return 1;

    int score{0};
    for (auto &dir : directions)
    {
        auto next_pos{pos + dir};
        if (isInsideMap(map, next_pos) && map[next_pos.y][next_pos.x] == map[pos.y][pos.x] + 1)
            score += walkTrailhead(map, next_pos, visited);
    }

    return score;
}

int main()
{
    std::ifstream file("./inputs/Day10.txt");
    std::string line{};

    std::vector<std::vector<char>> map{};
    std::vector<Vector2> starting_points{};
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
        if (line == "")
            break;

        map.push_back({});
        for (auto &c : line)
        {
            map.back().push_back(c);
            if (c == '0')
            {
                starting_points.push_back(Vector2{(int)map.back().size() - 1, (int)map.size() - 1});
            }
        }
    }

    int total{0};
    for (auto &trailhead : starting_points)
    {
        std::vector<Vector2> visited{};
        total += walkTrailhead(map, trailhead, visited);
    }

    std::cout << total << std::endl;
}