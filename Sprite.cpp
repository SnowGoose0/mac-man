#include "Sprite.hpp"

RectSprite::RectSprite(float spriteWidth, sf::Vector2f spritePosition) {

  this.sprite = sf::RectangleShape s(sf::Vector2f(spriteWidth, spriteWidth));
  this.spritePosition = spritePosition;
  
}

RectSprite::~RectSprite() {}

void RectSprite::moveSprite(sf::Vector2f spriteOffset) {
  move(spriteOffset.x, spriteOffset.y);
}

void RectSprite::moveSprite(float xOffset, float yOffset) {
  move(xOffset, yOffset);
}

void RectSprite::setSpritePosition(sf::Vector2f spriteOffset) {
  sprite.setPosition(spriteOffset);
}

void RectSprite::createSpriteTexture(string path) {
  spriteTexture.loadTexture(path);
}

void RectSprite::move(float xOffset, float yOffset) {
  player.move(xOffset, yOffset);
}
