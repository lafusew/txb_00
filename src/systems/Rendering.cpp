#include "BearLibTerminal.h"

#include "core/Components.h"
#include "core/Game.h"

class RenderingSystem : public GameSystem {
private:
  flecs::system render_system_;
public:
  RenderingSystem() {}

  void initialize(flecs::world& world) override {
    render_system_ = world.system<const Position, const Image>("EntityRender")
      .kind(flecs::PostUpdate)
      .each([this](flecs::entity e, const Position& pos, const Image& img) {
        terminal_color(img.color);
        terminal_put(pos.x, pos.y, img.character);
      });
  };

  void cleanup(flecs::world& world) override {
    render_system_.destruct();
  }
};
