#pragma once

#include <string>
#include <iostream>

enum GameCell {
  Wall,
  Dot,
  None,
  Undefined,
};

const std::string MapDefault =
  "0000000000000000000"
  "0        0        0"
  "0 00 000 0 000 00 0"
  "0                 0"
  "0 00 0 00000 0 00 0"
  "0    0   0   0    0"
  "0000 000 0 000 0000"
  "   0 0       0 0   "
  "0000 0 00 00 0 0000"
  "       0   0       "
  "0000 0 00000 0 0000"
  "   0 0       0 0   "
  "0000 0 00000 0 0000"
  "0        0        0"
  "0 00 000 0 000 00 0"
  "0  0     @     0  0"
  "00 0 0 00000 0 0 00"
  "0    0   0   0    0"
  "0 000000 0 000000 0"
  "0                 0"
  "0000000000000000000";

const std::string MapDebug =
  "0000000000000000000"
  "0                 0"
  "0 00 000   000 00 0"
  "0                 0"
  "0                 0"
  "0                 0"
  "0                 0"
  "0                 0"
  "0                 0"
  "0                 0"
  "0                 0"
  "0 000000000       0"
  "0                 0"
  "0                 0"
  "0                 0"
  "0        @        0"
  "0                 0"
  "0                 0"
  "0 000000   000000 0"
  "0                 0"
  "0000000000000000000";

template<typename T>
float distanceVector2(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {
  float dx = std::abs(v2.x - v1.x);
  float dy = std::abs(v2.y - v1.y);
  
  return std::sqrt(dx * dx + dy * dy);
}
