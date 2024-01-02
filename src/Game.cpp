#include "Game.hpp"

GameOverState::GameOverState(StateManager& state, AudioManager& audio, sf::RenderWindow& win, int score)
  : state(state), audio(audio), window(win), deltaTime(0.0f), score(score) {
	
  font.loadFromFile(FONT_MASTER_PATH);
};

void GameOverState::enter() {
  title.setFont(font);
  title.setString(GAMEOVER_MENU_TITLE);
  title.setCharacterSize(25);
  title.setFillColor(sf::Color::White);
  title.setStyle(sf::Text::Bold | sf::Text::Underlined);

  subtitle.setFont(font);
  subtitle.setString(GAMEOVER_MENU_SUBTITLE);
  subtitle.setCharacterSize(18);
  subtitle.setFillColor(sf::Color::White);

  scoreBoard.setFont(font);
  scoreBoard.setString(std::string(SCORE_TITLE_LONG) + std::to_string(score));
  scoreBoard.setCharacterSize(12);
  scoreBoard.setFillColor(sf::Color::White);

  sf::FloatRect titleBounds = title.getLocalBounds();
  sf::FloatRect subtitleBounds = subtitle.getLocalBounds();
  sf::FloatRect scoreBounds = scoreBoard.getLocalBounds();

  float winX = window.getSize().x;
  float winY = window.getSize().y;
	
  title.setPosition((winX - titleBounds.width) / 2, winY * 0.25f);
  scoreBoard.setPosition((winX - scoreBounds.width) / 2, winY * 0.35f);
  subtitle.setPosition((winX - subtitleBounds.width) / 2, winY * 0.75f);
}

void GameOverState::exit() {}

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

void GameOverState::draw() {
  window.draw(title);
  window.draw(subtitle);
  window.draw(scoreBoard);
}

GameOnState::GameOnState(StateManager& state, AudioManager& audio, sf::RenderWindow& win)
  : state(state),
	audio(audio),
	window(win),
	  
	macMap(MapDefault, 19, 25),
	macMan(macMap.getMacInitPosition(), macMap, audio),
	  
	redGhost(Red, sf::Vector2f(225.0f, 175.0f), macMap, audio),
	blueGhost(Blue, sf::Vector2f(250.0f, 225.0f), macMap, audio),
	orangeGhost(Orange, sf::Vector2f(225.0f, 225.0f), macMap, audio),
	pinkGhost(Pink, sf::Vector2f(200.0f, 225.0f), macMap, audio)
{
  //ghostList = {&orangeGhost};
  ghostList = {&redGhost, &blueGhost, &orangeGhost, &pinkGhost};
}

void GameOnState::enter() {
  font.loadFromFile(FONT_MASTER_PATH);
  
  macMan.bindObserver(&redGhost);
  macMan.bindObserver(&blueGhost);
  macMan.bindObserver(&orangeGhost);
  macMan.bindObserver(&pinkGhost);

  scoreTitle.setString(SCORE_TITLE);
  scoreTitle.setStyle(sf::Text::Bold);
  scoreTitle.setFont(font);
  scoreTitle.setCharacterSize(16);
  scoreTitle.setFillColor(sf::Color::White);

  scoreValue.setString(SCORE_VALUE);
  scoreValue.setFillColor(sf::Color::White);
  scoreValue.setFont(font);
  scoreValue.setCharacterSize(16);
  scoreValue.setStyle(sf::Text::Bold);

  scoreTitle.setPosition(5.0f, window.getSize().y - 25.0f);
  scoreValue.setPosition(75.0f, window.getSize().y - 25.0f);
}

void GameOnState::exit() {}

void GameOnState::ghostStatusHandler(GameStatus status) {
  switch (status) {
  case GAME_ONGOING:
	break;

  case GAME_OVER:
	state.pushState(new GameOverState(state, audio, window, macMan.getScore()));
	break;
  }
}

void GameOnState::update(float dt) {
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

void GameOnState::draw() {
  macMap.drawMap(window);
  macMan.draw(window);
	
  for (auto gIt = ghostList.begin(); gIt != ghostList.end(); gIt++) {
	if ((*gIt)->isActive()) {
	  (*gIt)->draw(window);
	}
  }

  scoreValue.setString(std::to_string(macMan.getScore()));

  window.draw(scoreValue);
  window.draw(scoreTitle);
}

MenuState::MenuState(StateManager& state, AudioManager& audio, sf::RenderWindow& win)
  : state(state), audio(audio), window(win), deltaTime(0.0f) {
  
  font.loadFromFile(FONT_MASTER_PATH);
};

void MenuState::enter() {
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

  audio.playLoop(AUDIO_MENU);
}

void MenuState::exit() {}

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
		audio.stop(AUDIO_MENU);
		audio.play(AUDIO_GAME_START);
		state.changeState(new GameOnState(state, audio, window));
		break;
	  }
	}
  }
}

void MenuState::draw() {
  window.draw(title);
  window.draw(subtitle);
}
