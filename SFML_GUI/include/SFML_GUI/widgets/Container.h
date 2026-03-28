#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_GUI/UIElements.h"
#include "SFML_GUI/UIManager.h"
#include <vector>

class Container : public UIElement {
public:
    friend class UIManager;
    friend class std::unique_ptr<Container>;
    friend class std::allocator<Container>;

    template <typename T, typename... Args>
    T* add(Args&&... args) {
        auto element = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = element.get();
        children.push_back(std::move(element));
        return ptr;
    }

    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void draw(sf::RenderWindow& window) override;

protected:
    std::vector<std::unique_ptr<UIElement>> children;
};