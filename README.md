# SFML_GUI (v0.1-alpha)

A lightweight, modern, and hierarchical UI library built for **SFML 3.0.2+**. 
This library provides a flexible way to create nested interfaces using a dedicated `UIManager` and `Panel` system.

## 🚀 Key Features

* **SFML 3.0 Core**: Fully compatible with the latest SFML 3 features (new event system, `std::optional`, etc.).
* **Nested Hierarchy**: Use `Panel` widgets as containers. Each panel has its own `sf::View`, allowing for isolated coordinate systems and easy clipping.
* **Adaptive Text**: Buttons and Input fields automatically calculate font size and scale to fit their bounds perfectly.
* **Smart Event Propagation**: The `UIManager` handles hover, focus, and click events, distributing them down the widget tree.
* **C++20 Ready**: Built using modern C++ standards for clean and efficient code.

## 📂 Project Structure

```text
SFML_GUI/
├── SFML_GUI/              # Library source code
│   ├── include/           # Headers (.h)
│   └── src/               # Implementation (.cpp)
├── examples/              # Usage examples
│   └── main.cpp           # Demo application
├── CMakeLists.txt         # Root CMake configuration
├── CMakePresets.json      # Local build presets (ignored by git)
└── README.md              # You are here!
```
#🛠 Prerequisites
Compiler: C++20 compatible (MSVC 2022, GCC 11+, Clang 12+).

Framework: SFML 3.0.2 or higher.

Build System: CMake 3.25+.

#💻 Quick Start
Here is a simple example of how to create a UI with a panel and buttons:

```cpp
#include <SFML_GUI/UIManager.h>
#include <SFML_GUI/widgets/widgets.hpp>

// ... inside your main loop ...
UIManager manager(window);

// Create a container panel
auto* panel = manager.add<Panel>(sf::Vector2f(500, 400), sf::Vector2f(50, 50));

// Add widgets inside the panel
auto* btn = panel->add<Button>("Click Me", sf::Vector2f(120, 40), sf::Vector2f(20, 20));

// Event handling (SFML 3 style)
while (const std::optional event = window.pollEvent()) {
    manager.update(*event); 
}

// Drawing
window.clear();
manager.draw();
window.display();
```
#⚙️ Building the Project.

Clone the repository:

```bash
git clone [https://github.com/Ktyzerr/SFML_GUI.git](https://github.com/YOUR_USERNAME/SFML_GUI.git)
cd SFML_GUI
```
Configure with CMake:
If SFML is not in your standard system path, provide it via SFML_DIR:
```Bash
cmake -B build -DSFML_DIR="C:/path/to/SFML/lib/cmake/SFML"
```
Build:

```Bash
cmake --build build
```
📄 License
This project is licensed under the MIT License.
