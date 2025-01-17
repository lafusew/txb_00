#include <execution>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

struct Node
{
	int x, y;
	int gCost, hCost, fCost;
	Node* parent;

	Node(int x, int y, int g, int h, Node* p = nullptr)
		: x(x), y(y), gCost(g), hCost(h), fCost(g + h), parent(p){}
	
	bool operator>(const Node& other) const
	{
		return fCost > other.fCost;
	}
};

struct Grid
{
	int width, height;
	std::vector<std::vector<bool>> tiles; // true = walkable, false = blocked

	Grid(int w, int h) : width(w), height(h), tiles(w, std::vector<bool>(h, true)) {}

	bool isWalkable(int x, int y) const
	{
		return x >= 0 && y >= 0 && x < width && y < height && tiles[x][y];
	}
};

class AStar
{
public:
	static std::vector<std::pair<int, int>> findPath(
		const Grid& grid,
		std::pair<int, int> start,
		std::pair<int, int> goal
	);

private:
	static int heuristic(int x1, int y1, int x2, int y2);
};
