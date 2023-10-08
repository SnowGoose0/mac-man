#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Map {

public:
  Map(const std::string map, int mapWidth, int cellWidth);

  ~Map();

  void drawMap(sf::RenderWindow& win);

private:
  std::string map;
  
  int cellWidth;

  int mapWidth;
 
};
