#include "Mac.hpp"

Mac::Mac(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  _texture.loadFromFile("./assets/map.png");
  _palletCount = 0;
  _status = MAC_STATUS_NORMAL;
  _previousCheckPoint = map.computeGridPositionCentered(spriteInitPosition);
  _observers = {};

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
	  _sprite.setTextureRect(sf::IntRect(3 * ppc, ppc, ppc ,ppc));
	  _status = MAC_STATUS_OBESE;
	  _timer.restart();
	  
	  signalStatus(); 	  std::cout << "EAT BIGMAC\n";
	}
  }

  if (current - _previousCheckPoint >= 1) {
	signalPosition();
	_previousCheckPoint = current;
  }
  
  if (_status != MAC_STATUS_NORMAL) {
	float powerUpTimeElapsed = _timer.getElapsedTime().asSeconds();

	if (powerUpTimeElapsed > obeseTime) {
	  _sprite.setTextureRect(sf::IntRect(2 * ppc, ppc, ppc ,ppc));
	  _status = MAC_STATUS_NORMAL;

	  signalStatus();
	}
  }
}

void Mac::bindObserver(Ghost* observer) {
  _observers.push_back(observer); 
}

void Mac::signalStatus() {
  for (int i = 0; i < _observers.size(); i++)
	_observers[i]->setMacStatus(_status);
}

void Mac::signalPosition() {
  for (int i = 0; i < _observers.size(); ++i)
	_observers[i]->setMacPosition(_sprite.getPosition());
}
