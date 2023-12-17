#include "Algorithm.hpp"

Graph::Graph(Map& m) {
  _graph = m.mapParsed;
  
}

Graph::~Graph() {}

std::vector<Point>
Graph::aStar(Point& start, Point& end) {
  if (!traversable(start) || !traversable(end))
	return {};

  /* priority queue for open nodes */
  std::vector<Node*> openSet;

  /* set for expanded nodes */
  std::unordered_set<Node*> closedSet;

  /* ALL allocated nodes - used for memory management*/
  std::vector<Node*> nodeList;

  Node* startNode = new Node();
  startNode->p = start;
  startNode->g = 0;
  startNode->h = heuristic(start, end);
  startNode->parent = nullptr;
  
  openSet.push_back(startNode);
  nodeList.push_back(startNode);
  std::make_heap(openSet.begin(), openSet.end(), NodeComparator());

  while (!openSet.empty()) {
	std::pop_heap(openSet.begin(), openSet.end(), NodeComparator());
	Node* current = openSet.back(); openSet.pop_back();

	if (current->p == end) {
	  std::vector<Point> path;
	  
	  while (!(current->p == start)) {
		path.push_back(current->p);
		current = current->parent;
	  }
	  
	  freeNodeList(nodeList);
	  return path;
	}

	closedSet.insert(current);

	// TODO: DYNAMICALLY STORE NODES
	std::vector<Point> neighbors = getNeighbors(*current);
	for (const Point& next : neighbors) {
	  if (!traversable(next)) continue;

	  Node* successor = new Node();
	  successor->p = next;
	  successor->g = current->g + 1;
	  successor->h = heuristic(next, end);
	  successor->parent = current;

	  nodeList.push_back(successor);
	  
	  auto closeIt = closedSet.find(successor);
	  auto openIt = std::find(openSet.begin(), openSet.end(), successor);

	  if (closeIt != closedSet.end()) continue;	  
	  if (openIt != openSet.end() && (*openIt)->g < successor->g) continue;

	  openSet.push_back(successor);
	  std::push_heap(openSet.begin(), openSet.end(), NodeComparator());
	}
  }

  freeNodeList(nodeList);
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

void Graph::freeNodeList(std::vector<Node*> list) {
  for (auto it = list.begin(); it != list.end(); it++) {
	delete *it;
  }
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
