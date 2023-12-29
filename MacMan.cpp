#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include "Common.hpp"
#include "Animation.hpp"
#include "Algorithm.hpp"
#include "Map.hpp"
#include "Sprite.hpp"
#include "Mac.hpp"
#include "Ghost.hpp"
#include "State.hpp"
#include "Game.hpp"

int main(void) {
  sf::Clock clock;
  sf::RenderWindow window(sf::VideoMode(475, 525), "MacMan", sf::Style::Close | sf::Style::Titlebar);

  StateManager s = StateManager(window);
  
  float dt = 0.0f;

  window.setKeyRepeatEnabled(false);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

  s.pushState(new MenuState(s, window));

  while(window.isOpen()) {
	dt = clock.restart().asSeconds();
	
	s.update(dt);
	s.draw();

	/* fps */
	std::cout <<
	  1000000.0f / clock.getElapsedTime().asMicroseconds()
			  << std::endl;
  }

  return 0;
}
