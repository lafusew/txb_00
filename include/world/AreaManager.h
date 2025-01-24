#pragma once

#include "world/Area.h"
#include <memory>

class AreaManager {
private:
	std::unordered_map<std::string, std::unique_ptr<Area>> areas;
	flecs::world& ecs_world;
public:
	AreaManager(flecs::world& world);
	Area* create_area(const std::string& name);
	Area* get_area(const std::string& name);
	void register_area_systems();
};
