#include "SFML_GUI/widgets/Container.h"
#include <SFML/Graphics.hpp>

void Container::update(sf::RenderWindow& window, const sf::Event& event) {
    if (!isVisible()) { return; }
    for (auto& child : children) {
        child->update(window, event);
    }
}

void Container::draw(sf::RenderWindow& window) {
    if (!isVisible()) { return; }
    for (auto& child : children) {
        child->draw(window);
    }
}