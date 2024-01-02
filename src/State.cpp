#include "State.hpp"

StateManager::StateManager(sf::RenderWindow& win) : window(win) {}

void StateManager::pushState(GameState* state) {
  state->enter();
  states.push(state);
}

void StateManager::popState() {
  if (states.empty())
    return;

  GameState* obsoleteState = states.top();
  states.pop();
  delete obsoleteState;
}

void StateManager::changeState(GameState* state) {
  popState();
  pushState(state);
}

void StateManager::update(float dt) {
  states.top()->update(dt);
}

void StateManager::draw() {
  states.top()->draw();

  window.display();
  window.clear(sf::Color::Black);
}
