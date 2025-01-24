#pragma once

#include "BearLibTerminal.h"
#include <vector>

struct Image {
	int character;
	color_t color;
};

struct Position
{
	int x, y;
};

struct PositionGoal
{
	int x, y;
};

using Path = std::vector<std::pair<int, int>>;

