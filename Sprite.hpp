#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class RectSprite {

public:

  RectSprite(float spriteWidth, sf::Vector2f spritePosition, unsigned int spriteSpeed);
  ~RectSprite();

  sf::RectangleShape getSprite();

  void moveSprite();

  void setSpritePosition(sf::Vector2f spriteOffset);

  void setDireciton();

  void createSpriteTexture(string path);

private:

  sf::RectangleShape _sprite;

  unsigned int _spriteSpeed;
  
  sf::Texture _spriteTexture;
  
  sf::Vector2f _currentDirection;
  sf::Vector2f _queuedDirection;

}
