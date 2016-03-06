#include "World.hpp"

World::World(sf::Vector2u windowSize)
	:_windowSize(windowSize)
	, _blockSize(16) {
	respawnApple();
	_appleShape.setFillColor(sf::Color::Red);
	_appleShape.setRadius(_blockSize / 2);

	for (int i = 0; i < 4; ++i) {
		_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)) {
			_bounds[i].setSize(sf::Vector2f(_windowSize.x, _blockSize));
		}
		else {
			_bounds[i].setSize(sf::Vector2f(_blockSize, _windowSize.y));
		}
		if (i < 2) {
			_bounds[i].setPosition(0, 0);
		}
		else {
			_bounds[i].setOrigin(_bounds[i].getSize());
			_bounds[i].setPosition(sf::Vector2f(_windowSize));
		}
	}
}

World::~World() {}

void World::respawnApple() {
	int maxX = (_windowSize.x / _blockSize) - 2;
	int maxY = (_windowSize.y / _blockSize) - 2;

	_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);

	_appleShape.setPosition(_item.x * _blockSize, _item.y * _blockSize);
}
void World::update(Snake &player) {
	if (player.getPosition() == _item) {
		player.extend();
		player.increaseScore();
		respawnApple();
	}

	int gridSizeX = _windowSize.x / _blockSize;
	int gridSizeY = _windowSize.y / _blockSize;

	if (player.getPosition().x <= 0
		|| player.getPosition().y <= 0
		|| player.getPosition().x >= gridSizeX - 1
		|| player.getPosition().y >= gridSizeY - 1) {

		player.lose();
	}
}

void World::render(sf::RenderWindow &window) {
	for (int i = 0; i < 4; ++i) {
		window.draw(_bounds[i]);
	}
	window.draw(_appleShape);
}

int World::getBlockSize() {
	return _blockSize;
}