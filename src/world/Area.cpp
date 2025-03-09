#include <world/Area.h>

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

bool Area::is_blocked(int x, int y) const {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return true;
  }

  return !tiles[y][x].walkable;
}

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

