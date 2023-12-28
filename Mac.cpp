#include "Mac.hpp"

Mac::Mac(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _texture.loadFromFile("./assets/map.png");
  _palletCount = 0;
  _previousCheckPoint = map.computeGridPositionCentered(spriteInitPosition);
  _observers = {};

  int ppc = 32;
  _sprite.setTexture(&_texture);
  _sprite.setTextureRect(sf::IntRect(2 * ppc, ppc, ppc ,ppc));
}

Mac::~Mac() {}

void Mac::update() {
  Point current = map.computeGridPositionCentered(_sprite.getPosition());	
  GameCell currentCell = map.getCellAt(current.y, current.x);

  if (currentCell == Snack || currentCell == BigMac) {
	map.updateCellAt(current.y, current.x, None);	
	_palletCount++;

	if (currentCell == BigMac) {
	  
	}
  }

  if (current - _previousCheckPoint >= 1) {
	notifyObservers();
	_previousCheckPoint = current;
  }
}

void Mac::bindObserver(Ghost* observer) {
  _observers.push_back(observer); 
}

void Mac::notifyObservers() {
  for (int i = 0; i < _observers.size(); ++i) {
	_observers[i]->setMacPosition(_sprite.getPosition());
  }
}

