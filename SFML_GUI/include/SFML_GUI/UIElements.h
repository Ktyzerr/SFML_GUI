#pragma once
#include <SFML/Graphics.hpp>

class UIElement {
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(sf::RenderWindow& window, const sf::Event& event) = 0;

	bool isVisible() { return visible; }
	bool isActive() { return active; }

	void setVisible(bool v) { visible = v; }
	void setActive(bool a) { active = a; }

	virtual ~UIElement() {}
private:
	bool active = true;
	bool visible = true;
};