#include "world/AreaManager.h"

AreaManager::AreaManager(flecs::world& world) : ecs_world(world) {}

Area* AreaManager::create_area(const std::string& name) {
  auto [it, inserted] = areas.try_emplace(
    name,
    std::make_unique<Area>(name)
  );

  if (!inserted) {
    throw std::runtime_error("Area with name '" + name + "' already exists");
  }

  return it->second.get();
}

Area* AreaManager::get_area(const std::string& name) {
  auto it = areas.find(name);
  return it != areas.end() ? it->second.get() : nullptr;
}

void AreaManager::register_area_systems() {
  // Nothing for now
}
