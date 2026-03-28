#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "UIElements.h"
#include "SFML_GUI/style/FontManager.h"

class UIManager {
public:
	UIManager(sf::RenderWindow& window) : window(window), font(FontManager::getInstance().getFont()) {}

	template <typename T, typename... Args>
	T* add(Args&&... args) {
		auto element = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = element.get();
		elements.push_back(std::move(element));
		return ptr;
	}
	void update(const sf::Event& event);
	void draw();
private:
	std::vector<std::unique_ptr<UIElement>> elements;
	sf::RenderWindow& window;
	sf::Font& font;
};