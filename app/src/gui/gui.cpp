#include "gui/gui.h"
#include <SFML/Graphics.hpp>

namespace gui {
    void render(sim::Simulateur *s) {
        sf::RenderWindow window(sf::VideoMode(1600, 900), "Ant Colony!");
//        sf::CircleShape shape(100.f);
//        shape.setFillColor(sf::Color::Green);
//
//        while (window.isOpen()) {
//            sf::Event event{};
//            while (window.pollEvent(event)) {
//                if (event.type == sf::Event::Closed)
//                    window.close();
//            }
//
//            window.clear();
//            window.draw(shape);
//            window.display();
//        }

// draw a map with squares of simulateur :: constantes DIMENSION_CARTE_X & DIMENSION_CARTE_Y
// make it a grid

//        for (int i = 0; i < sim::consts::DIMENSION_CARTE_X; i++) {
//            for (int j = 0; j < sim::consts::DIMENSION_CARTE_Y; j++) {
//                sf::RectangleShape rectangle(sf::Vector2f(100, 100));
//                rectangle.setFillColor(sf::Color::Green);
//                rectangle.setPosition(i * 100, j * 100);
//                window.draw(rectangle);
//            }
//        }

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.display();
        }
    }
}