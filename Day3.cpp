#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

constexpr std::string_view ENABLING_TOKEN = "do()";
constexpr std::string_view DISABLING_TOKEN = "don't()";

std::string cleanDisabledInstructions(const std::string &input)
{
    std::string valid_input{};

    size_t current_pos{0};
    size_t enabling_position{0};
    while ((current_pos = input.find(DISABLING_TOKEN, current_pos)) != std::string::npos)
    {
        valid_input += input.substr(enabling_position, current_pos - enabling_position);

        enabling_position = input.find(ENABLING_TOKEN, current_pos);
        if (enabling_position == std::string::npos)
            break;

        current_pos = enabling_position + ENABLING_TOKEN.size();
    }

    if (enabling_position != std::string::npos)
        valid_input += input.substr(enabling_position);

    return valid_input;
}

long runInstructions(const std::string &input)
{
    const std::regex pattern(R"(mul\((\d+),(\d+)\))");

    std::sregex_iterator current_instruction(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    long sum{0};
    while (current_instruction != end)
    {
        std::smatch match = *current_instruction;
        sum += std::stoi(match.str(1)) * std::stoi(match.str(2));
        ++current_instruction;
    }

    return sum;
}

int main()
{
    std::string input{};

    std::ifstream file(".\\inputs\\Day3.txt");
    std::string line;
    while (getline(file, line))
        input += line;

    std::cout << runInstructions(cleanDisabledInstructions(input)) << std::endl;
}