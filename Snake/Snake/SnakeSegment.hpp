#pragma once

#include <SFML\System\Vector2.hpp>
#include <vector>

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};