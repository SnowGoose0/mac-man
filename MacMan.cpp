#include <SFML/Graphics.hpp>

#include <iostream>

#include "Common.hpp"
#include "Animation.hpp"
#include "Map.hpp"

int main() {
  float playerSpeedFactor = 0.0075f;

  sf::Vector2f playerPrevDirection(0.0f, 0.0f);
  sf::Vector2f playerDirection(0.0f, 0.0f);
  
  sf::RenderWindow window(sf::VideoMode(475, 525), "MacMan", sf::Style::Close | sf::Style::Titlebar);
  
  sf::RectangleShape player(sf::Vector2f(25.0f, 25.0f));
  sf::Texture mac;
  sf::Texture ghost;
  sf::Clock clock;

  ghost.loadFromFile("./assets/ghost.jpg");
  
  Animation animation(&ghost, sf::Vector2u(4, 3), 0.3f);
  Map pacMap(MapDefault, 19, 25);
  //Map pacMap(MapDebug, 19, 25);

  float deltaTime = 0.0f;

  window.setKeyRepeatEnabled(false);
  
  player.setTexture(&ghost, true);
  player.setPosition(pacMap.getMacInitPosition());

  while (window.isOpen()) {

	deltaTime = clock.restart().asSeconds();
	
	sf::Event event;
	
	while(window.pollEvent(event)) {

	  if (event.type == sf::Event::Closed) {
		window.close();
	  }

	  else if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Key::W) {
		  playerPrevDirection = playerDirection;
		  playerDirection = sf::Vector2f(0.0f, -1.0f * playerSpeedFactor);
		}

		else if (event.key.code== sf::Keyboard::Key::A) {
		  playerPrevDirection = playerDirection;
		  playerDirection = sf::Vector2f(-1.0f * playerSpeedFactor, 0.0f);
		}
	
		else if (event.key.code == sf::Keyboard::Key::S) {
		  playerPrevDirection = playerDirection;
		  playerDirection = sf::Vector2f(0.0f, 1.0f * playerSpeedFactor);
		}
	
		else if (event.key.code == sf::Keyboard::Key::D) {
		  playerPrevDirection = playerDirection;
		  playerDirection = sf::Vector2f(1.0f * playerSpeedFactor, 0.0f);
		}
	  } 

	  
	}

	animation.Update(0, deltaTime);
	player.setTextureRect(animation.uvRect);
	player.move(playerDirection);

	sf::Vector2f macPosition = player.getPosition();
	sf::Vector2f collisionOffset = pacMap.checkSpriteCollision(macPosition);

	if (collisionOffset.x != 0.0f || collisionOffset.y != 0.0f) {

	  if (playerDirection.x == 0.0f) {
		player.move(0.0f, collisionOffset.y);
	  }

	  else if (playerDirection.y == 0.0f) {
		std:: cout << "move " << collisionOffset.x << "\n";
		player.move(collisionOffset.x, 0.0f);
	  }

	  playerDirection = playerPrevDirection;
	  playerPrevDirection = sf::Vector2f(0.0f, 0.0f);

	}
	
	window.draw(player); // draw to back buffer
	
	pacMap.drawMap(window);

	window.display(); // swap front back buffers 

	window.clear(sf::Color::Black); // clear back buffer
  }

  return 0;
}
