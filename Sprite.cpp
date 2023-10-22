#include "Sprite.hpp"
#include "Common.hpp"

RectSprite::RectSprite(float spriteWidth, sf::Vector2f spritePosition, float spriteSpeed) {

  _sprite = sf::RectangleShape(sf::Vector2f(spriteWidth, spriteWidth));
  _spritePosition = spritePosition;
  _spriteSpeed = spriteSpeed;

  _currentDirection = sf::Vector2f(0.0f, 0.0f);
  _queuedDirection = sf::Vector2f(0.0f, 0.0f);
  
}

RectSprite::~RectSprite() {}

void RectSprite::moveSprite(Map m) {
  // queued direction is non-empty
  if (_queuedDirection.x + _queuedDirection.y != 0.0f) {
	sf::Vector2f spritePos = _sprite.getPosition();

	GameCell targetCell = Undefined;
	
	if (_queuedDirection.x == 1) { // right
	  targetCell = m.getCellAt(std::floor(spritePos.y), std::floor(spritePos.x) + 1);
	}

	else if (_queuedDirection.x == -1) { // left
	  targetCell = m.getCellAt(std::floor(spritePos.y), std::floor(spritePos.x) - 1);
	}

	else if (_queuedDirection.y == 1) { // down
	  targetCell = m.getCellAt(std::floor(spritePos.y) + 1, std::floor(spritePos.x));
	}

	else if (_queuedDirection.y == -1) { // up
	  targetCell = m.getCellAt(std::floor(spritePos.y) - 1, std::floor(spritePos.x));
	}

	_currentDirection = _queuedDirection;

	_queuedDirection.x = 0.0f;
	_queuedDirection.y = 0.0f;

  }

  _sprite.move(
			   _currentDirection.x * _spriteSpeed,
			   _currentDirection.y * _spriteSpeed
			   );
}

void RectSprite::setSpritePosition(sf::Vector2f spriteOffset) {
  _sprite.setPosition(spriteOffset);
}

void RectSprite::setDirection(sf::Vector2f direction) {
  _queuedDirection = direction;
}

void RectSprite::setSpriteTexture(std::string path) {
  _spriteTexture.loadFromFile(path);
  _sprite.setTexture(&_spriteTexture, true);
}
