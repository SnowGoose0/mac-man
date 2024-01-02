#pragma once

#include <string>
#include <cmath>
#include <iostream>

#define FONT_MASTER_PATH 			"./fonts/jb-mono.ttf"
#define TEXTURE_MASTER_PATH			"./images/map.png"

#define MENU_TITLE 					"Welcome to MacMan"
#define MENU_SUBTITLE 				"Press SPACE to begin (ESC to quit)"
#define GAMEOVER_MENU_TITLE 		"Game Over"
#define GAMEOVER_MENU_SUBTITLE 		"ESC to quit"
#define SCORE_TITLE					"SCORE:"
#define SCORE_VALUE					"000000"

enum GameCell {
  Wall,
  GhostWall,
  House,
  Snack,
  BigMac,
  None,
  Undefined,
};

const std::string MapDefault =
  "0000000000000000000"
  "0********0********0"
  "0M00*000*0*000*00M0"
  "0*****************0"
  "0*00*0*00000*0*00*0"
  "0****0***0***0****0"
  "0000*000 0 000*0000"
  "   0*0*******0*0   "
  "0000*0 00 00 0*0000"
  "   #*  0%%%0  *#   "
  "0000*0 00000 0*0000"
  "   0*0*******0*0   "
  "0000*0*00000*0*0000"
  "0********0********0"
  "0*00*000*0*000*00*0"
  "0M*0*****@*****0*M0"
  "00*0*0*00000*0*0*00"
  "0****0***0***0****0"
  "0*000000*0*000000*0"
  "0*****************0"
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

const std::string MapDebugNoSnack =
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

template<typename T>
float distanceVector2(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {
  float dx = std::abs(v2.x - v1.x);
  float dy = std::abs(v2.y - v1.y);
  
  return std::sqrt(dx * dx + dy * dy);
}

template<typename T>
float dotVector2(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
float normVector2(const sf::Vector2<T>& v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}
