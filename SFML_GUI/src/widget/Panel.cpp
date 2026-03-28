#include <SFML/Graphics.hpp>
#include "SFML_GUI/widgets/Panel.h"

void Panel::update(sf::RenderWindow& window, const sf::Event& event) {
    if (!isActive()) return;

    sf::Vector2f winSize = sf::Vector2f(window.getSize());

    panelView.setSize(rectSize);
    panelView.setCenter(rectSize / 2.f);
    panelView.setViewport(sf::Rect<float>(
        { rectPosition.x / winSize.x, rectPosition.y / winSize.y },
        { rectSize.x / winSize.x, rectSize.y / winSize.y }
    ));

    sf::View oldView = window.getView();
    window.setView(panelView);
    Container::update(window, event);
    window.setView(oldView);
}

void Panel::draw(sf::RenderWindow& window) {
    if (!isVisible()) return;

    window.draw(background);

    sf::View oldView = window.getView();
    sf::View panelView;
    panelView.setSize(rectSize);

    sf::Vector2f winSize = sf::Vector2f(window.getSize());
    panelView.setViewport(sf::FloatRect(
        { rectPosition.x / winSize.x, rectPosition.y / winSize.y },
        { rectSize.x / winSize.x, rectSize.y / winSize.y }
    ));

    panelView.setCenter({ rectSize.x / 2.f, rectSize.y / 2.f });

    window.setView(panelView);

    Container::draw(window);

    window.setView(oldView);
}


