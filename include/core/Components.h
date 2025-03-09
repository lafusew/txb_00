#pragma once

#include <vector>
#include "raylib.h"

struct ScreenImage {
	int character;
	Color color;
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

struct Health
{
	int value;
	int max_value;
};


