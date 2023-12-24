#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <stack>

class GameState {
public:
  virtual void enter() = 0;
  virtual void exit() = 0;
  virtual void update(float dt) = 0;
  virtual void draw() = 0;
};

class StateManager {
public:
  StateManager(sf::RenderWindow& win);

  ~StateManager() {}

  void pushState(GameState* state);
  void popState();
  void update(float dt);
  void draw();

private:
  sf::RenderWindow& window;
  std::stack<GameState*> states;
};

// class StateManager {
// public:

//   StateManager(sf::RenderWindow& win) : window(win) {

//   }

//   ~StateManager() {}
  
//   void pushState(GameState* state) {
// 	if (states.empty()) state->enter();
	
// 	states.push(state);
//   }
  
//   void popState() {
// 	if (states.empty()) return;
	
// 	GameState* obsoleteState = states.top();
// 	states.pop();
// 	delete obsoleteState;

// 	if (states.empty()) window.close();
//   }
  
//   void update(float dt) {
// 	states.top()->update(dt);
//   }
  
//   void draw() {
// 	states.top()->draw();
	
// 	window.display();
// 	window.clear(sf::Color::Black);
//   }

// private:
//   sf::RenderWindow& window;
//   std::stack<GameState*> states;
// };
