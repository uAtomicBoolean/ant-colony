#include "gui/gui.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace gui {
    void init(sim::Simulateur *s) {

        // Objects
        std::vector<sf::Sprite> boxShapeList;

        // Textures
        sf::Texture textureFourmiOuvriere;
        sf::Texture textureFourmiSoldat;
        sf::Texture textureFourmiEclaireur;
        sf::Texture textureFourmiReine;
        sf::Texture textureFourmiEsclavagiste;
        sf::Texture textureVide;
        sf::Texture textureObstacle;
        sf::Texture textureColonie;
        sf::Texture textureNourriture;

        // Constants
        int component_size = 600;
        int sprite_size = component_size / sim::consts::DIMENSION_CARTE_X;

        sf::RenderWindow window(sf::VideoMode(component_size * 2, component_size), "Ant Colony!");
        sf::View view = window.getDefaultView();
        view.setCenter(sf::Vector2f(component_size / 2.99f, component_size / 2.85f));
        view.zoom(0.05f);
        window.setView(view);

        sf::RectangleShape sideMenu;
        sideMenu.setFillColor(sf::Color::White);
        sideMenu.setSize(sf::Vector2f(component_size, component_size));
        sideMenu.setPosition(sf::Vector2f(component_size, 0));

        textureFourmiOuvriere.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/ouvriere.png");
        textureFourmiSoldat.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/soldat.png");
        textureFourmiEclaireur.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/eclaireur.png");
        textureFourmiReine.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/reine.png");
        textureFourmiEsclavagiste.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/esclavagiste.png");
        textureVide.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/vide.png");
        textureObstacle.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/obstacle.png");
        textureColonie.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/colonie.png");
        textureNourriture.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/nourriture.png");

        for (int i = 0; i < sim::consts::DIMENSION_CARTE_X; i++) {
            for (int j = 0; j < sim::consts::DIMENSION_CARTE_Y; j++) {
                sim::carte::TypeCase c = s->get_carte()->get_case(i, j)->get_type();
                sf::Sprite sprite;
                // set color
//                sprite.setTexture(textureVide);
                std::cout << c << std::endl;
                switch (c) {
                    case sim::carte::VIDE:
                        sprite.setTexture(textureVide);
                        break;
                    case sim::carte::OBSTACLE:
                        sprite.setTexture(textureObstacle);
                        break;
                    case sim::carte::COLONIE:
                        sprite.setTexture(textureColonie);
                        break;
                    case sim::carte::NOURRITURE:
                        sprite.setTexture(textureNourriture);
                        break;
                }

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                view.zoom(1.01f);
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                view.zoom(0.99f);
                window.setView(view);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                view.move(0, -0.5);
                window.setView(view);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view.move(0, 0.5);
                window.setView(view);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                view.move(-0.5, 0);
                window.setView(view);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view.move(0.5, 0);
                window.setView(view);
            }
            window.display();
        }
    }

    void render(sim::Simulateur *s) {

    }
}