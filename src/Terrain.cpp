#include <Terrain.h>
#include <memory>
#include <stdexcept>

// Area implementation
Area::Area(std::string name) : name(std::move(name)) {
  for (auto& row : tiles) {
    for (auto& tile: row) {
      tile = Tile{'.', true};
    }
  }

  generate_terrain("maze");
}

Tile* Area::get_tile(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return nullptr;
  }
  
  return &tiles[y][x];
}

const Tile* Area::get_tile(int x, int y) const {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return nullptr;
  }
  
  return &tiles[y][x];
} 

constexpr int Area::get_height() { return HEIGHT; }
constexpr int Area::get_width() { return WIDTH; }

const std::string& Area::get_name() { return name; }

void Area::generate_terrain(const std::string& pattern = "maze") {
  if (pattern == "maze") {
    // More complex maze-like pattern
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if ((x + y) % 7 == 0) {  // Creates scattered walls
                tiles[y][x] = Tile{'#', false};
            }
        }
    }
  }
}

// Area Manager implementation 
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
