#pragma once

#include <utility>
#include <vector>
struct Position
{
	int x, y;
};

struct PositionGoal
{
	int x, y;
};

using Path = std::vector<std::pair<int, int>>;

