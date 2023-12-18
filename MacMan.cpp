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

int main(void) {
  float playerSpeedFactor = 0.0075f;
  float deltaTime = 0.0f;

  sf::Vector2f playerPrevPosition(0.0f, 0.0f);
  sf::Vector2f playerDirection(0.0f, 0.0f);
  
  sf::RenderWindow window(sf::VideoMode(475, 525), "MacMan", sf::Style::Close | sf::Style::Titlebar);
  
  sf::RectangleShape player(sf::Vector2f(25.0f, 25.0f));
  sf::Texture mac;
  sf::Texture ghost;
  sf::Clock clock;

  ghost.loadFromFile("./assets/ghost.jpg");
  
  Animation animation(&ghost, sf::Vector2u(4, 3), 0.3f);
  Map macMap(MapDefault, 19, 25);

  window.setKeyRepeatEnabled(false);

  // RectSprite macMan(25.0f, sf::Vector2f(25.0f, 25.0f), 0.0575f, macMap);

  Mac macMan(25.0f, macMap.getMacInitPosition(), 0.0575f, macMap);
  Ghost g(25.0f, sf::Vector2f(50.0f, 25.0f), 0.0575f, macMap);

  macMan.bindObserver(&g);

  while (window.isOpen()) {
	sf::Event event;

	deltaTime = clock.restart().asSeconds();
	
	while(window.pollEvent(event)) {

	  if (event.type == sf::Event::Closed) {
		window.close();
	  }

	  else if (event.type == sf::Event::KeyPressed) {
		int keyCode = event.key.code;

		switch (keyCode) {
		case sf::Keyboard::Key::W:
		  playerDirection = sf::Vector2f(0.0f, -1.0f);
		  playerPrevPosition = player.getPosition();
		  break;

		case sf::Keyboard::Key::A:
		  playerDirection = sf::Vector2f(-1.0f, 0.0f);
		  playerPrevPosition = player.getPosition();
		  break;
	
		case sf::Keyboard::Key::S:
		  playerDirection = sf::Vector2f(0.0f, 1.0f);
		  playerPrevPosition = player.getPosition();
		  break;
	
		case sf::Keyboard::Key::D:
		  playerDirection = sf::Vector2f(1.0f, 0.0f);
		  playerPrevPosition = player.getPosition();
		  break;
		}
	  }  
	}

	macMap.drawMap(window);

	macMan.setSpriteDirection(playerDirection);
	macMan.moveSprite();
	macMan.update();
	macMan.draw(window);

	g.moveSprite();
	g.update();
	g.draw(window);

	window.display(); // swap front back buffers 
	window.clear(sf::Color::Black); // clear back buffer
  }

  return 0;
}
