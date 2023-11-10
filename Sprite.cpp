#include "Sprite.hpp"
#include "Common.hpp"

RectSprite::RectSprite(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& gameMap): map(gameMap) {

  _sprite = sf::RectangleShape(sf::Vector2f(spriteWidth, spriteWidth));
  _spritePosition = spriteInitPosition;
  _spriteSpeed = spriteSpeed;

  _currentDirection = sf::Vector2f(0.0f, 0.0f);
  _queuedDirection = sf::Vector2f(0.0f, 0.0f);

  _sprite.setPosition(_spritePosition);  
}

RectSprite::~RectSprite() {}

void RectSprite::draw(sf::RenderWindow& window) {
	window.draw(_sprite);
}

void RectSprite::moveSprite() {
  
  // queued direction is non-empty
  if (_queuedDirection.x + _queuedDirection.y != 0.0f) {
	GameCell targetCell = getNeighboringCell(_queuedDirection);
	
	sf::Vector2f spritePos = _sprite.getPosition();
	sf::Vector2f targetPos = getNeighboringCellCoordinates(_queuedDirection);

	sf::Vector2f spritePosOrigin(spritePos.x + 12.5f, spritePos.y + 12.5f);
	sf::Vector2f targetPosOrigin(targetPos.x + 12.5f, targetPos.y + 12.5f);
   

	float dist = distanceVector2(spritePosOrigin, targetPosOrigin);

	/*
	  direction change is possible

	  - targetCell is not a wall
	  - sprite is within a threshold (.01) amount of proximity
	 */
	if (targetCell == None) {
	  
	  // dot product: perpendicular direction change evaluation
	  float perp = _queuedDirection.x * _currentDirection.x + _queuedDirection.y * _currentDirection.y;

	  std::cout << "perp " << perp << "\n";
	 
	  if (perp == 0.0f && std::abs(dist - 25.0f) < .01f) {
		_currentDirection = _queuedDirection;

		float dx = std::round(spritePos.x / 25.0f) * 25.0f;
		float dy = std::round(spritePos.y / 25.0f) * 25.0f;

		_sprite.setPosition(dx, dy);

		_queuedDirection = sf::Vector2f(0.0f, 0.0f);
	  }

	  else if (perp != 0.0f) {
		_currentDirection = _queuedDirection;
		_queuedDirection = sf::Vector2f(0.0f, 0.0f);
	  }
	}
  }
  
  _sprite.move(
			   _currentDirection.x * _spriteSpeed,
			   _currentDirection.y * _spriteSpeed
			   );

  checkCollision();
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

void RectSprite::checkCollision() {
  GameCell targetCell = getNeighboringCell(_currentDirection);
  sf::Vector2f spritePosition = _sprite.getPosition();

  if (targetCell == Wall) {

	sf::Vector2f wallPosition = getNeighboringCellCoordinates(_currentDirection);

	if (distanceVector2(wallPosition, spritePosition) < 25.0f) {
	  float dx = std::round(spritePosition.x / 25.0f) * 25.0f;
	  float dy = std::round(spritePosition.y / 25.0f) * 25.0f;


	  _sprite.setPosition(dx, dy);

	  // std::cout << "Direction: " << _currentDirection.x << ", " << _currentDirection.y << "\n";
	  // std::cout << "Corrected Position: " << dx << ", " << dy << "\n";
	  // std::cout << "Wall Position: " << wallPosition.x << ", " << wallPosition.y << "\n";
	  }
	
  }
}

GameCell RectSprite::getNeighboringCell(sf::Vector2f direction) {
  sf::Vector2f cellCoordinates = getNeighboringCellCoordinates(direction);

  /*
	x=0       x=n
	+---------+ y=0
	|         |
	|         |
	+---------+ y=m
   */
  
  return map.getCellAt(cellCoordinates.y / 25.0f, cellCoordinates.x / 25.0f);
}

sf::Vector2f RectSprite::getNeighboringCellCoordinates(sf::Vector2f direction) {
  sf::Vector2f spritePos = _sprite.getPosition();
  sf::Vector2f coord(-1.0f, -1.0f);

  int targetCellRow = std::floor((spritePos.y + 12.5f) / 25.0f);
  int targetCellCol = std::floor((spritePos.x + 12.5f) / 25.0f);
	
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

  coord.x = targetCellCol * 25.0f;
  coord.y = targetCellRow * 25.0f;

  return coord;
}
