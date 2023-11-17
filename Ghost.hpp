#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

#include "Sprite.hpp"

class Ghost : public RectSprite {

public:

  Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m);
  
  ~Ghost();

private:
  void update();
  void setTargetPosition(sf::Vector2f targetPosition);
  void setTargetPosition(float x, float y);
  sf::Vector2f getTargetPosition();

private:

  sf::Vector2f _targetPosition;
  
};
