#include <SFML_GUI/widgets/Input.h>
#include <SFML/Graphics.hpp>

void Input::update(sf::RenderWindow& window, const sf::Event& event) {
	if (isActive()) {

		if (currentState == InputState::ACTIVE) {
			if (const auto* textEvent = event.getIf<sf::Event::TextEntered>()) {
				uint32_t unicode = textEvent->unicode;
				sf::String str = text.getString();


				if (unicode == 8) { 
					if (cursorIndex > 0 && !str.isEmpty()) {
						str.erase(cursorIndex - 1, 1);
						text.setString(str);
						cursorIndex--; 
					}
				}
				else if (unicode == 13 || unicode == 10) { 
					currentState = InputState::HOVER;
				}
				else if (unicode >= 32) {
					str.insert(cursorIndex, static_cast<char32_t>(unicode));
					text.setString(str);
					cursorIndex++;
				}
			}
			if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->code == sf::Keyboard::Key::Left) {
					if (cursorIndex > 0) cursorIndex--;
				}
				else if (keyPressed->code == sf::Keyboard::Key::Right) {
					if (cursorIndex < text.getString().getSize()) cursorIndex++;
				}
				updateCursorPosition();
				showCursor = true;
				cursorClock.restart();
			}
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mouseCoords = window.mapPixelToCoords(mousePos, window.getView());
		if (currentState != InputState::ACTIVE) {
			if (rect.getGlobalBounds().contains(mouseCoords)) {
				currentState = InputState::HOVER;
			}
			else {
				currentState = InputState::IDLE;
			}
		}

		if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePressed->button == sf::Mouse::Button::Left) {
				if (rect.getGlobalBounds().contains(mouseCoords)) {
					currentState = InputState::ACTIVE;
				}
				else {
					currentState = InputState::IDLE;
				}
			}
		}

		if (currentState == InputState::ACTIVE) {
			if (cursorClock.getElapsedTime().asMilliseconds() > 500) {
				showCursor = !showCursor;
				cursorClock.restart();
			}
			updateCursorPosition();
		}
		else {
			showCursor = false;
		}

		updateStyle();
	}
}

void Input::draw(sf::RenderWindow& window) {
	if (!isVisible()) return;

	window.draw(rect);

	sf::View oldView = window.getView();
	float paddingX = 10.f;

	sf::Vector2f visibleSize = { rectSize.x - (paddingX * 2.f), rectSize.y };
	sf::View textView;
	textView.setSize(visibleSize);

	sf::Vector2i screenPos = window.mapCoordsToPixel(rectPosition, oldView);
	sf::Vector2f winSize = sf::Vector2f(window.getSize());

	textView.setViewport(sf::FloatRect(
		{ (static_cast<float>(screenPos.x) + paddingX) / winSize.x,
		static_cast<float>(screenPos.y) / winSize.y },
		{ visibleSize.x / winSize.x,
		visibleSize.y / winSize.y }
	));

	float textWidth = text.getGlobalBounds().size.x;

	if (textWidth > visibleSize.x) {
		textView.setCenter({ textWidth - (visibleSize.x / 2.f), visibleSize.y / 2.f });
	}
	else {
		textView.setCenter({ visibleSize.x / 2.f, visibleSize.y / 2.f });
	}

	window.setView(textView);

	if (text.getString().isEmpty()) {
		window.draw(placeholder);
	}
	else {
		window.draw(text);
	}

	if (showCursor && currentState == InputState::ACTIVE) {
		window.draw(cursor);
	}

	window.setView(oldView); 
}

void Input::alignText() {
	float charSize = static_cast<float>(text.getCharacterSize());

	text.setOrigin({ 0.f, charSize / 2.0f });
	text.setPosition({ 0.f, rectSize.y / 2.0f });

	placeholder.setOrigin({ 0.f, charSize / 2.0f });
	placeholder.setPosition({ 0.f, rectSize.y / 2.0f });
}

void Input::updateStyle() {
	switch (currentState) {
	case InputState::IDLE:
		rect.setFillColor(style.idleFillColor);
		rect.setOutlineColor(style.idleBorderColor);
		text.setFillColor(style.idleTextColor);
		break;
	case InputState::HOVER:
		rect.setFillColor(style.hoverFillColor);
		rect.setOutlineColor(style.hoverBorderColor);
		text.setFillColor(style.hoverTextColor);
		break;
	case InputState::ACTIVE:
		rect.setFillColor(style.activeFillColor);
		rect.setOutlineColor(style.activeBorderColor);
		text.setFillColor(style.activeTextColor);
		break;
	}
}

void Input::setPlaceholder(std::string text) {
	placeholder.setString(text);
}

void Input::updateCursorPosition() {
	size_t charCount = text.getString().getSize();
	sf::Vector2f pos = text.findCharacterPos(cursorIndex);

	cursor.setPosition({ pos.x, rectSize.y / 2.0f });
	cursor.setOrigin({ 0.f, cursor.getSize().y / 2.0f });
}

std::string Input::getText() {
	return text.getString();
}

void Input::adaptFontSize() {
	const float verticalPaddingFactor = 0.6f;
	unsigned int newCharSize = static_cast<unsigned int>(rectSize.y * verticalPaddingFactor);

	if (newCharSize < 10) newCharSize = 10;

	text.setCharacterSize(newCharSize);
	placeholder.setCharacterSize(newCharSize);
	cursor.setSize({ 2.f, static_cast<float>(newCharSize) * 1.2f });
	alignText();
}