#include "Map.hpp"

Map::Map(const std::string map, int mapWidth, int cellWidth) {
  this->map = map;
  this->cellWidth = cellWidth;
  this->mapWidth = mapWidth;
};

Map::~Map() {};

void Map::drawMap(sf::RenderWindow& win) {

  int y_offset = -1;
  
  for (int i = 0; i < map.size(); i++) {
	int x_offset = i % mapWidth;
	
	if (x_offset == 0) y_offset++;

	if (map[i] == '0') {
	  sf::RectangleShape cell(sf::Vector2f(cellWidth, cellWidth));

	  cell.setFillColor(sf::Color(0, 0, 255));
	  cell.setPosition(x_offset * cellWidth, y_offset * cellWidth);
	  
	  win.draw(cell);
	}
  }
}
