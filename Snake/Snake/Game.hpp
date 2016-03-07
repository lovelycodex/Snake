#include <SFML\Graphics.hpp>

#include "World.hpp"
#include "Snake.hpp"
#include "Textbox.hpp"

/// \brief Main game class
class Game {
public:
/**
* \brief Default constructor
*        Set up game window, start player position
*/
	Game();
/**
* \brief Call to start the game from main file
*/
	void run();

private:
/**
* \brief Render all textures to the screen
*/
	void render();
/**
* \brief Updates the game logic
* \param deltaTime Uses for calculate movement speed
*/
	void update(sf::Time deltaTime);
/**
* \brief Handles user input
*/
	void proccessEvents();
/**
* \brief Check which key has been pressed
* \param key Contain the pressed key
* \param isPressed Define key was pressed or released
*/
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
/// \brief Main game window
	sf::RenderWindow mWindow;
	
	World _world;
	Snake _snake;
	Textbox _textbox;
};

