#include "Ghost.hpp"

Ghost::Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  isActive = true;
  //_targetPosition = m.getMacInitPosition();
  _targetPosition = {-50.0f, 50.0f};
  _targetPath = {};
  _currentPoint = map.computeGridPosition(_sprite.getPosition());
  _parentPoint = {-444, -444};
  _macPosition = {-90.0f, -90.0f};
}

Ghost::~Ghost() {}

GameStatus Ghost::update() {
  Point mac = map.computeGridPositionCentered(_macPosition);
  
  Point current = map.computeGridPositionCentered(_sprite.getPosition()); 
  Point target = map.computeGridPositionCentered(_targetPosition);

  /* macman and ghost collision */
  if (mac - current < 1) {
	std::cout << "GG" << std::endl;
	isActive=false;
	// return GAME_OVER;
	return GAME_ONGOING;
  }

  if (_targetPath.empty()) {
	/* TODO: use std::queue */
	
	_targetPath = map.computePath(current, target, _parentPoint);

	// if (_targetPath.size() == 0) {
	//   std::cout << "GG" << std::endl;
	//   exit(0);
	// }
  }
  
  Point subtarget = _targetPath.back();
  sf::Vector2f direction = current << subtarget;
  
  if (current == subtarget) {
	/* Note path array is ordered from {goal, ... , start} */ 
	_targetPath.pop_back(); 
  }

  if (!(_currentPoint == current)) {
	_parentPoint = _currentPoint;
  }
  
  this->setSpriteDirection(direction);
  
  _currentPoint = current;

  return GAME_ONGOING;
}

void Ghost::setTargetPosition(sf::Vector2f targetPosition) {
  if (_targetPosition != targetPosition) {
	_targetPosition = targetPosition;
	_targetPath = {};  /* empty path will trigger path recomputation */
  }
}

void Ghost::setMacPosition(sf::Vector2f position) {
  std::cout << "EVENT\n";
  _macPosition = position;
}

sf::Vector2f Ghost::getTargetPosition() {
  return sf::Vector2f(0.0f,0.0f);
}
