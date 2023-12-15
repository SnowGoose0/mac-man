#include "Algorithm.hpp"

Graph::Graph(Map& m) {
  _graph = m.mapParsed;
  
}

Graph::~Graph() {}

std::vector<Point>
Graph::aStar(Point& start, Point& end) {
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
  std::unordered_set<Node> openSetTrace;
  std::unordered_set<Node> closedSet; 

  Node s = {.p = start, .g = 0, .h = 0, .parent = nullptr};
  openSet.push(s);
 
  while (!openSet.empty()) {
	Node cur = openSet.top(); openSet.pop();

	if (cur.p == end) {
	  // TODO: TRACE PATH
	  return path;
	}

	closedSet.insert(cur);

	std::vector<Point> neighbors = getNeighbors();
	for (const Point& next : neighbors) {
	  if (!traversable(next)) continue;
	  
	  Node successor = {.p = next,
						.g = cur.g + 1,
						.h = heuristic(next, end),
						.parent = &cur};
	  
	  auto closedIt = closedSet.find(successor);
	  if (closedIt != closedSet.end() && closedIt->f() > successor.f()) {
		closedSet.erase(closedIt);
		closedSet.insert(successor);
	  }
	  
	  if (openSetTrace.find(successor) == openSetTrace.end()) { 
		openSet.push(successor);
		openSetTrace.insert(successor);
	  }
	  
	}
  }

  return path;
}

bool Graph::traversable(Point& target) {
  if (_graph[next.y][next.x] == Wall)
	return false;

  return true;
}

int Graph::heuristic(const Point& p1, const Point& p2) {
  return p2 - p1;
}

std::vector<Point> Graph::getNeighbors(const Node& node) {
  // { left, right, top, bottom }
  std::vector<Point> neighbors = { 
	{cur.p.x - 1, cur.p.y},
	{cur.p.x + 1, cur.p.y},
	{cur.p.x, cur.p.y - 1},
	{cur.p.x, cur.p.y + 1}
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
