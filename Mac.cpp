#include "Mac.hpp"

Mac::Mac(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
  this->_palletCount = 0;
}

Mac::~Mac() {}

void Mac::update() {
  sf::Vector2f currentPosition = _sprite.getPosition();
  // offset by half the cell width to so it will only be eaten when macman is at the centre of the pallet
  unsigned int mapX = (currentPosition.y + 12.5f) / 25.0f;
  unsigned int mapY = (currentPosition.x + 12.5f) / 25.0f;
	
  GameCell currentCell = map.getCellAt(mapX, mapY);

  if (currentCell == Snack) {
	map.updateCellAt(mapX, mapY, None);
	_palletCount++;
	std::cout << _palletCount << "\n";

	if (_palletCount == map.palletCount) {
	  std::cout << "You win!\n";
	}
  }

 mapX = (currentPosition.y) / 25.0f;
mapY = (currentPosition.x) / 25.0f;

  std::cout << "< " << mapX << ", " << mapY << " >\n";

  if (map.getCellAt(mapX + _currentDirection.x, mapY + _currentDirection.y) == None || map.getCellAt(mapX - _currentDirection.x, mapY - _currentDirection.y) == None) {
	// at intersection

	std::cout << "INTERSECTION\n";
  }
  else {
	//	std::cout << "123\n";
  }

}

