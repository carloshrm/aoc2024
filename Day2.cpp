#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Day2.h"

bool activateDampener(bool was_dampened, const std::vector<int> &levels, size_t problem_pos)
{
    if (was_dampened)
        return false;

    std::vector<int> dampened_levels{levels};
    dampened_levels.erase(dampened_levels.begin() + problem_pos);

    return checkLevelSafety(dampened_levels, false, true);
}

bool checkLevelSafety(const std::vector<int> &levels, bool engineer_amnesia = true, bool was_dampened = false)
{
    bool increasing_levels{false};
    for (size_t i = 1; i < levels.size(); i++)
    {
        if (levels[i] == levels[i - 1] || std::abs(levels[i] - levels[i - 1]) > 3)
        {
            if (engineer_amnesia)
                return false;

            return activateDampener(was_dampened, levels, i) || activateDampener(was_dampened, levels, i - 1);
        }
        else
        {
            bool level_has_increased{levels[i] > levels[i - 1]};

            if (i == 1)
            {
                increasing_levels = level_has_increased;
                continue;
            }

            if (level_has_increased != increasing_levels)
            {
                if (engineer_amnesia)
                    return false;

                return activateDampener(was_dampened, levels, i) || activateDampener(was_dampened, levels, i - 1) || activateDampener(was_dampened, levels, i - 2);
            }
        }
    }

    return true;
}

std::string firstPart(const std::vector<std::vector<int>> &reports)
{
    int total_safe_levels{0};
    for (const auto &report : reports)
    {
        if (checkLevelSafety(report))
            total_safe_levels++;
    }
    return std::to_string(total_safe_levels);
}

std::string secondPart(const std::vector<std::vector<int>> &reports)
{
    int total_safe_levels{0};
    for (const auto &report : reports)
    {
        if (checkLevelSafety(report, false))
            total_safe_levels++;
    }
    return std::to_string(total_safe_levels);
}

int main()
{
    std::vector<std::vector<int>> reports{};

    std::ifstream file(".\\inputs\\Day2.txt");
    std::string line;
    while (getline(file, line))
    {
        reports.push_back({});
        size_t prev = 0;
        size_t next = 0;

        bool keep_looking{true};
        while (keep_looking)
        {
            next = line.find(' ', prev);
            if (next == std::string::npos)
                keep_looking = false;

            reports.back().push_back(std::stoi(line.substr(prev, next - prev)));
            prev = next + 1;
        }
    }

    std::cout << firstPart(reports) << std::endl;
    std::cout << secondPart(reports) << std::endl;
}