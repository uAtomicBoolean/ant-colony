#include <iostream>
#include "include/colonie.h"
#include "include/gui.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

/*int main() {
    std::cout << "Oui\n";
    std::cout << simulateur::colonie::test_ac() << "\n";
    std::cout << simulateur::gui::test_gui() << std::endl;
    return 0;
}*/

