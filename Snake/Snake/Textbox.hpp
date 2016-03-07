#pragma once

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

#include<string>

class Textbox {
public:
	Textbox();
	Textbox(int visible, int charSize, int width, sf::Vector2f screenPos);
	~Textbox();

	void setup(int visible, int charSize, int width, sf::Vector2f screenPos);
	void add(std::string message);
	void clear();

	void render(sf::RenderWindow &window);

private:
	using MessageContainer = std::vector<std::string>;
	MessageContainer _messages;
	int _numVisible;

	sf::RectangleShape _backdrop;
	sf::Font _font;
	sf::Text _content;
};