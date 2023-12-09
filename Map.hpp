#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <string>
#include <cmath>

#include "Common.hpp"

class Map {

public:
  Map(const std::string map, int mapWidth, int cellWidth);

  ~Map();

  void drawMap(sf::RenderWindow& win);

  sf::Vector2f getMacInitPosition();

  GameCell getCellAt(unsigned int row, unsigned int col);

  void updateCellAt(unsigned int row, unsigned int col, GameCell newState);

  bool checkSpriteCollision(sf::Vector2f pos, float direction[2]);

  sf::Vector2f checkSpriteCollision(sf::Vector2f spritePos);

  sf::Vector2f computeCellPos(int x, int y);

public:
  int cellWidth;
  int mapWidth;

private:
  std::string mapString;
  sf::Vector2f macInitPosition;
  std::array<std::array<GameCell, 19>, 21> mapParsed;
 
};
