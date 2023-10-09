#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <string>

#include "Common.hpp"

class Map {

public:
  Map(const std::string map, int mapWidth, int cellWidth);

  ~Map();

  void drawMap(sf::RenderWindow& win);

  sf::Vector2f getMacInitPosition();

private:
  sf::Vector2f computeCellPos(int x, int y);

private:
  std::string mapString;
  
  int cellWidth;

  int mapWidth;

  sf::Vector2f macInitPosition;

  std::array<std::array<GameCell, 19>, 19> mapParsed;
 
};
