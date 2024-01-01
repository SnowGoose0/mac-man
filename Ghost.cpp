#include "Ghost.hpp"

Ghost::Ghost(GhostType type, float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _type = type;
  _ghostStatus = GHOST_STATUS_NORMAL;
  _lives = 3;
  _texture.loadFromFile("./assets/map.png");
  _sprite.setTexture(&_texture);
  _sprite.setTextureRect(sf::IntRect(5 * ppc, ppc, ppc, ppc));
  
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
  Point target = map.computeGridPositionCentered(computeTarget());

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

  
  updateStatusAttributes();
  updateDirection(current, target, mac);
  
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

sf::Vector2f Ghost::computeTarget() {
  switch(_ghostStatus) {
  case GHOST_STATUS_FRIGHTENED:
  case GHOST_STATUS_NORMAL:
	return computeTargetNormal();
	break;

  case GHOST_STATUS_PURSUIT:
	return computeTargetPursuit();
	break;
  }

  return {};
}

/* these procedures solely exist to avoid a nested switch statement */
sf::Vector2f Ghost::computeTargetNormal() {
  switch(_type) {
  case Red:
	return {-50.0f, 50.0f};
	break;

  case Blue:
	return {525.0f, 50.0f};
	break;

  case Pink:
	return {-50.0f, 550.0f};
	break;

  case Orange:
	return {525.0f, 550.0f};
	break;
  }

  return {-50.0f, 50.0f};
}

sf::Vector2f Ghost::computeTargetPursuit() {
  /* note: target methods are not exactly the same as the original pacman */
  
  switch (_type) {
  case Red:
	return _macPosition; /* direct target */
	break;

  case Blue:
	return {_macPosition.x + 3.0f, _macPosition.y + 3.0f};
	break;

  case Pink:
	return {_macPosition.x - 3.0f, _macPosition.y - 3.0f};
	break;

  case Orange:
	if (map.computeGridPosition(_macPosition) - _currentPoint < 8) {
	  _macPosition;
	}

	return computeTargetNormal();
	break;
  }

  return {-50.0f, 50.0f};
}

void Ghost::updateStatusAttributes() {
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
}

void Ghost::updateDirection(Point current, Point target, Point mac) {
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
}
