#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

#include "Map.hpp"

class RectSprite {

public:

  RectSprite(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m);
  ~RectSprite();

  void draw(sf::RenderWindow& window);

  void moveSprite();

  sf::RectangleShape getSprite();

  void setSpritePosition(sf::Vector2f spriteOffset);

  void setSpriteDirection(sf::Vector2f direction);

  void setSpriteTexture(std::string path);

protected:

  void checkCollision();

  GameCell getNeighboringCell(sf::Vector2f direction);

  sf::Vector2f getNeighboringCellCoordinates(sf::Vector2f direction);

protected:
  sf::Vector2f _prevDirection;
  sf::Vector2f _currentDirection;
  sf::Vector2f _queuedDirection;

  Map& map;

  sf::RectangleShape _sprite;

  float _spriteSpeed;
  
  sf::Texture _spriteTexture;

  sf::Vector2f _spritePosition;

};
