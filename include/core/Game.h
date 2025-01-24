#pragma once

#include "world/AreaManager.h"
#include "systems/Systems.h"
#include <flecs.h>

class Game {
public:
  Game();
  ~Game();
  void Run();

private:
  flecs::world world;
  AreaManager area_manager;
  SystemManager system_manager;

  void Update();
  void Render();
};

