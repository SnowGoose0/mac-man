#include "Map.hpp"
#include <iostream>

Map::Map(const std::string map, int mapWidth, int cellWidth) {
  _mapString = map;
  
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
  sf::Texture cellTexture;
  sf::RectangleShape cellDrawable(sf::Vector2f(cellWidth, cellWidth));
  cellTexture.loadFromFile("./assets/map.png");
  cellDrawable.setTexture(&cellTexture);

  for (int i = 0; i < _mapParsed.size(); i++) {
	for (int j = 0; j < _mapParsed[i].size(); j++) {

	  GameCell cell = _mapParsed[i][j];

	  cellDrawable.setPosition(computeMapPosition(j, i));

	  if (cell == Wall) {
		cellDrawable.setTextureRect(sf::IntRect(32, 0, 32, 32));
	  }

	  else if (cell == Snack) {
 		cellDrawable.setTextureRect(sf::IntRect(0, 0, 32, 32));
	  }

	  else {
		continue;
	  }

	  // switch(cell) {
	  // case Wall:
	  // 	cellDrawable.setTextureRect(sf::IntRect(32, 0, 32, 32));
	  // 	break;
		
	  // case Snack:
	  // 	cellDrawable.setTextureRect(sf::IntRect(0, 0, 32, 32));
	  // 	break;
		
	  // default:
	  // 	continue;
	  // }
	  window.draw(cellDrawable);
	}
  }
}

sf::Vector2f Map::getMacInitPosition() {
  return _macInitPosition;
}

Point Map::computeGridPosition(sf::Vector2f position) {
  return {};
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

std::vector<Point>
Map::aStar(Point& start, Point& end) {
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

bool Map::traversable(const Point& target) {
  if (_mapParsed[target.y][target.x] == Wall)
	return false;

  return true;
}

int Map::heuristic(const Point& p1, const Point& p2) {
  return p2 - p1;
}

std::vector<Point> Map::getNeighbors(const Node& node) {
  // { left, right, top, bottom }
  std::vector<Point> neighbors = { 
	{node.p.x - 1, node.p.y},
	{node.p.x + 1, node.p.y},
	{node.p.x, node.p.y - 1},
	{node.p.x, node.p.y + 1}
  };

  return neighbors;
}

void Map::freeNodeList(std::vector<Node*> list) {
  for (auto it = list.begin(); it != list.end(); it++) {
	delete *it;
  }
}

std::vector<Point>
Map::computePath(int x1, int y1, int x2, int y2) {
  struct Point p1 = {x1, y1};
  struct Point p2 = {x2, y2};

  return aStar(p1, p2);
}

std::vector<Point>
Map::computePath(Point& s, Point& g) {
  return aStar(s,g);
}
