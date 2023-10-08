#include <SFML/Graphics.hpp>

#include <iostream>

#include "Common.hpp"
#include "Animation.hpp"
#include "Map.hpp"

int main() {
  float playerDirection[2] = {0.0f, 0.0f};
  float playerSpeedFactor = 0.01f;
  
  sf::RenderWindow window(sf::VideoMode(475, 475), "MacMan", sf::Style::Close | sf::Style::Titlebar);
  
  sf::RectangleShape player(sf::Vector2f(30.0f, 30.0f));
  sf::Texture mac;
  sf::Texture ghost;
  sf::Clock clock; 

  ghost.loadFromFile("./assets/ghost.jpg");
  player.setTexture(&ghost, true);

  Animation animation(&ghost, sf::Vector2u(4, 3), 0.3f);
  Map pacMap(MapDefault, 19, 25);

  float deltaTime = 0.0f;

  while (window.isOpen()) {

	deltaTime = clock.restart().asSeconds();
	
	sf::Event e;
	
	while(window.pollEvent(e)) {

	  switch (e.type) {
		
	  case sf::Event::Closed:
		window.close();
		break;

	  case sf::Event::TextEntered:
		break;
	  } 
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
	  playerDirection[0] = 0.0f;
	  playerDirection[1] = -1.0f * playerSpeedFactor;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
	  playerDirection[0] = -1.0f * playerSpeedFactor;
	  playerDirection[1] = 0.0f;
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
	  playerDirection[0] = 0.0f;
	  playerDirection[1] = 1.0f * playerSpeedFactor;
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
	  playerDirection[0] = 1.0f * playerSpeedFactor;
	  playerDirection[1] = 0.0f;
	}

	animation.Update(0, deltaTime);
	player.setTextureRect(animation.uvRect);
	player.move(playerDirection[0], playerDirection[1]);
	
	window.draw(player); // draw to back buffer
	
	pacMap.drawMap(window);

	window.display(); // swap front back buffers 

	window.clear(sf::Color::Black); // clear back buffer
  }

  return 0;
}
