#include "Map.hpp"

Map::Map(const std::string map, int mapWidth, int cellWidth) {
  this->mapString = map;
  this->cellWidth = cellWidth;
  this->mapWidth = mapWidth;

  int y = -1;
  
  for (int i = 0; i < map.size(); i++) {
	int x = i % mapWidth;
	
	if (x == 0) y++;

	switch (map[i]) {
	  
	case '0':
	  mapParsed[y][x] = Wall;
	  break; 

	case '@':
	  mapParsed[y][x] = None;
	  macInitPosition = computeCellPos(x, y);
	  break;

	default:
	  mapParsed[y][x] = None;
	}
  }
};

Map::~Map() {};

void Map::drawMap(sf::RenderWindow& window) {

  for (int i = 0; i < mapParsed.size(); i++) {

	for (int j = 0; j < mapParsed[i].size(); j++) {

	  GameCell cell = mapParsed[i][j];

	  if (cell == Wall) {
		sf::RectangleShape cell(sf::Vector2f(cellWidth, cellWidth));
		cell.setFillColor(sf::Color(0, 0, 255));
		cell.setPosition(computeCellPos(j, i));
	  
		window.draw(cell);
	  }
	}
  }
}

sf::Vector2f Map::computeCellPos(int x, int y) {
  return sf::Vector2f(x * cellWidth, y * cellWidth);
}

sf::Vector2f Map::getMacInitPosition() {
  return macInitPosition;
}

bool Map::checkSpriteCollision(sf::Vector2f pos, float direction[2]) {
  int collisionBoundA, collisionBoundB;

  /*
	suppose moving right:
	
	+---+ blockmin
	|   |     ->
	+---+ blockmax
   */

  if (playerDirection[1] < 0 || playerDirection[0] < 0)
	blockCornerA = pos
}
