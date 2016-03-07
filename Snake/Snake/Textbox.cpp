#include "Textbox.hpp"

Textbox::Textbox() {
	setup(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos) {
	setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox() {
	clear();
}

void Textbox::setup(int visible, int charSize, int width, sf::Vector2f screenPos) {
	_numVisible = visible;

	sf::Vector2f offset(2.f, 2.f);

	_font.loadFromFile("arial.ttf");
	_content.setFont(_font);
	_content.setCharacterSize(charSize);
	_content.setColor(sf::Color::White);
	_content.setString("");
	_content.setPosition(screenPos + offset);

	_backdrop.setSize(sf::Vector2f(width, _numVisible * (charSize * 1.2f)));
	_backdrop.setFillColor(sf::Color(90,90,90,90));
	_backdrop.setPosition(screenPos);
}

void Textbox::add(std::string message) {
	_messages.push_back(message);
	if (_messages.size() < 6) return;
	_messages.erase(_messages.begin());
}

void Textbox::clear() {
	_messages.clear();
}

void Textbox::render(sf::RenderWindow &window) {
	std::string content;

	for (auto itr : _messages) {
		content.append(itr + "\n");
	}

	if (content != "") {
		_content.setString(content);
		window.draw(_backdrop);
		window.draw(_content);
	}
}