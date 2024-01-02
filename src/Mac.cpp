#include "Mac.hpp"

Mac::Mac(sf::Vector2f spriteInitPosition, Map& map, AudioManager& audio)
  
  : RectSprite(25.0f, spriteInitPosition, 88.0f, map, audio) {
  
  _texture.loadFromFile(TEXTURE_MASTER_PATH);
  _score = 0;
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

	if (currentCell == BigMac) {
	  _sprite.setTextureRect(sf::IntRect(3 * ppc, ppc, ppc ,ppc));
	  _status = MAC_STATUS_OBESE;
	  _timer.restart();
	  _score += 200;
	 
	  signalStatus();
	  
	  audio.play(AUDIO_POWER_UP);
	}

	else {
	  _score += 100;
	  audio.play(AUDIO_EAT_PALLET);
	}

	if (!(_score % 1000)) {
	  audio.play(AUDIO_1000_SCORE);
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

	  audio.play(AUDIO_FULL);
	}
  }
}

int Mac::getScore() {
  return _score;
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
