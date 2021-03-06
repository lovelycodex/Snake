#include "Snake.hpp"

Snake::Snake(int l_blockSize)
	: _size(l_blockSize){
	_bodyRect.setSize(sf::Vector2f(_size - 1, _size - 1));
	reset();
}

Snake::~Snake() {}

void Snake::reset() {
	_snakeBody.clear();

	_snakeBody.push_back(SnakeSegment(5, 7));
	_snakeBody.push_back(SnakeSegment(5, 6));
	_snakeBody.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);

	_speed = 15;
	_lives = 3;
	_score = 0;
	_lost  = false;
}

void Snake::setDirection(Direction direction) {
	_direction = direction;
}

Direction Snake::getDirection() {
	if (_snakeBody.size() <= 1) return Direction::None;

	const SnakeSegment &head = _snakeBody[0];
	const SnakeSegment &neck = _snakeBody[1];

	if (head.position.x == neck.position.x) {
		return head.position.y > neck.position.y ? Direction::Down : Direction::Up;
	}
	else if(head.position.y == head.position.y) {
		return head.position.x > neck.position.x ? Direction::Right : Direction::Left;
	}
}

int Snake::getSpeed() {
	return _speed;
}

int Snake::getLives() {
	return _lives;
}

int Snake::getScore() {
	return _score;
}

void Snake::increaseScore() {
	_score += 10;
}

bool Snake::hasLost() {
	return _lost;
}

sf::Vector2i Snake::getPosition() {
	return (!_snakeBody.empty() ?
		_snakeBody.front().position : sf::Vector2i(1, 1));
}

void Snake::lose() {
	_lost = true;
}

void Snake::toogleLost() {
	_lost = !_lost;
}

void Snake::extend() {
	if (_snakeBody.empty()) return;

	SnakeSegment &tailHead = _snakeBody[_snakeBody.size() - 1];

	if (_snakeBody.size() > 1) {
		SnakeSegment &tailBone = _snakeBody[_snakeBody.size() - 2];

		if (tailBone.position.x == tailHead.position.x) {
			if (tailHead.position.y > tailBone.position.y) {
				_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			}
			else {
				_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
			}
		}
		else if (tailBone.position.y == tailHead.position.y) {
			if (tailHead.position.x > tailBone.position.y) {
				_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			}
			else {
				_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
			}
		}
	}
	else {
		switch (_direction) {
		case Direction::Up :
			_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			break;
		case Direction::Right :
			_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
			break;
		case Direction::Left :
			_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			break;
		case Direction::Down :
			_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
			break;
		}
	}
}

void Snake::move() {
	for (int i = _snakeBody.size() - 1; i > 0; i--) {
		_snakeBody[i].position = _snakeBody[i - 1].position;
	}

	switch (_direction) {
	case Direction::Up :
		--_snakeBody[0].position.y;
		break;
	case Direction::Down :
		++_snakeBody[0].position.y;
		break;
	case Direction::Right :
		++_snakeBody[0].position.x;
		break;
	case Direction::Left :
		--_snakeBody[0].position.x;
	}
}

void Snake::checkCollision() {
	if (_snakeBody.size() < 5) return;

	SnakeSegment &head = _snakeBody.front();

	for (auto itr = _snakeBody.begin() + 1; itr != _snakeBody.end(); ++itr) {
		if (itr->position == head.position) {
			int segments = _snakeBody.end() - itr;
			cut(segments);
			break;
		}
	}
}

void Snake::cut(int segment) {
	for (int i = 0; i < segment; ++i) {
		_snakeBody.pop_back();
	}

	--_lives;

	if (!_lives) {
		lose();
		return;
	}
}

void Snake::tick() {
	if (_snakeBody.empty()) return;
	if (_direction == Direction::None) return;
	
	move();
	checkCollision();
}

void Snake::render(sf::RenderWindow &window) {
	if (_snakeBody.empty()) return;

	auto head = _snakeBody.begin();
	_bodyRect.setFillColor(sf::Color::Yellow);
	_bodyRect.setPosition(head->position.x * _size, head->position.y * _size);
	window.draw(_bodyRect);

	for (auto itr = _snakeBody.begin() + 1; itr != _snakeBody.end(); ++itr) {
		_bodyRect.setFillColor(sf::Color::Green);
		_bodyRect.setPosition(itr->position.x * _size, itr->position.y * _size);

		window.draw(_bodyRect);
	}
}

bool Snake::checkCollisionWithNewItem(sf::Vector2i &item) {
	for (auto itr : _snakeBody) {
		if (itr.position == item)
			return true;
	}
	return false;
}