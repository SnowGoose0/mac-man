#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Sprite.hpp"
#include "State.hpp"
#include "Mac.hpp"
#include "Ghost.hpp"
#include "Common.hpp"

class MenuState : public GameState {
public:
  MenuState(StateManager& state, sf::RenderWindow& win);
  void enter() override;
  void exit() override;
  void update(float dt) override;
  void draw() override;

private:
  StateManager& state;
  sf::RenderWindow& window;
  float deltaTime;
  sf::Text title;
  sf::Text subtitle;
  sf::Font font;
};

class GameOverState : public GameState {
public:
  GameOverState(StateManager& state, sf::RenderWindow& win);
  void enter() override;
  void exit() override;
  void update(float dt) override;
  void draw() override;

private:
  StateManager& state;
  sf::RenderWindow& window;
  float deltaTime;
  sf::Text title;
  sf::Text subtitle;
  sf::Font font;
};

class GameOnState : public GameState {
public:
  GameOnState(StateManager& state, sf::RenderWindow& win);
  void enter() override;
  void exit() override;
  void update(float dt) override;
  void draw() override;

  void ghostStatusHandler(GameStatus status);

private:
  float deltaTime;
  StateManager& state;
  sf::RenderWindow& window;
  Map macMap;
  Mac macMan;
  Ghost redGhost;
  Ghost blueGhost;
  Ghost orangeGhost;
  Ghost pinkGhost;
  
  std::vector<Ghost*> ghostList;
  sf::Vector2f playerPrevPosition, playerDirection;
};
