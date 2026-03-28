#include <SFML/Graphics.hpp>
#include "SFML_GUI/UIManager.h"
#include "SFML_GUI/UIElements.h"

void UIManager::update(const sf::Event& event) {
	for (std::unique_ptr<UIElement>& el : elements) {
		if (el->isActive()) {
			el->update(this->window, event);
		}
	}
}

void UIManager::draw() {
	for (std::unique_ptr<UIElement>& el : elements) {
		if (el->isVisible()) {
			el->draw(this->window);
		}
	}
}