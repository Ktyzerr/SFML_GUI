#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_GUI/widgets/Container.h"

class Panel : public Container {
public:
    Panel(sf::Vector2f size, sf::Vector2f pos) {
        rectSize = size;
        rectPosition = pos;

        background.setSize(size);
        background.setPosition(pos);
        background.setFillColor(sf::Color(50, 50, 50));
        background.setOutlineThickness(1.f);
    }
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::View panelView;
    sf::RectangleShape background;
    sf::Vector2f rectSize;
    sf::Vector2f rectPosition;
};