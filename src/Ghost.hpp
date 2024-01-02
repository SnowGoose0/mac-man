#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <random>

#include "Sprite.hpp"
#include "Algorithm.hpp"
#include "Common.hpp"

enum GhostType {
  Red,
  Blue,
  Pink,
  Orange
};

class Ghost : public RectSprite {

public:

  Ghost(GhostType type, sf::Vector2f spriteInitPosition, Map& map, AudioManager& audio);
  
  ~Ghost();

  GameStatus update();

  bool isActive();

  void setTargetPosition(sf::Vector2f targetPosition);

  void setMacPosition(sf::Vector2f position);
  void setMacStatus(int status);

private:
  void setTargetPosition(float x, float y);

  void updateStatusAttributes();
  void updateDirection(Point current, Point target, Point mac);
  
  sf::Vector2f computeTarget();
  sf::Vector2f computeTargetNormal();
  sf::Vector2f computeTargetPursuit();
  
private:
  GhostType _type;
  int _lives;
  sf::Texture _texture;
  
  sf::Vector2f _targetPosition;
  std::vector<Point> _targetPath;
  
  Point _currentPoint;
  Point _parentPoint;

  int _ghostStatus;
  sf::Vector2f _macPosition;
};
