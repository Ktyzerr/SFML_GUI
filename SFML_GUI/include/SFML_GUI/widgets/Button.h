#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "SFML_GUI/UIElements.h"
#include "SFML_GUI/style/FontManager.h"
#include "SFML_GUI/UIManager.h"

struct ButtonStyle {
	//idle
	sf::Color idleFillColor = sf::Color(221, 221, 221);
	sf::Color idleTextColor = sf::Color::Black;
	sf::Color idleBorderColor = sf::Color(60, 60, 60);

	//hover
	sf::Color hoverFillColor = sf::Color(177, 255, 243);
	sf::Color hoverTextColor = sf::Color::Black;
	sf::Color hoverBorderColor = sf::Color(75, 171,255);

	//onClick
	sf::Color activeFillColor = sf::Color(116, 190, 255);
	sf::Color activeTextColor = sf::Color::Black;
	sf::Color activeBorderColor = sf::Color(75, 171, 255);

	float borderThickness = 2.f;
};

class Button : public UIElement{
public:

	Button(std::string t_string, sf::Vector2f _size, sf::Vector2f _position) : text(FontManager::getInstance().getFont(), t_string),
		size(_size),
		position(_position)
	{
		//rect
		rect.setFillColor(style.idleFillColor);
		rect.setSize(size);
		rect.setPosition(position);
		rect.setOutlineThickness(style.borderThickness);
		rect.setOutlineColor(style.idleBorderColor);
		//text
		text.setCharacterSize(20);
		text.setFillColor(style.idleTextColor);
		//text position
		sf::FloatRect textBounds = text.getLocalBounds();
		text.setOrigin({
			textBounds.position.x + textBounds.size.x / 2.0f,
			textBounds.position.y + textBounds.size.y / 2.0f
		});
		text.setPosition({
			position.x + size.x / 2.0f,
			position.y + size.y / 2.0f
		});
		adaptFontSize();
	}
	Button();

	using Callback = std::function<void()>;

	friend class UIManager;
	friend class std::unique_ptr<Button>;
	friend class std::allocator<Button>;

	void update(sf::RenderWindow& window, const sf::Event& event) override;
	void draw(sf::RenderWindow& window) override;

	void setButtonText(std::string t_string);
	void setButtonSize(sf::Vector2f _size);
	void setButtonPosition(sf::Vector2f _position);

	template <typename Func, typename... Args>
	void setOnClick(Func&& func, Args&&... args) {
		onClick = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
	}

	ButtonStyle style;

private:
	enum class ButtonStyleState{ IDLE, HOVER, ACTIVE };

	sf::RectangleShape rect;
	sf::Vector2f size;
	sf::Vector2f position;
	Callback onClick;

	sf::Text text;
	sf::Vector2f t_size;
	sf::Vector2f t_position;

	ButtonStyleState styleState = ButtonStyleState::IDLE;

	void setCenterTextPosition();
	void updateStyle();
	void adaptFontSize();
};