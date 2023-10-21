#include "Sprite.hpp"

RectSprite::RectSprite(float spriteWidth, sf::Vector2f spritePosition unsigned int spriteSpeed) {

  _sprite = sf::RectangleShape s(sf::Vector2f(spriteWidth, spriteWidth));
  _spritePosition = spritePosition;
  _spriteSpeed = spriteSpeed;
  
}

RectSprite::~RectSprite() {}

void RectSprite::moveSprite() {
  _sprite.move(
			   _currentDirection.x * _spriteSpeed,
			   _currentDirection.y * spriteSpeed
			   );

  // queued direction is non-empty
  if (_queuedDirection.x + _queuedDirection.y != 0.0f) {
	sf::Vector2f spritePos = _sprite.getPosition();

	float spritePos
  }
}

void RectSprite::setSpritePosition(sf::Vector2f spriteOffset) {
  _sprite.setPosition(spriteOffset);
}

void RectSprite::setDirection(sf::Vector2f direction) {
  _queuedDirection = direction;
}

void RectSprite::createSpriteTexture(string path) {
  _spriteTexture.loadTexture(path);
}
