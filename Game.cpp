#include "Game.hpp"

GameOverState::GameOverState(StateManager& state, sf::RenderWindow& win)
  : state(state), window(win), deltaTime(0.0f) {
	
  font.loadFromFile("./assets/fonts/jb-mono.ttf");
};

void GameOverState::enter()  {
  title.setFont(font);
  title.setString(GAMEOVER_MENU_TITLE);
  title.setCharacterSize(25);
  title.setFillColor(sf::Color::White);
  title.setStyle(sf::Text::Bold | sf::Text::Underlined);

  subtitle.setFont(font);
  subtitle.setString(GAMEOVER_MENU_SUBTITLE);
  subtitle.setCharacterSize(12);
  subtitle.setFillColor(sf::Color::White);

  sf::FloatRect titleBounds = title.getLocalBounds();
  sf::FloatRect subtitleBounds = subtitle.getLocalBounds();

  float winX = window.getSize().x;
  float winY = window.getSize().y;
	
  title.setPosition((winX - titleBounds.width) / 2, winY * 0.25f);
  subtitle.setPosition((winX - subtitleBounds.width) / 2, winY * 0.75f);
}

void GameOverState::exit()  {}

void GameOverState::update(float dt) {
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

void GameOverState::draw()  {
  window.draw(title);
  window.draw(subtitle);
}

GameOnState::GameOnState(StateManager& state, sf::RenderWindow& win)
  : state(state),
	window(win),
	  
	macMap(MapDefault, 19, 25),
	macMan(macMap.getMacInitPosition(), macMap),
	  
	redGhost(Red, sf::Vector2f(200.0f, 225.0f), macMap),
	blueGhost(Pink, sf::Vector2f(250.0f, 225.0f), macMap)
{
  redGhost.setTargetPosition({-50.0f, 50.0f});
  blueGhost.setTargetPosition({525.0f, 50.0f});
  //ghostList = {&redGhost, &blueGhost};
  ghostList = {&redGhost, &blueGhost};
}

void GameOnState::enter()  {
  macMan.bindObserver(&redGhost);
  macMan.bindObserver(&blueGhost);
}

void GameOnState::exit()  {}

void GameOnState::ghostStatusHandler(GameStatus status) {
  switch (status) {
  case GAME_ONGOING:
	break;

  case GAME_OVER:
	state.pushState(new GameOverState(state, window));
	break;
  }
}

void GameOnState::update(float dt)  {
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
	if ((*gIt)->isActive()) {
	  (*gIt)->moveSprite(deltaTime); 
	  ghostStatusHandler((*gIt)->update());
	}
  }
}

void GameOnState::draw()  {
  macMap.drawMap(window);
  macMan.draw(window);
	
  for (auto gIt = ghostList.begin(); gIt != ghostList.end(); gIt++) {
	if ((*gIt)->isActive()) {
	  (*gIt)->draw(window);
	}
  }

}

MenuState::MenuState(StateManager& state, sf::RenderWindow& win)
  : state(state), window(win), deltaTime(0.0f) {
  font.loadFromFile(FONT_MASTER_PATH);
};

void MenuState::enter()  {
  title.setFont(font);
  title.setString(MENU_TITLE);
  title.setCharacterSize(25);
  title.setFillColor(sf::Color::White);
  title.setStyle(sf::Text::Bold | sf::Text::Underlined);

  subtitle.setFont(font);
  subtitle.setString(MENU_SUBTITLE);
  subtitle.setCharacterSize(12);
  subtitle.setFillColor(sf::Color::White);

  sf::FloatRect titleBounds = title.getLocalBounds();
  sf::FloatRect subtitleBounds = subtitle.getLocalBounds();

  float winX = window.getSize().x;
  float winY = window.getSize().y;
	
  title.setPosition((winX - titleBounds.width) / 2, winY * 0.25f);
  subtitle.setPosition((winX - subtitleBounds.width) / 2, winY * 0.75f);
}

void MenuState::exit()  {}

void MenuState::update(float dt) {
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

void MenuState::draw() {
  window.draw(title);
  window.draw(subtitle);
}
