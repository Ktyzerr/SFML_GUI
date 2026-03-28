#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class FontManager {
public:
	sf::Font& getFont();
	void setFont(sf::Font& font);
	static FontManager& getInstance();
private:
	static sf::Font* customFont;

	static sf::Font& getDefaultFont();
};