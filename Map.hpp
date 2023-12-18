#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <string>
#include <cmath>

#include "Common.hpp"
#include "Algorithm.hpp"

class Map {

public:
  
  Map(const std::string map, int mapWidth, int cellWidth);

  ~Map();

  void drawMap(sf::RenderWindow& win);
  
  GameCell getCellAt(unsigned int row, unsigned int col);
  
  void updateCellAt(unsigned int row, unsigned int col, GameCell newState);

  sf::Vector2f getMacInitPosition();

  sf::Vector2f computeMapPosition(int x, int y);
  
  Point computeGridPosition(sf::Vector2f position);
  Point computeGridPositionCentered(sf::Vector2f position);
  
  std::vector<Point> computePath(int x1, int y1, int x2, int y2);
  std::vector<Point> computePath(Point& s, Point& g);

private:
  int computeWallTileOffset(int x, int y);
  
  std::vector<Point> aStar(Point& start, Point& end);
  
  bool traversable(const Point& p);

  int heuristic(const Point& p1, const Point& p2);

  std::vector<Point> getNeighbors(int x, int y);
  std::vector<Point> getNeighbors(const Node& node);

  bool isValidGridPosition(int x, int y);

  void freeNodeList(std::vector<Node*> list);


public:
  int cellWidth;
  int mapWidth;
  unsigned int palletCount;

private:
  std::string _mapString;
  sf::Vector2f _macInitPosition;
  std::array<std::array<GameCell, 19>, 21> _mapParsed;
 
};
