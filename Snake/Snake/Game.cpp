#include "Game.hpp"

Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Snake")
	, _snake(_world.getBlockSize())
	, _world(sf::Vector2u(800, 600)) {
	_textbox.setup(5, 14, 350, sf::Vector2f(255, 0));

	_textbox.add("Hello! This is SNAKE!!!");
}

void Game::run() {

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Time timestep = sf::seconds(1.f / _snake.getSpeed());

	while (mWindow.isOpen()) {

		proccessEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timestep) {
			timeSinceLastUpdate -= timestep;
			proccessEvents();
			update(timestep);
		}

		render();
	}
}

void Game::proccessEvents() {
	sf::Event event;

	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed :
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased :
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed :
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime) {
	_snake.tick();
	_world.update(_snake, _textbox);

	if (_snake.hasLost()) {
		_textbox.clear();
		_textbox.add("Game Over. Total Score:" + std::to_string(_snake.getScore()));
		_snake.reset();
	}
}

void Game::render() {
	mWindow.clear();
	_snake.render(mWindow);
	_world.render(mWindow);
	_textbox.render(mWindow);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	switch (key) {
	case sf::Keyboard::Up :
		if (_snake.getDirection() != Direction::Down)
			_snake.setDirection(Direction::Up);
		break;
	case sf::Keyboard::Down :
		if (_snake.getDirection() != Direction::Up)
			_snake.setDirection(Direction::Down);
		break;
	case sf::Keyboard::Left :
		if (_snake.getDirection() != Direction::Right)
			_snake.setDirection(Direction::Left);
		break;
	case sf::Keyboard::Right :
		if (_snake.getDirection() != Direction::Left)
			_snake.setDirection(Direction::Right);
		break;
	}
}