#include "Ghost.hpp"

Ghost::Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _targetPosition = m.getMacInitPosition();
  _targetPath = {};
}

Ghost::~Ghost() {}

void Ghost::update() {
  Point current = map.computeGridPositionCentered(_sprite.getPosition());
  Point target = map.computeGridPositionCentered(_targetPosition);

  if (current == target) {
	this->setSpriteDirection({0.0f, 0.0f});
	return;
  }

  if (_targetPath.empty()) {
	/* TODO: use std::queue */
	_targetPath = map.computePath(current, target);
  }
  
  Point subtarget = _targetPath.back();
  if (current == subtarget) {
	/* Note path array is ordered from {goal, ... , start} */ 
	_targetPath.pop_back(); 
	
	subtarget = _targetPath.back();
  };

  sf::Vector2f direction = current << subtarget;  
  this->setSpriteDirection(direction);
 
}

void Ghost::setTargetPosition(sf::Vector2f targetPosition) {
  _targetPosition = targetPosition;
}

void Ghost::setTargetPosition(float x, float y) {
  sf::Vector2f tmp(x, y);  
  Ghost::setTargetPosition(tmp);
}

sf::Vector2f Ghost::getTargetPosition() {
  return sf::Vector2f(0.0f,0.0f);
}
