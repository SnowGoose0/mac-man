#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "Sprite.hpp"
#include "State.hpp"
#include "Audio.hpp"
#include "Mac.hpp"
#include "Ghost.hpp"
#include "Common.hpp"

class MenuState : public GameState {
public:
  MenuState(StateManager& state, AudioManager& audio, sf::RenderWindow& win);
  void enter() override;
  void exit() override;
  void update(float dt) override;
  void draw() override;

private:
  StateManager& state;
  AudioManager& audio;
  sf::RenderWindow& window;
  float deltaTime;
  sf::Text title;
  sf::Text subtitle;
  sf::Font font;
};

class GameOverState : public GameState {
public:
  GameOverState(StateManager& state, AudioManager& audio, sf::RenderWindow& win, int score);
  void enter() override;
  void exit() override;
  void update(float dt) override;
  void draw() override;

private:
  StateManager& state;
  AudioManager& audio;
  sf::RenderWindow& window;
  int score;
  float deltaTime;
  sf::Text title;
  sf::Text subtitle;
  sf::Text scoreBoard;
  sf::Font font;
};

class GameOnState : public GameState {
public:
  GameOnState(StateManager& state, AudioManager& audio, sf::RenderWindow& win);
  void enter() override;
  void exit() override;
  void update(float dt) override;
  void draw() override;

  void ghostStatusHandler(GameStatus status);

private:
  float deltaTime;
  StateManager& state;
  AudioManager& audio;
  sf::RenderWindow& window;
  sf::Text scoreTitle;
  sf::Text scoreValue;
  sf::Font font;
  
  Map macMap;
  Mac macMan;
  Ghost redGhost;
  Ghost blueGhost;
  Ghost orangeGhost;
  Ghost pinkGhost;
  
  std::vector<Ghost*> ghostList;
  sf::Vector2f playerPrevPosition, playerDirection;
};
