#include "Map.hpp"
#include <iostream>

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

	case '*':
	  mapParsed[y][x] = Snack;
	  break;

	default:
	  mapParsed[y][x] = None;
	}
  }
};

Map::~Map() {};

void Map::drawMap(sf::RenderWindow& window) {
  sf::Texture cellTexture;
  sf::RectangleShape cellDrawable(sf::Vector2f(cellWidth, cellWidth));
  cellTexture.loadFromFile("./assets/map.png");
  cellDrawable.setTexture(&cellTexture);

  for (int i = 0; i < mapParsed.size(); i++) {

	for (int j = 0; j < mapParsed[i].size(); j++) {

	  GameCell cell = mapParsed[i][j];

	  cellDrawable.setPosition(computeCellPos(j, i));

	  if (cell == Wall) {
		cellDrawable.setTextureRect(sf::IntRect(32, 0, 32, 32));
	  }

	  else if (cell == Snack) {
		// cellTexture.loadFromFile("./assets/snack.png");
		// cellDrawable.setFillColor(sf::Color(0, 0, 50));
		cellDrawable.setTextureRect(sf::IntRect(0, 0, 32, 32));
	  }

	  else {
		continue;
	  }

	  window.draw(cellDrawable);
	}
  }
}

sf::Vector2f Map::computeCellPos(int x, int y) {
  return sf::Vector2f(x * cellWidth, y * cellWidth);
}

sf::Vector2f Map::getMacInitPosition() {
  return macInitPosition;
}

GameCell Map::getCellAt(unsigned int row, unsigned int col) {
  return mapParsed[row % (mapWidth + 2)][col % mapWidth];
}


sf::Vector2f Map::checkSpriteCollision(sf::Vector2f spritePos) {

  float offsetCompensate = 0.0f;

  // std::cout << "POS: " << spritePos.x << " " << spritePos.y << "\n";

  std::array<sf::Vector2f, 4> spriteCorners = {
	sf::Vector2f(spritePos.x, spritePos.y),
	sf::Vector2f(spritePos.x + cellWidth - 0.01f, spritePos.y),
	sf::Vector2f(spritePos.x, spritePos.y + cellWidth - 0.01f),
	sf::Vector2f(spritePos.x + cellWidth - 0.01f, spritePos.y + cellWidth - 0.01f),
  };

  int i = 0;

  for (auto it = spriteCorners.begin(); it != spriteCorners.end(); it++) {

	int overlapCellX, overlapCellY;

	overlapCellX = std::floor(it->x / cellWidth);
	overlapCellY = std::floor(it->y / cellWidth);
	
	if (mapParsed[overlapCellY][overlapCellX] == Wall) {

	  sf::Vector2f overlapCellPos = computeCellPos(overlapCellX, overlapCellY);

	  float dxParity = spritePos.x - overlapCellPos.x < 0 ? -1.0f : 1.0f;
	  float dyParity = spritePos.y - overlapCellPos.y < 0 ? -1.0f : 1.0f;
	  
	  float dx = (cellWidth - std::abs(spritePos.x - overlapCellPos.x)) * (dxParity);
	  float dy = (cellWidth - std::abs(spritePos.y - overlapCellPos.y)) * (dyParity);

	  // std::cout << i << ": SPRITE:" << (float) std::abs(spritePos.x) << "\n";
	  // std::cout << i << ": WALL: " << (float) std::abs(overlapCellPos.x) << "\n";

	  return sf::Vector2f(dx, dy);

	}
	i++;

  }

  return sf::Vector2f(0.0f, 0.0f);
}

bool Map::checkSpriteCollision(sf::Vector2f pos, float direction[2]) {
  sf::Vector2f cornerTL, cornerTR, cornerBL, cornerBR;
  sf::Vector2f collisionBoundA, collisionBoundB;

  cornerTL = pos;
  cornerTR = sf::Vector2f(pos.x + cellWidth, pos.y);
  cornerBL = sf::Vector2f(pos.x, pos.y + cellWidth);
  cornerBR = sf::Vector2f(pos.x + cellWidth, pos.y + cellWidth);

  /*
	[moving right]    [targets]

	    blockmin      +---+
	+---+             | 0 |
	| 0 |     ->      +---+
	+---+             | 0 |
	    blockmax      +---+
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
