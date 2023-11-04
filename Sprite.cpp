#include "Sprite.hpp"
#include "Common.hpp"

RectSprite::RectSprite(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed) {

  _sprite = sf::RectangleShape(sf::Vector2f(spriteWidth, spriteWidth));
  _spritePosition = spriteInitPosition;
  _spriteSpeed = spriteSpeed;

  _currentDirection = sf::Vector2f(0.0f, 0.0f);
  _queuedDirection = sf::Vector2f(0.0f, 0.0f);

  _sprite.setPosition(_spritePosition);

  std::cout << "SETGUP\n" << _spriteSpeed;
  
}

RectSprite::~RectSprite() {}

void RectSprite::moveSprite(Map m) {
  
  // queued direction is non-empty
  if (_queuedDirection.x + _queuedDirection.y != 0.0f) {
	sf::Vector2f spritePos = _sprite.getPosition();
	sf::Vector2f target = getNeighboringCellCoordinates(_queuedDirection);
	
	GameCell targetCell = getNeighboringCell(_queuedDirection, m);

	float dist = distanceVector2(m.computeCellPos(target.x, target.y), spritePos);

	/*
	  direction change is possible

	  - targetCell is not a wall
	  - sprite is within a threshold (.01) amount of proximity
	 */
	if (targetCell == None && std::abs(dist - 25.0f) < .01f) {
	  _currentDirection = _queuedDirection;

	  _sprite.setPosition(std::floor(spritePos.x), std::floor(spritePos.y));

	  _queuedDirection.x = 0.0f;
	  _queuedDirection.y = 0.0f;
	}
  }
  
  _sprite.move(
			   _currentDirection.x * _spriteSpeed,
			   _currentDirection.y * _spriteSpeed
			   );

  handleCollision(m);
}

sf::RectangleShape RectSprite::getSprite() {
  return _sprite;
}

void RectSprite::setSpritePosition(sf::Vector2f spriteOffset) {
  _sprite.setPosition(spriteOffset);
}

void RectSprite::setSpriteDirection(sf::Vector2f direction) {
  if (direction == _currentDirection) return;
  
  _queuedDirection = direction;
}

void RectSprite::setSpriteTexture(std::string path) {
  _spriteTexture.loadFromFile(path);
  _sprite.setTexture(&_spriteTexture, true);
}

void RectSprite::handleCollision(Map m) {
  GameCell targetCell = getNeighboringCell(_currentDirection, m);
  sf::Vector2f spritePosition = _sprite.getPosition();

  if (targetCell == Wall) {

	sf::Vector2f wallPosition = getNeighboringCellCoordinates(_currentDirection);

	// float dx = (25.0f - std::abs(spritePosition.x - (25.0f * wallPosition.x)));
	// float dy = (25.0f - std::abs(spritePosition.y - (25.0f * wallPosition.y)));

	// TODO ROUND TO NEAREST CELL WIDTH MULTIPLE
	float dx = std::floor(_spritePosition.x - _currentDirection.x);	
	float dy = std::floor(_spritePosition.y - _currentDirection.y);

	// TODO: ceil or floor depends on direction of travel. should do it that way instead

	// if (_currentDirection.x != 0.0f) {
	//   _sprite.setPosition(dx, _spritePosition.y);
	// }

	// else if (_currentDirection.y != 0.0f) {
	//   _sprite.setPosition(_spritePosition.x, dy);
	// }
  }
}

GameCell RectSprite::getNeighboringCell(sf::Vector2f direction, Map m) {
  sf::Vector2f cellCoordinates = getNeighboringCellCoordinates(direction);

  /*
	x=0       x=n
	+---------+ y=0
	|         |
	|         |
	+---------+ y=m
   */
  
  return m.getCellAt(cellCoordinates.y, cellCoordinates.x);
}

sf::Vector2f RectSprite::getNeighboringCellCoordinates(sf::Vector2f direction) {
  sf::Vector2f spritePos = _sprite.getPosition();
  sf::Vector2f coord(-1.0f, -1.0f);

  int targetCellRow = std::floor(spritePos.y / 25);
  int targetCellCol = std::floor(spritePos.x / 25);
	
  if (direction.x == 1) { // right
	targetCellCol++; 
  }

  else if (direction.x == -1) { // left
	targetCellCol--;
  }

  else if (direction.y == 1) { // down
	targetCellRow++;
  }

  else if (direction.y == -1) { // up
	targetCellRow--;
  }

  coord.x = targetCellCol;
  coord.y = targetCellRow;

  return coord;
}
