#pragma once

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

#include "SnakeSegment.hpp"
#include "Direction.hpp"



class Snake {
public:
	Snake(int l_blockSize);
	~Snake();

	bool						hasLost();
	bool						checkCollisionWithNewItem(sf::Vector2i &item);

	void						setDirection(Direction direction);
	void						increaseScore();
	void						lose();
	void						toogleLost();
	void						extend();
	void						reset();
	void						move();
	void						tick();
	void						cut(int segment);
	void						render(sf::RenderWindow &window);

	int							getSpeed();
	int							getLives();
	int							getScore();

	Direction				getDirection();
	sf::Vector2i		getPosition();

private:
	using SnakeContainer = std::vector<SnakeSegment>;

	void								checkCollision();
	
	sf::RectangleShape	_bodyRect;
	SnakeContainer			_snakeBody;
	Direction						_direction;

	int									_size;
	int									_speed;
	int									_lives;
	int									_score;
			
	bool								_lost;
};
