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

  Mac(sf::Vector2f spriteInitPosition, Map& map, AudioManager& audio);
   
  ~Mac();

  void update();

  int getScore();

  void bindObserver(Ghost* ghostPointer);

private:
  void signalStatus();
  void signalPosition();

private:
  std::vector<Ghost*> _observers;
  
  sf::Texture _texture;

  Point _previousCheckPoint;

  int _status;
  int _score;
};
