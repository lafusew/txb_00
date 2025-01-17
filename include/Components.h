#pragma once
#include <string>
#include <unordered_map>

struct Position
{
	float x, y;
};

struct Inventory { 
	std::unordered_map<std::string, int> resources; 
};

struct ResourceYeld {
	std::string type;
	int amount;	
};

struct Boost {
	int amount;
};
