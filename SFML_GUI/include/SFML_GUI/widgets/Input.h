#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_GUI/UIElements.h"
#include "SFML_GUI/style/FontManager.h"
#include "SFML_GUI/UIManager.h"

struct InputStyles {
	sf::Color idleFillColor = sf::Color::White;
	sf::Color idleTextColor = sf::Color::Black;
	sf::Color idleBorderColor = sf::Color(60, 60, 60);

	//hover
	sf::Color hoverFillColor = sf::Color::White;
	sf::Color hoverTextColor = sf::Color::Black;
	sf::Color hoverBorderColor = sf::Color(75, 171, 255);

	//onClick
	sf::Color activeFillColor = sf::Color::White;
	sf::Color activeTextColor = sf::Color::Black;
	sf::Color activeBorderColor = sf::Color(60, 60, 60);

	float borderThickness = 2.f;
	float activeBorderThickness = 3.f;
	sf::Color placeHolder = sf::Color(120, 120, 120);
};

class Input : public UIElement {
public:

	Input(sf::Vector2f size, sf::Vector2f position, std::string placeHolder = "") : placeholder(FontManager::getInstance().getFont()),
		text(FontManager::getInstance().getFont())
	{
		rect.setSize(size);
		rectSize = size;
		rect.setPosition(position);
		rectPosition = position;
		rect.setFillColor(style.idleFillColor);
		rect.setOutlineThickness(style.borderThickness);
		rect.setOutlineColor(style.idleBorderColor);
		placeholder.setString(placeHolder);
		placeholder.setFillColor(style.placeHolder);
		text.setFillColor(style.idleTextColor);

		cursor.setSize({ 2.f, rectSize.y * 0.6f });
		cursor.setFillColor(style.idleTextColor);

		adaptFontSize();
		alignText();
	}

	friend class UIManager;
	friend class std::unique_ptr<Input>;
	friend class std::allocator<Input>;

	void setPlaceholder(std::string text);
	std::string getText();

	void update(sf::RenderWindow& window, const sf::Event& event);
	void draw(sf::RenderWindow& window);


	InputStyles style;

private:
	enum class InputState { IDLE, HOVER, ACTIVE };
	InputState currentState = InputState::IDLE;

	sf::RectangleShape rect;
	sf::Vector2f rectPosition;
	sf::Vector2f rectSize;
	sf::Text placeholder;
	sf::Text text;

	sf::RectangleShape cursor;
	sf::Clock cursorClock;
	bool showCursor = false;
	std::size_t cursorIndex = 0;

	void updateCursorPosition();
	void updateStyle();
	void alignText();
	void adaptFontSize();
};