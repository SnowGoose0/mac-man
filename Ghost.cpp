#include "Ghost.hpp"

Ghost::Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  //_targetPosition = m.getMacInitPosition();
  _texture.loadFromFile("./assets/map.png");
  _targetPosition = {-50.0f, 50.0f};
  _targetPath = {};
  _ghostStatus = GHOST_STATUS_NORMAL;
  _lives = 10;
  _currentPoint = map.computeGridPosition(_sprite.getPosition());
  _parentPoint = {-444, -444};
  _macPosition = {-90.0f, -90.0f};

  _sprite.setTexture(&_texture);
  _sprite.setTextureRect(sf::IntRect(5 * ppc, ppc, ppc, ppc));
}

Ghost::~Ghost() {}

GameStatus Ghost::update() {
  Point mac = map.computeGridPositionCentered(_macPosition);
  Point current = map.computeGridPositionCentered(_sprite.getPosition());
  Point target = map.computeGridPositionCentered(_targetPosition);

  /* sprite speed */
  switch(_ghostStatus) {
  case GHOST_STATUS_FRIGHTENED:
	setSpriteSpeed(44.0f);
	_sprite.setTextureRect(sf::IntRect(5 * ppc, 2 * ppc, ppc, ppc));
	break;

  default:
	setSpriteSpeed(78.0f);
	_sprite.setTextureRect(sf::IntRect(5 * ppc, ppc, ppc, ppc));
  }

  /* macman and ghost collision */
  if (mac - current < 1) {
	if (_ghostStatus == GHOST_STATUS_FRIGHTENED) {
	  if (_lives > 0) {
		setSpritePosition(_spritePosition);
		
		_targetPath = {};
		_queuedDirection = {0.0f, 0.0f};
		_parentPoint = {-444, -444};
		_ghostStatus = GHOST_STATUS_NORMAL;
		_lives--;
	  }

	  return GAME_ONGOING;
	}

	else {
	  /* return GAME_OVER; */
	  return GAME_OVER;
	}
  }

  if (_targetPath.empty()) {
	/* TODO: use std::queue */
	_targetPath = map.computePath(current, target, _parentPoint);
	current.print();
  }
  
  Point subtarget = _targetPath.back();
  sf::Vector2f direction = current << subtarget;
  
  if (current == subtarget) {
	/* Note path array is ordered from {goal, ... , start} */ 
	_targetPath.pop_back(); 
  }

  if (!(_currentPoint == current))
	_parentPoint = _currentPoint;
  _currentPoint = current;
  
  this->setSpriteDirection(direction);
  
  return GAME_ONGOING;
}

bool Ghost::isActive() {
  return _lives > 0;
}

void Ghost::setTargetPosition(sf::Vector2f targetPosition) {
  if (_targetPosition != targetPosition) {
	_targetPosition = targetPosition;
	_targetPath = {};  /* empty path will trigger path recomputation */
  }
}

void Ghost::setMacPosition(sf::Vector2f position) {
  _macPosition = position;
}

void Ghost::setMacStatus(int status) {
  if (status == MAC_STATUS_OBESE) {
	_ghostStatus = GHOST_STATUS_FRIGHTENED;
  }
}

sf::Vector2f Ghost::getTargetPosition() {
  return sf::Vector2f(0.0f,0.0f);
}
