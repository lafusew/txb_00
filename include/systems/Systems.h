#include <flecs.h>
#include <memory>
#include <typeindex>
#include <unordered_map>

class GameSystem {
public:
  virtual ~GameSystem() = default;
  virtual void initialize(flecs::world &world) = 0;
  virtual void cleanup(flecs::world &world) {};
};

class SystemManager {
private:
  std::unordered_map<std::type_index, std::unique_ptr<GameSystem>> systems_;
  flecs::world &world_;

public:
  SystemManager(flecs::world &world) : world_(world) {}

  // Add system (existing method)
  template <typename SystemType, typename... Args>
  SystemType *add_system(Args &&...args) {
    auto system = std::make_unique<SystemType>(std::forward<Args>(args)...);
    SystemType *system_ptr = system.get();

    // Store the system
    systems_[std::type_index(typeid(SystemType))] = std::move(system);

    // Initialize the system
    system_ptr->initialize(world_);

    return system_ptr;
  }

  // Remove system by type
  template <typename SystemType> bool remove_system() {
    auto it = systems_.find(std::type_index(typeid(SystemType)));
    if (it != systems_.end()) {
      // Call cleanup before removal
      it->second->cleanup(world_);
      systems_.erase(it);
      return true;
    }
    return false;
  }

  // Check if system exists
  template <typename SystemType> bool has_system() const {
    return systems_.find(std::type_index(typeid(SystemType))) != systems_.end();
  }
};
