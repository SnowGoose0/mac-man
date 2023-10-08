#include "Animation.hpp"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float frameDuration) {

  this->imageCount = imageCount;
  this->frameDuration = frameDuration;
  totalDuration = 0.0f;
  currentImage.x = 0;

  uvRect.width = texture->getSize().x / float(imageCount.x);
  uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation() {

}

void Animation::Update(int row, float deltaDuration) {
  currentImage.y = row;
  totalDuration += deltaDuration;

  if (totalDuration >= frameDuration) {
	totalDuration -= frameDuration;
	currentImage.x = (currentImage.x + 1) % imageCount.x;
  }

  uvRect.left = currentImage.x * uvRect.width;
  uvRect.top = currentImage.y * uvRect.width;
}
