#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

#include "Map.hpp"

class RectSprite {

public:

  RectSprite(float spriteWidth, sf::Vector2f spritePosition, float spriteSpeed);
  ~RectSprite();

  sf::RectangleShape getSprite();

  void moveSprite(Map m);

  void setSpritePosition(sf::Vector2f spriteOffset);

  void setDirection(sf::Vector2f direction);

  void setSpriteTexture(std::string path);

private:

  sf::RectangleShape _sprite;

  unsigned int _spriteSpeed;
  
  sf::Texture _spriteTexture;

  sf::Vector2f _spritePosition;
  sf::Vector2f _currentDirection;
  sf::Vector2f _queuedDirection;

};
