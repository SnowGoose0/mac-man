#include "Map.hpp"
#include <iostream>

Map::Map(const std::string map, int mapWidth, int cellWidth) {
  _mapString = map;
  _cellTexture.loadFromFile("./assets/map.png");
  
  this->cellWidth = cellWidth;
  this->mapWidth = mapWidth;

  int y = -1;
  int palletCounter = 0;
  
  for (int i = 0; i < map.size(); i++) {
	int x = i % mapWidth;
	
	if (x == 0) y++;

	switch (map[i]) {
	  
	case '0':
	  _mapParsed[y][x] = Wall;
	  break; 

	case '@':
	  _mapParsed[y][x] = None;
	  _macInitPosition = computeMapPosition(x, y);
	  break;

	case '*':
	  _mapParsed[y][x] = Snack;
	  palletCounter++;
	  break;

	default:
	  _mapParsed[y][x] = None;
	}
  }

  this->palletCount = palletCounter;
};

Map::~Map() {};

void Map::drawMap(sf::RenderWindow& window) {
  sf::RectangleShape cellDrawable(sf::Vector2f(cellWidth, cellWidth));
  cellDrawable.setTexture(&_cellTexture);

  for (int i = 0; i < _mapParsed.size(); i++) {
	for (int j = 0; j < _mapParsed[i].size(); j++) {

	  GameCell cell = _mapParsed[i][j];
	  int ppc = 32;

	  cellDrawable.setPosition(computeMapPosition(j, i));

	  if (cell == Wall) {
		int wallTileOffset = computeWallTileOffset(j, i);
		cellDrawable.setTextureRect(sf::IntRect(ppc*(wallTileOffset), 0, ppc, ppc));
	  }

	  else if (cell == Snack) {
 		cellDrawable.setTextureRect(sf::IntRect(0, ppc, ppc, ppc));
	  }

	  else {
		continue;
	  }
	  
	  window.draw(cellDrawable);
	}
  }
}

sf::Vector2f Map::getMacInitPosition() {
  return _macInitPosition;
}

Point Map::computeGridPosition(sf::Vector2f position) {
  return {
	static_cast<int>((position.x) / 25.0f),
	static_cast<int>((position.y) / 25.0f),
  };
}

Point Map::computeGridPositionCentered(sf::Vector2f position) {
  return {
	static_cast<int>((position.x + (cellWidth / 2)) / 25.0f),
	static_cast<int>((position.y + (cellWidth / 2)) / 25.0f),
  };
}

sf::Vector2f Map::computeMapPosition(int x, int y) {
  return sf::Vector2f(x * cellWidth, y * cellWidth);
}

GameCell Map::getCellAt(unsigned int row, unsigned int col) {
  return _mapParsed[row % (mapWidth + 2)][col % mapWidth];
}

void Map::updateCellAt(unsigned int row, unsigned int col, GameCell newState) {
  GameCell currentState = _mapParsed[row % (mapWidth + 2)][col % mapWidth];

  if (currentState == Wall) { return; } // do not allow modification of walls
  _mapParsed[row % (mapWidth + 2)][col % mapWidth] = newState;
}

int Map::computeWallTileOffset(int x, int y) {
  /* { top right bottom left} */
  int dx[] = {0, 1, 0, -1}; int dy[] = {-1, 0, 1, 0};
  int offset = 0b0000;

  for (int i = 0; i < 4; ++i) {
	int nx = x + dx[i]; int ny = y + dy[i];

	if (isValidGridPosition(nx, ny) && getCellAt(ny, nx) == Wall)
	  offset |= (1 << 3 - i);
  }
  
  return offset;
}

std::vector<Point>
Map::aStarFallback(Point& start, Point& end, Point& parent) {
  std::cout << "Yea";
  if (!traversable(start))
	return {};

  std::vector<Point> neighbors = getNeighbors(start.x, start.y);
  Point bestNeighbor;
  int bestHeuristic = INT_MAX;
  for (const Point& next : neighbors) {
	if (!traversable(next) || next == parent) {
	  continue;
	}

	next.print();

	int h = heuristic(next, end);
	if (h < bestHeuristic) {
	  bestHeuristic = h;
	  bestNeighbor = next;
	}
  }

  if (bestHeuristic != INT_MAX) {
	return {bestNeighbor};
  } 

  return {};
}

std::vector<Point>
Map::aStar(Point& start, Point& end, Point& parent) {
  if (!traversable(start))
	return {};

  if (!isValidGridPosition(end.x, end.y)) {
	end.print();
	return aStarFallback(start, end, parent);
  }

  /* priority queue for open nodes */
  std::vector<Node*> openSet;

  /* set for expanded nodes */
  std::unordered_set<Node*> closedSet;

  /* ALL allocated nodes - used for memory management*/
  std::vector<Node*> nodeList;

  Node parentNode = {.p = parent, .g = 0, .h = 0, .parent = nullptr};

  Node* startNode = new Node();
  startNode->p = start;
  startNode->g = 0;
  startNode->h = heuristic(start, end);
  startNode->parent = &parentNode;
  
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
	  if (!traversable(next) || next == current->parent->p) continue;

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

bool Map::traversable(const Point& target) {
  if (_mapParsed[target.y][target.x] == Wall)
	return false;

  return true;
}

int Map::heuristic(const Point& p1, const Point& p2) {
  return p2 - p1;
}

bool Map::isValidGridPosition(int x, int y) {
  return x >= 0 && x < 19 && y >= 0 && y < 21;
}

std::vector<Point> Map::getNeighbors(int x, int y) {
  std::vector<Point> neighbors;
  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, -1, 1};

  for (int i = 0; i < 4; ++i) {
	int nx = x + dx[i]; int ny = y + dy[i];
	
	if (isValidGridPosition(nx, ny))
	  neighbors.push_back({nx, ny});
  }
	
  return neighbors;
}

std::vector<Point> Map::getNeighbors(const Node& node) {
  return getNeighbors(node.p.x, node.p.y);
}

void Map::freeNodeList(std::vector<Node*> list) {
  for (auto it = list.begin(); it != list.end(); it++) {
	delete *it;
  }
}

std::vector<Point>
Map::computePath(int x1, int y1, int x2, int y2, int x3, int y3) {
  struct Point p1 = {x1, y1};
  struct Point p2 = {x2, y2};
  struct Point p3 = {x3, y3};

  return aStar(p1, p2, p3);
}

std::vector<Point>
Map::computePath(Point& s, Point& g, Point& p) {
  return aStar(s,g, p);
}
