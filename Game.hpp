#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Sprite.hpp"
#include "Game.hpp"

class GameOverState : public GameState {

public:
  GameOverState(StateManager& state, sf::RenderWindow& win)
	: state(state), window(win), deltaTime(0.0f) {
	
	font.loadFromFile("./assets/fonts/jb-mono.ttf");
  };

  void enter() override {
	title.setFont(font);
	title.setString("Game Over");
	title.setCharacterSize(25);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	subtitle.setFont(font);
	subtitle.setString("ESC to quit");
 	subtitle.setCharacterSize(12);
	subtitle.setFillColor(sf::Color::White);

	sf::FloatRect titleBounds = title.getLocalBounds();
	sf::FloatRect subtitleBounds = subtitle.getLocalBounds();

	float winX = window.getSize().x;
	float winY = window.getSize().y;
	
	title.setPosition((winX - titleBounds.width) / 2, winY * 0.25f);
	subtitle.setPosition((winX - subtitleBounds.width) / 2, winY * 0.75f);
  }

  void exit() override {}

  void update(float dt) {
	sf::Event event;
	
	deltaTime = dt;

	while(window.pollEvent(event)) {

	  if (event.type == sf::Event::Closed) {
		window.close();
	  }

	  else if (event.type == sf::Event::KeyPressed) {
		int keyCode = event.key.code;

		switch (keyCode) {
		case sf::Keyboard::Key::Escape:
		  window.close();
		  break;
		}
	  }
	  
	}
  }

  void draw() override {
	window.draw(title);
	window.draw(subtitle);
  }

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
  GameOnState(StateManager& state, sf::RenderWindow& win)
    : state(state),
      window(win),
      macMap(MapDefault, 19, 25),
      macMan(25.0f, macMap.getMacInitPosition(), defaultSpeed, macMap),
      g(25.0f, sf::Vector2f(50.0f, 25.0f), defaultSpeed, macMap) {

	ghostList.push_back(&g);
  }

  void enter() override {
	ghostTexture.loadFromFile("./assets/ghost.jpg");
	macMan.bindObserver(&g);
  }

  void exit() override {}

  void ghostStatusHandler(GameStatus status) {
	switch (status) {
	case GAME_ONGOING:
	  break;

	case GAME_OVER:
	  state.pushState(new GameOverState(state, window));
	  break;
	}
  }

  void update(float dt) override {
	sf::Event event;
	
	deltaTime = dt;

	while(window.pollEvent(event)) {

	  if (event.type == sf::Event::Closed) {
		window.close();
	  }

	  else if (event.type == sf::Event::KeyPressed) {
		int keyCode = event.key.code;

		switch (keyCode) {
		case sf::Keyboard::Key::W:
		  playerDirection = sf::Vector2f(0.0f, -1.0f);
		  break;

		case sf::Keyboard::Key::A:
		  playerDirection = sf::Vector2f(-1.0f, 0.0f);
		  break;
	
		case sf::Keyboard::Key::S:
		  playerDirection = sf::Vector2f(0.0f, 1.0f);
		  break;
	
		case sf::Keyboard::Key::D:
		  playerDirection = sf::Vector2f(1.0f, 0.0f);
		  break;
		}
	  }
	}

	GameStatus status = GAME_ONGOING;

	macMan.setSpriteDirection(playerDirection);
	macMan.moveSprite(deltaTime);
	macMan.update();

	for (auto gIt = ghostList.begin(); gIt != ghostList.end(); gIt++) {
	  if (!(*gIt)->isActive) continue;
	  
	  (*gIt)->moveSprite(deltaTime); 
	  ghostStatusHandler((*gIt)->update());
	}

	//g.moveSprite(deltaTime);
	//status = g.update();
	//ghostStatusHandler(status);
  }

  void draw() override {
	macMap.drawMap(window);
	macMan.draw(window);


	for (auto gIt = ghostList.begin(); gIt != ghostList.end(); gIt++) {
	  if ((*gIt)->isActive) {
		(*gIt)->draw(window);
	  }
	}
	
  }

private:
  // TODO
  const float defaultSpeed = 88.0f;
  float deltaTime;
  
  StateManager& state;
  sf::RenderWindow& window;

  Map macMap;
  
  Mac macMan;
  Ghost g;
  std::vector<Ghost*> ghostList;
  
  sf::Texture ghostTexture;
  sf::Vector2f playerPrevPosition, playerDirection;
};


class MenuState : public GameState {

public:
  MenuState(StateManager& state, sf::RenderWindow& win)
	: state(state), window(win), deltaTime(0.0f) {
	
	font.loadFromFile("./assets/fonts/jb-mono.ttf");
  };

  void enter() override {
	title.setFont(font);
	title.setString("Welcome to MacMan");
	title.setCharacterSize(25);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	subtitle.setFont(font);
	subtitle.setString("Press SPACE to begin (ESC to quit)");
 	subtitle.setCharacterSize(12);
	subtitle.setFillColor(sf::Color::White);

	sf::FloatRect titleBounds = title.getLocalBounds();
	sf::FloatRect subtitleBounds = subtitle.getLocalBounds();

	float winX = window.getSize().x;
	float winY = window.getSize().y;
	
	title.setPosition((winX - titleBounds.width) / 2, winY * 0.25f);
	subtitle.setPosition((winX - subtitleBounds.width) / 2, winY * 0.75f);
  }

  void exit() override {}

  void update(float dt) {
	sf::Event event;
	
	deltaTime = dt;

	while(window.pollEvent(event)) {

	  if (event.type == sf::Event::Closed) {
		window.close();
	  }

	  else if (event.type == sf::Event::KeyPressed) {
		int keyCode = event.key.code;

		switch (keyCode) {
		case sf::Keyboard::Key::Escape:
		  window.close();
		  break;

		case sf::Keyboard::Key::Space:
		  state.pushState(new GameOnState(state, window));
		  break;
		}
	  }
	}
  }

  void draw() override {
	window.draw(title);
	window.draw(subtitle);
  }

private:
  StateManager& state;
  sf::RenderWindow& window;
  float deltaTime;
  
  sf::Text title;
  sf::Text subtitle;
  sf::Font font;
};
