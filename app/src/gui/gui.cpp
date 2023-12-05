#include "gui/gui.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace gui {
    void render(sim::Simulateur *s) {
        int component_size = 600;
        int sprite_size = component_size / sim::consts::DIMENSION_CARTE_X;

        sf::RenderWindow window(sf::VideoMode(component_size * 2, component_size), "Ant Colony!");

        sf::View view = window.getDefaultView();
        view.zoom(0.05f);
        view.setCenter(sf::Vector2f(component_size / 2, component_size / 2));
        window.setView(view);

        sf::RectangleShape sideMenu;
        sideMenu.setFillColor(sf::Color::White);
        sideMenu.setSize(sf::Vector2f(component_size, component_size));
        sideMenu.setPosition(sf::Vector2f(component_size, 0));


//        sf::Texture textureGrass;
//        if (!textureGrass.loadFromFile("grass.png")) {
//            // erreur...
//        }
//
//        sf::Texture textureRock;
//        if (!textureRock.loadFromFile("rock.png")) {
//            // erreur...
//        }
//
//        sf::Texture textureFood;
//        if (!textureFood.loadFromFile("food.png")) {
//            // erreur...
//        }
//
//        sf::Texture textureColony;
//        if (!textureColony.loadFromFile("colony.png")) {
//            // erreur...
//        }


        sf::Texture textureFourmi;
        textureFourmi.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/fourmi.png");

        std::vector<sf::Sprite> boxShapeList;
        for (int i = 0; i < sim::consts::DIMENSION_CARTE_X; i++) {
            for (int j = 0; j < sim::consts::DIMENSION_CARTE_Y; j++) {
//                simulateur::carte::TypeCase c = s->get_carte().get_case(i, j).get_type();
                sf::Sprite sprite;
                // set color
                if(i % 2 == 0) {
                    sprite.setTexture(textureFourmi);
                    std::cout << "fourmi" << std::endl;
                }
                else if(i % 2 == 1) {
                    sprite.setColor(sf::Color::White);
                    std::cout << "white" << std::endl;

                }
//                switch (c) {
//                    case simulateur::carte::VIDE:
//                        sprite.setTexture(textureRock);
//                        break;
//                    case simulateur::carte::OBSTACLE:
//                        sprite.setTexture(textureGrass);
//                        break;
//                    case simulateur::carte::COLONIE:
//                        sprite.setTexture(textureColony);
//                        break;
//                    case simulateur::carte::NOURRITURE:
//                        sprite.setTexture(textureFood);
//                        break;
//                }

                // set position
                sprite.setPosition(sf::Vector2f(i * sprite_size, j * sprite_size));
                sprite.setScale(sf::Vector2f(sprite_size / 1000.f, sprite_size / 1000.f));
                boxShapeList.push_back(sprite);

            }
        }

        while (window.isOpen()) {
            std::cout << "render" << std::endl;
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            for (auto &boxShape : boxShapeList) {
                window.draw(boxShape);
            }
            // sf::Mouse::Wheel::VerticalWheel
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                view.zoom(1.01f);
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                view.zoom(0.99f);
                window.setView(view);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                view.move(0, -1);
                window.setView(view);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view.move(0, 1);
                window.setView(view);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                view.move(-1, 0);
                window.setView(view);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view.move(1, 0);
                window.setView(view);
            }
            window.display();
        }
    }
}