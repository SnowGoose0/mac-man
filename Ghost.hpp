#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>

#include "Sprite.hpp"
#include "Algorithm.hpp"
#include "Common.hpp"

class Ghost : public RectSprite {

public:

  Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m);
  
  ~Ghost();

  int update();

  void setTargetPosition(sf::Vector2f targetPosition);

  void setMacPosition(sf::Vector2f position);

private:
  void setTargetPosition(float x, float y);
  sf::Vector2f getTargetPosition();

private:
  sf::Vector2f _targetPosition;
  std::vector<Point> _targetPath;
  Point _currentPoint;
  Point _parentPoint;

  sf::Vector2f _macPosition;
};
