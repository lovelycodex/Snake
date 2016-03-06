#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

#include "Snake.hpp"

class World {
public:
	World(sf::Vector2u windowSize);
	~World();

	int getBlockSize();

	void respawnApple();
	void update(Snake &player);
	void render(sf::RenderWindow &window);

private:
	sf::Vector2u _windowSize;
	sf::Vector2i _item;
	int _blockSize;

	sf::CircleShape _appleShape;
	sf::RectangleShape _bounds[4];
};