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
  sf::Vector2f cornerTL, cornerTR, cornerBL, cornerBR;
  sf::Vector2f collisionBoundA, collisionBoundB;

  cornerTL = pos;
  cornerTR = sf::Vector2f(pos.x + cellWidth, pos.y);
  cornerBL = sf::Vector2f(pos.x, pos.y + cellWidth);
  cornerBR = sf::Vector2f(pos.x + cellWidth, pos.y + cellWidth);

  /*
	suppose moving right:
	
	+---+ blockmin
	|   |     ->
	+---+ blockmax
   */

  if (direction[0] < 0 || direction[1] < 0) { // moving up or left
	
	collisionBoundA = cornerTL;

	if (direction[0] < 0) { // moving left
	  collisionBoundB = cornerBL;
	}

	else {
	  collisionBoundB = cornerTR;
	}
  }

  else { // moving down or right
	
	collisionBoundA = cornerBR;

	if (direction[0] > 1) { // moving right
	  collisionBoundB = cornerTR;
	}

	else {
	  collisionBoundB = cornerBL;
	}
  }

  int logicalPositionX, logicalPositionY;

  logicalPositionX = std::floor((collisionBoundA.x - cellWidth) / cellWidth) - 1;
  logicalPositionY = std::floor((collisionBoundA.y) / cellWidth) - 1;

  if (mapParsed[logicalPositionY][logicalPositionX] == Wall) {
	return true;
  } 

  return false;
}
