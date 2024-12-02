#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>

std::string firstPart(const std::vector<int> &left_list, const std::vector<int> &right_list)
{
    int total_distance{0};
    for (size_t i = 0; i < left_list.size(); i++)
    {
        total_distance += std::abs(left_list[i] - right_list[i]);
    }

    return std::to_string(total_distance);
}

int countNumber(const std::vector<int> &list, int target)
{
    int count{0};
    for (const auto &number : list)
    {
        if (target == number)
            count++;
    }

    return count;
}

std::string secondPart(const std::vector<int> &left_list, const std::vector<int> &right_list)
{

    int similarity_score{0};
    for (const auto &number : left_list)
    {
        similarity_score += number * countNumber(right_list, number);
    }

    return std::to_string(similarity_score);
}

int main()
{
    std::vector<int> left_list{};
    std::vector<int> right_list{};

    std::ifstream file(".\\inputs\\Day1.txt");
    std::string line;
    while (getline(file, line))
    {
        left_list.push_back(std::stoi(line.substr(0, 5)));
        right_list.push_back(std::stoi(line.substr(8, 13)));
    }

    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    std::cout << firstPart(left_list, right_list) << std::endl;
    std::cout << secondPart(left_list, right_list) << std::endl;
    return 0;
}