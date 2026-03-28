#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML_GUI/UIManager.h>
#include <SFML_GUI/widgets/widgets.hpp>

/**
 * Callback function triggered by the button click.
 * @param inp Pointer to the Input widget to access its data.
 */
void click(Input* inp) {
    // Demonstrating inter-widget interaction: 
    // Pulling text from the Input field and printing it to the console.
    std::cout << "Submitted text: " << inp->getText() << std::endl;
}

int main() {
    // 1. Initialize the SFML 3.0 Window.
    // We use the new sf::VideoMode syntax and a descriptive window title.
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML_GUI | Modern UI Example");

    // 2. Initialize the UIManager.
    // It acts as the root controller for all UI elements, handling events and rendering.
    UIManager manager(window);

    // 3. Create a Panel (Container).
    // Parameters: Size (500x550), Global Position (25, 25).
    // Panels use internal sf::View to clip children and manage local coordinates.
    auto* panel = manager.add<Panel>(sf::Vector2f(500, 550), sf::Vector2f(25, 25));

    // 4. Add an Input widget INSIDE the panel.
    // Parameters: Size (300x30), Local Position (10, 10), and a Placeholder.
    // Note: (10, 10) is relative to the Panel's top-left corner, not the window.
    auto* input = panel->add<Input>(sf::Vector2f(300, 30), sf::Vector2f(10, 10), "username");

    // 5. Add a Button widget INSIDE the panel.
    // Parameters: Label string, Size (50x30), Local Position (10, 60).
    auto* button = panel->add<Button>("Login", sf::Vector2f(50, 30), sf::Vector2f(10, 60));

    // 6. Bind the Click event.
    // We pass the function 'click' and the 'input' object as an argument to it.
    button->setOnClick(click, input);

    // --- Main Application Loop ---
    while (window.isOpen()) {

        // SFML 3.0 uses std::optional for event polling.
        while (const std::optional event = window.pollEvent()) {

            // Standard check for window closure.
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // 7. Update UI State.
            // The Manager automatically propagates the event through the hierarchy:
            // Manager -> Panel -> Children (Input, Button).
            // It handles hover effects, focus, and text entry internally.
            manager.update(*event);
        }

        // --- Rendering Stage ---
        // Clear with a dark gray color to make UI elements pop.
        window.clear(sf::Color(30, 30, 30));

        // 8. Draw the UI.
        // This single call handles Z-order, View switching for Panels, 
        // and adaptive text rendering for all registered widgets.
        manager.draw();

        window.display();
    }

    return 0;
}