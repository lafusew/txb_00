#include "AStar.h"

// Function to find the shortest path using A* algorithm
std::vector<std::pair<int, int>> AStar::findPath(const Grid &grid, std::pair<int, int> start, std::pair<int, int> goal) {
  // Priority queue (Min-Heap) to store open nodes, sorted by lowest fCost
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
  // Map to store all created nodes, avoiding duplicate allocations
  std::unordered_map<int, std::unordered_map<int, Node *>> allNodes;
  // Lambda function to get or create a node at a given (x, y) position
  auto getNode = [&](int x, int y) -> Node * {
    if (allNodes[x][y] == nullptr) { // If node does not exist, create it
      allNodes[x][y] =
          new Node(x, y, INT_MAX, heuristic(x, y, goal.first, goal.second));
    }
    return allNodes[x][y];
  };
  // Initialize the start node
  Node *startNode = getNode(start.first, start.second);
  startNode->gCost = 0;                // Distance from start to itself is 0
  startNode->fCost = startNode->hCost; // Initial fCost is just the heuristic
  openList.push(*startNode);           // Add start node to open list

  // Define possible movement directions (Up, Right, Down, Left, Diagonals)
  std::vector<std::pair<int, int>> directions = {
      {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

  // Main A* loop: Process nodes until the goal is found or no path exists
  while (!openList.empty()) {
    // Get the node with the lowest fCost from the open list
    Node current = openList.top();
    openList.pop();
    // If the goal is reached, reconstruct the path
    if (current.x == goal.first && current.y == goal.second) {
      std::vector<std::pair<int, int>> path;
      for (Node *n = &current; n != nullptr; n = n->parent) {
        path.emplace_back(n->x, n->y);
      }
      std::reverse(path.begin(), path.end()); // Reverse to get correct order
      return path;                            // Return the final path
    }
    // Explore neighboring nodes
    for (auto [dx, dy] : directions) {
      int nx = current.x + dx;
      int ny = current.y + dy;
      // Skip if the new position is not walkable
      if (!grid.isWalkable(nx, ny))
        continue;
      Node *neighbor = getNode(nx, ny);
      // Assign movement cost: 1 for cardinal moves, 1.4 (~sqrt(2)) for
      // diagonals
      int moveCost = (dx == 0 || dy == 0)
                         ? 1
                         : 14; // Using scaled integer (10x for accuracy)
      int tentativeG = current.gCost + moveCost;
      // If the new path to neighbor is shorter, update it
      if (tentativeG < neighbor->gCost) {
        neighbor->gCost = tentativeG;
        neighbor->fCost =
            neighbor->gCost + neighbor->hCost; // Update total cost
        neighbor->parent =
            getNode(current.x, current.y); // Set parent for path reconstruction
        openList.push(*neighbor); // Add to open list for further exploration
      }
    }
  }

  return {}; // Return empty path if no solution is found
}

// Heuristic function: Uses Diagonal distance (best for 8-directional movement)
int AStar::heuristic(int x1, int y1, int x2, int y2) {
  int dx = std::abs(x1 - x2);
  int dy = std::abs(y1 - y2);
  return 10 * (dx + dy) +
         (4 * std::min(dx, dy)); // Manhattan + diagonal adjustment
}
