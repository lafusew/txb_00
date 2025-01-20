#pragma once
#include "Terrain.h"
#include <vector>
#include <cmath>

// Keep the Node struct as is since it's independent of the grid implementation
struct Node {
    int x, y;
    int gCost, hCost, fCost;
    Node* parent;
    Node(int x, int y, int g, int h, Node* p = nullptr)
        : x(x), y(y), gCost(g), hCost(h), fCost(g + h), parent(p) {}
    
    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

// New AStar class that works with any grid-like structure that provides required interface
class AStar {
public:
    static std::vector<std::pair<int, int>> findPath(
        const Area& grid,
        std::pair<int, int> start,
        std::pair<int, int> goal
    );

private:
    static int heuristic(int x1, int y1, int x2, int y2);
    
    // Helper method to check if a tile is walkable
    static bool isWalkable(const Area& grid, int x, int y) {
        if (const auto* tile = grid.get_tile(x, y)) {
            return tile->walkable;
        }
        return false;
    }
};
