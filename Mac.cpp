#include "Mac.hpp"

Mac::Mac(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _palletCount = 0;
  _previousCheckPoint = map.computeGridPositionCentered(spriteInitPosition);
  _observers = {};
}

Mac::~Mac() {}

void Mac::update() {
  Point current = map.computeGridPositionCentered(_sprite.getPosition());	
  GameCell currentCell = map.getCellAt(current.y, current.x);

  if (currentCell == Snack) {
	map.updateCellAt(current.y, current.x, None);	
	_palletCount++;
  }

  if (current - _previousCheckPoint >= 1) {
	std::cout << "Checkpoint Updated\n";
	notifyObservers();
	_previousCheckPoint = current;
  }
}

void Mac::bindObserver(Ghost* ghostPointer) {
  _observers.push_back(ghostPointer);
}

void Mac::notifyObservers() {
  for (int i = 0; i < _observers.size(); ++i) {
	_observers[i]->setTargetPosition(_sprite.getPosition());
  }
}

