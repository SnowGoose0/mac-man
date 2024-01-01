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

  GameStatus update();

  bool isActive();

  void setTargetPosition(sf::Vector2f targetPosition);

  void setMacPosition(sf::Vector2f position);
  void setMacStatus(int status);

private:
  void setTargetPosition(float x, float y);
  sf::Vector2f getTargetPosition();


private:
  int _lives;
  sf::Texture _texture;
  
  sf::Vector2f _targetPosition;
  std::vector<Point> _targetPath;
  
  Point _currentPoint;
  Point _parentPoint;

  int _ghostStatus;
  sf::Vector2f _macPosition;
};
