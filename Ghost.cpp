#include "Ghost.hpp"

Ghost::Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  //_targetPosition = m.getMacInitPosition();
  _targetPosition = {-90.0f, -90.0f};
  _targetPath = {};
  _currentPoint = map.computeGridPosition(_sprite.getPosition());
  _parentPoint = {-444, -444};
}

Ghost::~Ghost() {}

void Ghost::update() {
  Point current = map.computeGridPositionCentered(_sprite.getPosition()); 
  Point target = map.computeGridPositionCentered(_targetPosition);

  if (_targetPath.empty()) {
	/* TODO: use std::queue */
	
	_targetPath = map.computePath(current, target, _parentPoint);

	if (_targetPath.size() == 0) {
	  std::cout << "GG" << std::endl;
	  exit(0);
	}
  }
  
  Point subtarget = _targetPath.back();
  
  if (current == subtarget) {
	/* Note path array is ordered from {goal, ... , start} */ 
	_targetPath.pop_back(); 
  };

  sf::Vector2f direction = current << subtarget;
  
  this->setSpriteDirection(direction);

  if (!(_currentPoint == current)) {
	_parentPoint = _currentPoint;
  }
  
  _currentPoint = current;
}

void Ghost::setTargetPosition(sf::Vector2f targetPosition) {
  if (_targetPosition != targetPosition) {
	_targetPosition = targetPosition;
	_targetPath = {};  /* empty path will trigger path recomputation */
  }
}

void Ghost::setTargetPosition(float x, float y) {
  sf::Vector2f tmp(x, y);  
  Ghost::setTargetPosition(tmp);
}

sf::Vector2f Ghost::getTargetPosition() {
  return sf::Vector2f(0.0f,0.0f);
}
