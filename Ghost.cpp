#include "Ghost.hpp"

Ghost::Ghost(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _targetPosition = sf::Vector2f(0.0f, 0.0f);
}

Ghost::~Ghost() {}

void Ghost::update() {
  // if ghost is at intersection

  // ghost will move randomly for now

  sf::Vector2f newDirection(0.0f, 0.0f);

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> dist(1, 4);
  std::uniform_int_distribution<> distx(1, 100);

  int c = dist(gen);
  int b = distx(gen);
 
  if (b > 3) {
	return;
  }

  switch(c) {
  case 1:
	newDirection.x = 1.0f;
	break;
  case 2:
	newDirection.y = 1.0f;
	break;
  case 3:
	newDirection.x = -1.0f;
	break;
  case 4:
	newDirection.y = -1.0f;
	break;
  }

  // test if new direction choice is antiparallel
  // note: normVector2 takes the 2-norm
  // (a * b) / (|a| * |b|) = cosx = -1;
  // abort if true
  float dot = dotVector2(_currentDirection, newDirection);
  float nc = normVector2(_currentDirection);
  float nn = normVector2(newDirection);
  
  if (dot / (nc * nn) == -1.0f) {
	return;
  }
  
  this->setSpriteDirection(newDirection);
}

void Ghost::setTargetPosition(sf::Vector2f targetPosition) {
  
}

void Ghost::setTargetPosition(float x, float y) {
  sf::Vector2f tmp(x, y);  
  Ghost::setTargetPosition(tmp);
}

sf::Vector2f Ghost::getTargetPosition() {
  return sf::Vector2f(0.0f,0.0f);
}
