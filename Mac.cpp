#include "Mac.hpp"

Mac::Mac(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m)
    : RectSprite(spriteWidth, spriteInitPosition, spriteSpeed, m) {
}

Mac::~Mac() {}

void Mac::update() {
  sf::Vector2f currentPosition = _sprite.getPosition();
  // offset by half the cell width to so it will only be eaten when macman is at the centre of the pallet
  unsigned int mapX = (currentPosition.y + 12.5f) / 25.0f
  unsigned int mapY = (currentPosition.x + 12.5f) / 25.0f;
	
  GameCell currentCell = map.getCellAt(mapX, mapY);

  if (currentCell == Snack) {
	map.updateCellAt(mapX, mapY, None);
  }
}

