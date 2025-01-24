#include <iostream>

#include "BearLibTerminal.h"

#include "world/AreaManager.h"

#include "core/Components.h"
#include "core/Components.h"

#include "../systems/Movements.cpp"
#include "../systems/Rendering.cpp"


Game::Game()
  : world(), system_manager(world), area_manager(world)
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
  auto e = world.entity();
  e.set(Position{2, 2});
  e.set(PositionGoal{10, 22});
  e.set(Image{'@',  0xFFFF0000});
  
  Area& area = *area_manager.get_area("sandbox");

  system_manager.add_system<PathfindingSystem>(area);
  system_manager.add_system<MovementSystem>(area);
  system_manager.add_system<RenderingSystem>();

  bool running = true;
  while (running) {
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
  terminal_clear();
  terminal_layer(10);
  
  world.progress();

  Render();
}
