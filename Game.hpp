#include <SFML/Graphics.hpp>

#include <iostream>
#include <stack>

class GameState {
public:
  virtual void enter() = 0;
  virtual void exit() = 0;
  virtual void update(float dt) = 0;
  virtual void draw() = 0;
};

class MenuState : public GameState {

public:
  MenuState(sf::RenderWindow& win)
	: window(win), deltaTime(0.0f) {
	
	font.loadFromFile("./assets/fonts/jb-mono.ttf");
  };

  void enter() override {
	title.setFont(font);
	title.setString("Welcome to MacMan");
	title.setCharacterSize(18);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	subtitle.setFont(font);
	subtitle.setString("Press any key to begin");
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

		default:
		  std::cout << "Hello World!" << std::endl;
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
  sf::RenderWindow& window;
  float deltaTime;
  
  sf::Text title;
  sf::Text subtitle;
  sf::Font font;
};

class GameOnState : public GameState {

public:
  GameOnState(sf::RenderWindow& win)
	: window(win), 
	  macMap(MapDefault, 19, 25),
	  macMan(25.0f, macMap.getMacInitPosition(), defaultSpeed, macMap),
	  g(25.0f, sf::Vector2f(50.0f, 25.0f), defaultSpeed, macMap),
	  animation(&ghostTexture, sf::Vector2u(4, 3), 0.3f),
	  defaultSpeed(88.0f) { }

  void enter() override {
	ghostTexture.loadFromFile("./assets/ghost.jpg");
	macMan.bindObserver(&g);
  }

  void exit() override {}

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

	macMan.setSpriteDirection(playerDirection);
	macMan.moveSprite(deltaTime);
	macMan.update();
        
	g.moveSprite(deltaTime);
	g.update();
  }

  void draw() override {
	macMap.drawMap(window);
	macMan.draw(window);
	g.draw(window);
  }

private:
  // TODO
  sf::RenderWindow& window;
  sf::Texture macTexture, ghostTexture;
  float defaultSpeed, deltaTime;
  sf::Vector2f playerPrevPosition, playerDirection;
  Animation animation;
  Map macMap;
  Mac macMan;
  Ghost g;
  
};

class StateManager {
public:

  StateManager(sf::RenderWindow& win) : window(win) {

  }

  ~StateManager() {}
  
  void pushState(GameState* state) {
	if (states.empty()) state->enter();
	
	states.push(state);
  }
  
  void popState() {
	if (states.empty()) return;
	
	GameState* obsoleteState = states.top();
	states.pop();
	delete obsoleteState;

	if (states.empty()) window.close();
  }
  
  void update(float dt) {
	states.top()->update(dt);
  }
  
  void draw() {
	states.top()->draw();
	
	window.display();
	window.clear(sf::Color::Black);
  }

private:
  sf::RenderWindow& window;
  std::stack<GameState*> states;
};
