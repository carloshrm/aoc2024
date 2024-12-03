#pragma once
bool activateDampener(bool is_dampened, const std::vector<int> &levels, size_t i);

bool checkLevelSafety(const std::vector<int> &levels, bool engineer_amnesia, bool was_dampened);

std::string firstPart(const std::vector<std::vector<int>> &reports);

std::string secondPart(const std::vector<std::vector<int>> &reports);
