#include <iostream>

#include "raylib.h"
#include "world/AreaManager.h"

#include "core/Components.h"
#include "core/Components.h"

#include "../systems/Movements.cpp"
#include "../systems/Rendering.cpp"

Game::Game()
  : world(), system_manager(world), area_manager(world)
{
  auto area = *area_manager.create_area("sandbox");

  system_manager.add_system<PathfindingSystem>(area);
  system_manager.add_system<MovementSystem>(area);
  system_manager.add_system<RenderingSystem>(area);

  world.observer<Path>()
    .event(flecs::OnSet)
    .each([](flecs::entity e, Path& p) {
      std::cout << "Path set: ";
      for (const auto pos : p) {
        std::cout << "{" << pos.first << ", " << pos.second << "} ";
      }
      std::cout << "\n";
    });

  auto e = world.entity();
  e.set(Position{2, 2});
  e.set(PositionGoal{10, 22});
  e.set(ScreenImage{'@',  {255, 255, 255, 255}});
};

Game::~Game()
{
  CloseWindow();
};

void Game::Run() {
  while (!WindowShouldClose()) {
    Update();
  } 
};

void Game::Render() {
  
}

void Game::Update() {
  world.progress();
}
