#include "Algorithm.hpp"

int heuristic(const Point& p1, const Point& p2) {
  return p2 - p1;
}

Graph::Graph(Map& m) {
  _graph = m.mapParsed;
  
}

Graph::~Graph() {}

std::vector<Point>
Graph::aStar(Point& start, Point& end) {
  std::vector<Point> path;
  std::priority_queue<Node> openList;
  std::unordered_map<Point, > closeList;
  
  openList.push({.p = start, .g = 0, .h = 0});

  while (openList.size() > 0) {
	Node cur = openList.top();

	// { left, right, top, bottom }
	std::vector<Point> neighbors = {
	  {cur.p.x - 1, cur.p.y},
	  {cur.p.x + 1, cur.p.y},
	  {cur.p.x, cur.p.y - 1},
	  {cur.p.x, cur.p.y + 1}
	};

	for (const Point& next : neighbors) {
	  // wall check
	  if (_graph[next.y][next.x] == Wall) {
		continue;
	  }
	  
	  // target check
	  if (next == end) { 
		path.push_back(next);
		break;
	  }

	  Node nextNode = {.p = next, .g = cur, .h = heuristic(next, end)};

	  
	  
	}

	openList.pop();
  }

  return path;
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
