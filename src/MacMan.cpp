#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include "Common.hpp"
#include "Algorithm.hpp"
#include "Audio.hpp"
#include "Map.hpp"
#include "Sprite.hpp"
#include "Mac.hpp"
#include "Ghost.hpp"
#include "State.hpp"
#include "Game.hpp"

int main(void) {
  sf::Clock clock;
  sf::RenderWindow window(sf::VideoMode(475, 550), "MacMan", sf::Style::Close | sf::Style::Titlebar);

  StateManager stateManager = StateManager(window);
  AudioManager audioManager = AudioManager();
  
  float dt = 0.0f;

  window.setKeyRepeatEnabled(false);
  window.setFramerateLimit(120);
  // window.setVerticalSyncEnabled(true);

  stateManager.pushState(new MenuState(stateManager, audioManager, window));

  while(window.isOpen()) {
	dt = clock.restart().asSeconds();
	
	stateManager.update(dt);
	stateManager.draw();

	/* fps logger */
	// std::cout
	//   <<
	//   1000000.0f / clock.getElapsedTime().asMicroseconds()
	//   << std::endl;
  }

  return 0;
}
