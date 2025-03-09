# Game
The main purpose of this project is to learn ECS with `flecs`, I also have to learn C++ and low level programming as I never wrote any.  

## Engine

Using raylib as a base library for the game engine. The goal is to make a sepecific 2d engine that would suit my needs. 

I aim to make an engine suited for isometric games, with camera and occlusion handling.

## Build (Game isn't portable for now)
In order to build the project create a `/build` subdirectory and open a terminal inside.  
Then run:
```bash
cmake ..
```  
Then run:
```bash
cmake --build .
```  

> Currently only available for Linux64, I will add later other binaries to build for every major PC platforms.  

## Goals
My mains goals for this project is to explore ECS architecture and what it allows. I want to write code that is easy to read and modular. I'm willing to trade some performances for a better readability and modularity.  

