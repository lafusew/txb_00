#include "raylib.h"

#include "core/Components.h"
#include "core/Game.h"
#include "world/Area.h"

class RenderingSystem : public GameSystem {
private:
  flecs::system render_system_;

  Area& area_;

  int screen_width = 640;
  int screen_height = 480;
  int target_fps = 60;

  int tile_size = 32;

  Camera2D camera = { 0 };
public:
  RenderingSystem(Area& area) : area_(area) {
    camera.zoom = 1.0f;
  }

  void initialize(flecs::world& world) override {
    InitWindow(screen_width, screen_height, "txb");
    SetTargetFPS(target_fps);

    world.system("BeginDrawing")
      .kind(flecs::OnStore)
      .run([this](flecs::iter& it){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        area_.for_each_tile([this](int x, int y, Tile tile) {
          DrawRectangle(
            x * tile_size,
            y * tile_size, tile_size,
            tile_size,
            tile.walkable ? GREEN : RED
          );
        });
    });

    render_system_ = world.system<const Position, const ScreenImage>("EntityRender")
      .kind(flecs::OnStore)
      .each([this](flecs::entity e, const Position& pos, const ScreenImage& img) {
        DrawCircle(
          pos.x * tile_size + tile_size / 2,
          pos.y * tile_size + tile_size / 2,
          int(tile_size / 2),
          BLUE
        );
      });

    world.system("EndDrawing")
      .kind(flecs::OnStore)
      .run([](flecs::iter& it){
        DrawFPS(10, 10);

        EndMode2D();
        EndDrawing();
    });
  }

  void cleanup(flecs::world& world) override {
    render_system_.destruct();
  } 
};
