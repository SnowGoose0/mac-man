#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Sprite.hpp"
#include "Common.hpp"

class Mac : public RectSprite {

public:

  Mac(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m);
   
  ~Mac();

  void update();

private:

};
