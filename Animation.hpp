#pragma once

#include <SFML/Graphics.hpp>

class Animation {
  
public:
  Animation(sf::Texture* texture, sf::Vector2u imageCount, float frameDuration);
  
  ~Animation();

  void Update(int row, float deltaDuration);

public:
  sf::IntRect uvRect;

private:
  sf::Vector2u imageCount;
  
  sf::Vector2u currentImage;

  float totalDuration;
  
  float frameDuration;
};
