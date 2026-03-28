#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "SFML_GUI/UIElements.h"
#include "SFML_GUI/style/FontManager.h"
#include "SFML_GUI/widgets/Button.h"

Button::Button() : text(FontManager::getInstance().getFont()) {
	text.setString("text");
	text.setFillColor(style.idleTextColor);
	rect.setSize(sf::Vector2f(100.f, 50.f));
	rect.setPosition(sf::Vector2f(0.f, 0.f));
	rect.setFillColor(style.idleFillColor);
	rect.setOutlineThickness(style.borderThickness);
	rect.setOutlineColor(style.idleBorderColor);

	setCenterTextPosition();
}

void Button::update(sf::RenderWindow& window, const sf::Event& event) {
	if (isActive()) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mouseCoords = window.mapPixelToCoords(mousePos, window.getView());
		if (rect.getGlobalBounds().contains(mouseCoords)) {
			styleState = ButtonStyleState::HOVER;
		}
		else {
			styleState = ButtonStyleState::IDLE;
		}

		if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePressed->button == sf::Mouse::Button::Left) {
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView());
				if (rect.getGlobalBounds().contains(mousePos)) {
					styleState = ButtonStyleState::ACTIVE;
					if (onClick) {
						onClick();
					}
				}
			}
		}

		updateStyle();
	}
}
void Button::draw(sf::RenderWindow& window) {
	if (isVisible()) {
		window.draw(rect);
		window.draw(text);
	}
}

void Button::setButtonText(std::string t_string) {
	text.setString(t_string);
}
void Button::setButtonSize(sf::Vector2f _size) {
	size = _size;
	rect.setSize(_size);
	setCenterTextPosition();
}
void Button::setButtonPosition(sf::Vector2f _position) {
	position = _position;
	rect.setPosition(_position);
	setCenterTextPosition();
}

void Button::setCenterTextPosition() {
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin({
		textBounds.position.x + textBounds.size.x / 2.0f,
		textBounds.position.y + textBounds.size.y / 2.0f
		});
	text.setPosition({
		position.x + size.x / 2.0f,
		position.y + size.y / 2.0f
		});

}

void Button::updateStyle() {
	switch (styleState) {
	case ButtonStyleState::IDLE:
		rect.setFillColor(style.idleFillColor);
		rect.setOutlineColor(style.idleBorderColor);
		text.setFillColor(style.idleTextColor);
		break;
	case ButtonStyleState::HOVER:
		rect.setFillColor(style.hoverFillColor);
		rect.setOutlineColor(style.hoverBorderColor);
		text.setFillColor(style.hoverTextColor);
		break;
	case ButtonStyleState::ACTIVE:
		rect.setFillColor(style.activeFillColor);
		rect.setOutlineColor(style.activeBorderColor);
		text.setFillColor(style.activeTextColor);
		break;
	}
}

void Button::adaptFontSize() {
	const float verticalPaddingFactor = 0.5f;
	unsigned int newCharSize = static_cast<unsigned int>(size.y * verticalPaddingFactor);

	if (newCharSize < 12) newCharSize = 12;

	text.setCharacterSize(newCharSize);
	setCenterTextPosition();
}