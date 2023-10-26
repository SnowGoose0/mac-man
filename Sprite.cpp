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

	int targetCellRow = std::floor(spritePos.y / 25);
	int targetCellCol = std::floor(spritePos.x / 25);
	
	if (_queuedDirection.x == 1) { // right
	  targetCellCol++; 
	}

	else if (_queuedDirection.x == -1) { // left
	  targetCellCol--;
	}

	else if (_queuedDirection.y == 1) { // down
	  targetCellRow++;
	}

	else if (_queuedDirection.y == -1) { // up
	  targetCellRow--;
	}

	GameCell targetCell = m.getCellAt(targetCellRow, targetCellCol);

	std::cout << targetCellRow << "\n";

	float dist = distanceVector2(
									 m.computeCellPos(targetCellCol, targetCellRow),
									 spritePos
									 );

	// std::cout << std::abs(dist - 25.0f) << "\n";

	if (targetCell == None
		&&
		std::abs(dist - 25.0f) < .01f) {

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

  std::cout << _sprite.getPosition().y << "\n";
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
