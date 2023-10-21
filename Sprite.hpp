#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class RectSprite {

public:

  RectSprite(float spriteWidth, sf::Vector2f spritePosition);
  ~RectSprite();

  sf::RectangleShape getSprite();

  void moveSprite(sf::Vector2f spriteOffset);

  void moveSprite(float xOffset, float yOffset);

  void setSpritePosition(sf::Vector2f spriteOffset);

  void createSpriteTexture(string path) {

private:
  void move(float xOffset, float yOffset);

private:

  sf::RectangleShape sprite;
  sf::Texture spriteTexture;

  sf::Vector2f currentDirection;
  sf::Vector2f queuedDirection;

}
