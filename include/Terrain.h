#pragma once
#include <array>
#include <memory>
#include <string>
#include <unordered_map>

namespace flecs { struct world; }

struct Tile {
	int id;
	bool walkable;
};

class Area {
private:
	static constexpr int WIDTH = 128;
	static constexpr int HEIGHT = 56;
	std::array<std::array<Tile, WIDTH>, HEIGHT> tiles;
	std::string name;
	
	template<typename T>
	class TilePropertyStorage {
	private:
		std::unordered_map<int, T> data;
		int get_flat_index(int x, int y) const; 
	public:
		TilePropertyStorage(int w, int h);
		void set(int x, int y, T value);
		T* get(int x, int y);
		template<typename Func>
		void for_each(Func&& func);
	};

public:
	explicit Area(std::string name);
	// TilePropertyStorage<float> temperatures;
	Tile* get_tile(int x, int y);
	const Tile* get_tile(int x, int y) const;

	void generate_terrain(const std::string& pattern);

	static constexpr int get_width();
	static constexpr int get_height();
	const std::string& get_name();

	template<typename Func>
	void for_each_tile(Func&& func) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                func(x, y, tiles[y][x]);
            }
        };
    }
};

class AreaManager {
private:
	std::unordered_map<std::string, std::unique_ptr<Area>> areas;
	flecs::world& ecs_world;
public:
	AreaManager(flecs::world& world);
	Area* create_area(const std::string& name);
	Area* get_area(const std::string& name);
	void register_area_systems();
};
