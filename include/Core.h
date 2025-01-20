#pragma once
#include "Terrain.h"
#include <flecs.h>

class Game {
public:
	Game();
	~Game();
	void Run();
private:
	flecs::world world;
	AreaManager area_manager; 
	void Update();
	void Render();
};

