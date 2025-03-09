#include <iostream>

#include "utils/AStar.h"
#include "core/Components.h"
#include "core/Game.h"
#include "world/Area.h"

class PathfindingSystem: public GameSystem {
private:
  flecs::system pathfind_system_;
  Area& area_;

public:
  PathfindingSystem(Area& area) : area_(area) {}

  void initialize(flecs::world& world) override {
    pathfind_system_ = world.system<PositionGoal, const Position>("Pathfinding")
      .each([this](flecs::entity e, PositionGoal& goal, const Position& current) {
        if(e.has<Path>()) return;

        auto path = AStar::findPath(area_,
          {current.x, current.y},
          {goal.x, goal.y}
        );

        e.set(Path(path));
      });
  }

  void cleanup(flecs::world& world) override {
    pathfind_system_.destruct();
  }
};

class MovementSystem: public GameSystem {
private:
  flecs::system movement_system_;
  Area& area_;

public:
  MovementSystem(Area& area) : area_(area) {}

  void initialize(flecs::world& world) override {
    movement_system_ = world.system<Path, Position, PositionGoal>("MoveAlongPath")
    .each([this](flecs::entity e, Path& path, Position& pos, PositionGoal& g) {
        if (path.empty()) {
            e.remove<Path>();
            if (pos.x == g.x && pos.y == g.y) {
              e.remove<PositionGoal>();
            }
            return;
        }

        int goal_x = path.front().first;
        int goal_y = path.front().second;
        
        // Check if the goal is reachable
        // Note: This is a simple check, in a real game you would need to
        // implement more advanced pathfinding
        if (area_.is_blocked(goal_x, goal_y)) {
            // Path is blocked, clear it
            e.remove<Path>();
            return;
        }

        // Update position to the next waypoint
        pos.x = path.front().first;
        pos.y = path.front().second;

        // Remove the consumed waypoint
        // Note: This operation has O(n) complexity
        path.erase(path.begin());

        std::cout << "moved to " << pos.x << ", " << pos.y << "\n";
    });
  }

  void cleanup(flecs::world& world) override {
    movement_system_.destruct();
  }
};
