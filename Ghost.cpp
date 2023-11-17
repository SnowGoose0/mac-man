#include "Ghost.hpp"

Ghost::~Ghost() {}

Ghost::Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _targetPosition = sf::Vector2f(0.0f, 0.0f);
}




void Ghost::update() {
  // if ghost is at intersection

  // ghost will move randomly for now
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
