#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Map.hpp"
#include "Sprite.hpp"
#include "Ghost.hpp"
#include "Algorithm.hpp"
#include "Common.hpp"

class Mac : public RectSprite {

public:

  Mac(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m);
   
  ~Mac();

  void update();

  void bindObserver(Ghost* ghostPointer);

private:
  void notifyObservers();

private:
  unsigned int _palletCount;

  Point _previousCheckPoint;

  std::vector<Ghost*> _observers;
};
