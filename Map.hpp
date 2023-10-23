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

  bool checkSpriteCollision(sf::Vector2f pos, float direction[2]);

  sf::Vector2f checkSpriteCollision(sf::Vector2f spritePos);

  sf::Vector2f computeCellPos(int x, int y);

private:
  std::string mapString;
  
  int cellWidth;

  int mapWidth;

  sf::Vector2f macInitPosition;

  std::array<std::array<GameCell, 19>, 21> mapParsed;
 
};
