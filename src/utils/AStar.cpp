#include "utils/AStar.h"
#include "world/Area.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <vector>

std::vector<std::pair<int, int>> AStar::findPath(const Area &grid,
                                                 std::pair<int, int> start,
                                                 std::pair<int, int> goal) {
  // Priority queue for efficient "get lowest cost node" operations
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;

  // Track all nodes to manage memory and avoid duplicates
  std::unordered_map<int, std::unordered_map<int, Node *>> allNodes;

  // Helper to get/create nodes - avoids duplicate code and manages node
  // creation
  auto getNode = [&](int x, int y, Node *parent = nullptr,
                     int gCost = INT_MAX) {
    if (allNodes[x][y] == nullptr) {
      allNodes[x][y] = new Node(
          x, y, gCost, heuristic(x, y, goal.first, goal.second), parent);
    }
    return allNodes[x][y];
  };

  // Initialize starting point
  Node *startNode = getNode(start.first, start.second, nullptr, 0);
  openList.push(*startNode);

  // All possible movement directions (including diagonals)
  const std::vector<std::pair<int, int>> directions = {
      {0, 1}, {1, 0},   {0, -1}, {-1, 0}, // Cardinal directions
      {1, 1}, {-1, -1}, {1, -1}, {-1, 1}  // Diagonals
  };

  // Main pathfinding loop
  while (!openList.empty()) {
    Node current = openList.top();
    openList.pop();

    // Check if we reached the goal
    if (current.x == goal.first && current.y == goal.second) {
      // Reconstruct and return the path
      std::vector<std::pair<int, int>> path;
      for (Node *n = &current; n != nullptr; n = n->parent) {
        path.emplace_back(n->x, n->y);
      }
      // Clean up allocated nodes
      for (auto &row : allNodes) {
        for (auto &node : row.second) {
          delete node.second;
        }
      }
      std::reverse(path.begin(), path.end());
      return path;
    }

    // Check all neighboring tiles
    for (auto [dx, dy] : directions) {
      int newX = current.x + dx;
      int newY = current.y + dy;

      // Skip if not walkable
      if (!isWalkable(grid, newX, newY))
        continue;

      // Calculate new path cost (10 for cardinal, 14 for diagonal ≈ √2 * 10)
      int moveCost = (dx == 0 || dy == 0) ? 10 : 14;
      int newGCost = current.gCost + moveCost;

      Node *neighbor = getNode(newX, newY);

      // Update node if we found a better path
      if (newGCost < neighbor->gCost) {
        neighbor->parent = getNode(current.x, current.y);
        neighbor->gCost = newGCost;
        neighbor->fCost = newGCost + neighbor->hCost;
        openList.push(*neighbor);
      }
    }
  }

  // Clean up if no path found
  for (auto &row : allNodes) {
    for (auto &node : row.second) {
      delete node.second;
    }
  }
  return {};
}

int AStar::heuristic(int x1, int y1, int x2, int y2) {
  int dx = std::abs(x1 - x2);
  int dy = std::abs(y1 - y2);
  return 10 * (dx + dy) + (4 * std::min(dx, dy));
}
