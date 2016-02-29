#include "Game.hpp"

Game::Game()
	:mWindow(sf::VideoMode(640, 480), "Snake") {
	// some start initialization
}

void Game::run() {

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {

		proccessEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			proccessEvents();
			update(TimePerFrame);
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
	// to do
}

void Game::render() {
	mWindow.clear();
	// Draw all Sprites
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	switch (key) {
	case sf::Keyboard::W :
		break;
	case sf::Keyboard::S :
		break;
	case sf::Keyboard::A :
		break;
	case sf::Keyboard::D :
		break;
	}
}