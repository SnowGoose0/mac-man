#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

#include "Map.hpp"

class RectSprite {

public:

  RectSprite(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed);
  ~RectSprite();

  void moveSprite(Map m);

  sf::RectangleShape getSprite();

  void setSpritePosition(sf::Vector2f spriteOffset);

  void setSpriteDirection(sf::Vector2f direction);

  void setSpriteTexture(std::string path);

private:

  float detectCollision();

  GameCell getNeighboringCell(sf::Vector2f direction, Map m);

  sf::Vector2f getNeighboringCellCoordinates(sf::Vector2f direction);

private:

  sf::RectangleShape _sprite;

  float _spriteSpeed;
  
  sf::Texture _spriteTexture;

  sf::Vector2f _spritePosition;

  sf::Vector2f _prevDirection;
  sf::Vector2f _currentDirection;
  sf::Vector2f _queuedDirection;

};
