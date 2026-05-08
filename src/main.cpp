#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // SFML 3: VideoMode now takes a Vector2u (unsigned int) inside curly braces
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Bike Game - SFML 3");
    window.setFramerateLimit(60);

    // A simple shape for your bike
    sf::RectangleShape bike({50.f, 100.f});
    bike.setFillColor(sf::Color(255, 182, 193)); // Pink!
    bike.setPosition({400.f, 300.f});

    while (window.isOpen()) {
        // SFML 3: pollEvent returns a std::optional
        while (const std::optional event = window.pollEvent()) {
            
            // Check if the window was closed
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // SFML 3: Modern way to handle key presses
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }

        // Logic (Movement)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            bike.move({-5.f, 0.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            bike.move({5.f, 0.f});
        }

        // Drawing
        window.clear(sf::Color::White);
        window.draw(bike);
        window.display();
    }

    return 0;
}