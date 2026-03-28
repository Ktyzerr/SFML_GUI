#include <SFML/Graphics.hpp>
#include "SFML_GUI/style/FontManager.h"
#include "SFML_GUI/resources/font/DefaultFontData.h"
sf::Font* FontManager::customFont = nullptr;

sf::Font& FontManager::getDefaultFont() {
	static sf::Font font;
	static bool isLoaded = false;

	if (!isLoaded) {
		if (!font.openFromMemory(default_font_data, default_font_size)) {
			throw std::runtime_error("Failed to load embedded font!");
		}
		isLoaded = true;
	}

	return font;
}

sf::Font& FontManager::getFont() {
	if (customFont) { return *customFont; }
	return getDefaultFont();
}

void FontManager::setFont(sf::Font& font) {
	customFont = &font;
}

FontManager& FontManager::getInstance() {
	static FontManager instance;
	return instance;
}