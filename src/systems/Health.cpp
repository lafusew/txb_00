#include "core/Components.h"
#include "core/Game.h"

class HealthSystem : public GameSystem {
private:
  flecs:: system health_system_;
public:
  HealthSystem() {}

  void initialize(flecs::world& world) override {
    health_system_ = world.system<Health>("Health")
      .each([](flecs::entity e, Health& h) {
        if (h.value <= 0) {
          e.destruct();
        }
      });
  }

  void cleanup(flecs::world& world) override {
    health_system_.destruct();
  }
};
