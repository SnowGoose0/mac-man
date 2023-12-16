#include "Algorithm.hpp"

Graph::Graph(Map& m) {
  _graph = m.mapParsed;
  
}

Graph::~Graph() {}

std::vector<Point>
Graph::aStar(Point& start, Point& end) {
  std::vector<Node> openSet;
  std::unordered_set<Node> closedSet;

  Node s = {
	.p = start,
	.g = 0,
	.h = heuristic(start, end),
	.parent = nullptr
  };

  Node* sa = new Node();
  openSet.push_back(s);
  std::make_heap(openSet.begin(), openSet.end(), std::greater<Node>());

  while (!openSet.empty()) {
	std::pop_heap(openSet.begin(), openSet.end(), std::greater<Node>());
	Node cur = openSet.back(); openSet.pop_back();

	if (cur.p == end) {
	  std::vector<Point> path;
	  while (cur.parent) {
		path.push_back(cur.p);
		cur = *cur.parent;
	  }
	  return path;
	}

	closedSet.insert(cur);

	// TODO: DYNAMICALLY STORE NODES
	std::vector<Point> neighbors = getNeighbors(cur);
	for (const Point& next : neighbors) {
	  if (!traversable(next)) continue;
	  
	  Node successor = {.p = next,
						.g = cur.g + 1,
						.h = heuristic(next, end),
						.parent = &cur};
	  
	  auto closeIt = closedSet.find(successor);
	  auto openIt = std::find(openSet.begin(), openSet.end(), successor);

	  if (closeIt != closedSet.end()) continue;	  
	  if (openIt != openSet.end() && openIt->g < successor.g) continue;

	  openSet.push_back(successor);
	  std::push_heap(openSet.begin(), openSet.end(), std::greater<Node>());
	}
  }

  return {};
}

bool Graph::traversable(const Point& target) {
  if (_graph[target.y][target.x] == Wall)
	return false;

  return true;
}

int Graph::heuristic(const Point& p1, const Point& p2) {
  return p2 - p1;
}

std::vector<Point> Graph::getNeighbors(const Node& node) {
  // { left, right, top, bottom }
  std::vector<Point> neighbors = { 
	{node.p.x - 1, node.p.y},
	{node.p.x + 1, node.p.y},
	{node.p.x, node.p.y - 1},
	{node.p.x, node.p.y + 1}
  };

  return neighbors;
}

std::vector<Point>
Graph::computePath(int x1, int y1, int x2, int y2) {
  struct Point p1 = {x1, y1};
  struct Point p2 = {x2, y2};

  return aStar(p1, p2);
}

std::vector<Point>
Graph::computePath(sf::Vector2f& start, sf::Vector2f& end) {
  struct Point p1 = {(int) start.x, (int) start.y};
  struct Point p2 = {(int) end.x, (int) end.y};
  return aStar(p1, p2);
}
