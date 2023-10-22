#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include "Common.hpp"
#include "Animation.hpp"
#include "Map.hpp"


template<typename T>
float distanceVector2(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {
  float dx = std::abs(v2.x - v1.x);
  float dy = std::abs(v2.y - v1.y);
  
  return std::sqrt(dx * dx + dy * dy);
}

int main() {
  float playerSpeedFactor = 0.0075f;
  float deltaTime = 0.0f;

  sf::Vector2f playerPrevPosition(0.0f, 0.0f);
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

  window.setKeyRepeatEnabled(false);
  
  player.setTexture(&ghost, true);
  player.setPosition(pacMap.getMacInitPosition());
  playerPrevPosition = pacMap.getMacInitPosition();

  while (window.isOpen()) {

	deltaTime = clock.restart().asSeconds();
	
	sf::Event event;
	
	while(window.pollEvent(event)) {

	  if (event.type == sf::Event::Closed) {
		window.close();
	  }

	  else if (event.type == sf::Event::KeyPressed) {

		int keyCode = event.key.code;

		if (keyCode == sf::Keyboard::Key::W ||
			keyCode == sf::Keyboard::Key::A ||
			keyCode == sf::Keyboard::Key::S ||
			keyCode == sf::Keyboard::Key::D) {		  

		  playerPrevDirection = playerDirection;
		  playerPrevPosition = player.getPosition();

		}

		switch (keyCode) {
		case sf::Keyboard::Key::W:
		  playerDirection = sf::Vector2f(0.0f, -1.0f * playerSpeedFactor);
		  break;

		case sf::Keyboard::Key::A:
		  playerDirection = sf::Vector2f(-1.0f * playerSpeedFactor, 0.0f);
		  break;
	
		case sf::Keyboard::Key::S:
		  playerDirection = sf::Vector2f(0.0f, 1.0f * playerSpeedFactor);
		  break;
	
		case sf::Keyboard::Key::D:
		  playerDirection = sf::Vector2f(1.0f * playerSpeedFactor, 0.0f);
		  break;
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
	  
	  if (distanceVector2(macPosition, playerPrevPosition) < 0.05) {
		/*
		  This indicates that player tried to change directions while against a wall in such direction

		  Revert to previously travelling direction

		*/
		playerDirection = playerPrevDirection;
		
		playerPrevDirection = sf::Vector2f(0.0f, 0.0f);
	  }

	}
	
	window.draw(player); // draw to back buffer
	
	pacMap.drawMap(window);

	window.display(); // swap front back buffers 

	window.clear(sf::Color::Black); // clear back buffer
  }

  return 0;
}
