#include "Ghost.hpp"

Ghost::Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _targetPosition = spriteInitPosition;
}

Ghost::~Ghost() {}

void Ghost::update() {
  sf::Vector2f newDirection(0.0f, 0.0f);
  
  sf::Vector2f currentPosition = _sprite.getPosition();
  int posX = (currentPosition.y + 12.5f) / 25.0f;
  int posY = (currentPosition.x + 12.5f) / 25.0f;

  if (_targetPath.empty()) {
	_targetPath = g.computePath(posX, posY, _targetPosition.x, _targetPosition.y);
  }

  Point subtarget = _targetPath[0];
  if (subtarget.x == posX && subtarget.y == posY) {
	_targetPath.erase(_targetPath.begin());
  };
  
  this->setSpriteDirection(newDirection);
}

void Ghost::setTargetPosition(sf::Vector2f targetPosition) {
  
}

void Ghost::setTargetPosition(float x, float y) {
  sf::Vector2f tmp(x, y);  
  Ghost::setTargetPosition(tmp);
}

sf::Vector2f Ghost::getTargetPosition() {
  return sf::Vector2f(0.0f,0.0f);
}
