#include "AStar.h"
#include "BearLibTerminal.h"
#include <Terrain.h>
#include <Core.h>
#include <Components.h>
#include <iostream>

Game::Game()
  : world(), area_manager(world)
{
  world.observer<Path>()
    .event(flecs::OnSet)
    .each([](flecs::entity e, Path& p) {
      std::cout << "Path set: ";
      for (const auto pos : p) {
        std::cout << "{" << pos.first << ", " << pos.second << "} ";
      }
      std::cout << "\n";
    });

  area_manager.create_area("sandbox");
  terminal_open();
  terminal_set("window.size=240x67;");
};

Game::~Game()
{
  terminal_close();
};

void Game::Run() {
  // TODO:
  // 
 // Remove this example and add a propper system manager

  auto e = world.entity();

  e.set(Position{2, 2});
  e.set(PositionGoal{10, 22});

  Area& area = *area_manager.get_area("sandbox");

  flecs::system sys = world.system<PositionGoal, const Position>("PathFind")
    .each([&area](flecs::entity e, PositionGoal& g, const Position &p) {
      if (e.has<Path>()) {
        return;
      }
      auto path = AStar::findPath(area, {p.x, p.y}, {g.x, g.y});

      e.set(Path(path));
    });

  world.system<Path, Position, PositionGoal>("ProcessPath")
    .each([](flecs::entity e, Path& path, Position& pos, PositionGoal& g) {
        if (path.empty()) {
            e.remove<Path>();
            if (pos.x == g.x && pos.y == g.y) {
              e.remove<PositionGoal>();
            }
            return;
        }
        // Update position to the next waypoint
        pos.x = path.front().first;
        pos.y = path.front().second;
        // Remove the consumed waypoint
        // Note: This operation has O(n) complexity
        path.erase(path.begin());

        std::cout << "moved to " << pos.x << ", " << pos.y << "\n";
        terminal_layer(10);
        terminal_color("red");
        terminal_put(pos.x, pos.y, '#');
    });
  // TODO: 

  bool running = true;
  while (running) {
    Render();
    Update();

    if (terminal_read() == TK_CLOSE) {
      running = false;
    } 
  }
};

void Game::Render() {
  auto curr_area = area_manager.get_area("sandbox");
  if (curr_area) {
    terminal_layer(0);
    terminal_color("white");
    curr_area->for_each_tile([this](int x, int y, Tile tile) {
        terminal_put(x, y, tile.id); 
    });
  }
  
  terminal_refresh();
}

void Game::Update() {
  world.progress();
}
