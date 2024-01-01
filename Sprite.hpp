#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

#include "Map.hpp"

#define MAC_STATUS_NORMAL 		0
#define MAC_STATUS_OBESE		1
#define MAC_STATUS_FASTAF		2
#define GHOST_STATUS_NORMAL     10
#define GHOST_STATUS_PURSUIT    11
#define GHOST_STATUS_FRIGHTENED 12

enum GameStatus {
  GAME_ONGOING = 	0b00000000,
  GAME_OVER = 		0b00000010
};

class RectSprite {
public:
  static const int ppc = 32;
  static constexpr float obeseTime = 6.50f;
  
public:
  RectSprite(float spriteWidth, sf::Vector2f spriteInitPosition, float spriteSpeed, Map& m);
  ~RectSprite();

  void draw(sf::RenderWindow& window);

  void moveSprite(float deltaTime);

  sf::RectangleShape getSprite();

  void setSpritePosition(sf::Vector2f spriteOffset);

  void setSpriteDirection(sf::Vector2f direction);

  void setSpriteTexture(std::string path);

protected:
  void setSpriteSpeed(float newSpeed);
  
  void checkCollision();

  GameCell getNeighboringCell(sf::Vector2f direction);

  sf::Vector2f getNeighboringCellCoordinates(sf::Vector2f direction);

protected:
  sf::Vector2f _prevDirection;
  sf::Vector2f _currentDirection;
  sf::Vector2f _queuedDirection;

  Map& map;

  sf::Clock _timer;
  sf::RectangleShape _sprite;

  float _spriteSpeed;
  
  sf::Texture _spriteTexture;

  sf::Vector2f _spritePosition;

};
