#include "gui/gui.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace gui {
    GUI::GUI() = default;

    void GUI::init() {
        sf::RenderWindow window(sf::VideoMode(gui::GUI::COMPONENT_SIZE * 2, gui::GUI::COMPONENT_SIZE), "Ant Colony!");
        sf::View view = window.getDefaultView();
        view.setCenter(sf::Vector2f(gui::GUI::COMPONENT_SIZE / 2.99f, gui::GUI::COMPONENT_SIZE / 2.85f));
        view.zoom(0.05f);
        window.setView(view);

        sf::RectangleShape sideMenu;
        sideMenu.setFillColor(sf::Color::White);
        sideMenu.setSize(sf::Vector2f(gui::GUI::COMPONENT_SIZE, gui::GUI::COMPONENT_SIZE));
        sideMenu.setPosition(sf::Vector2f(gui::GUI::COMPONENT_SIZE, 0));

        this->textureFourmiOuvriere.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/ouvriere.png");
        this->textureFourmiSoldat.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/soldat.png");
        this->textureFourmiEclaireur.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/eclaireur.png");
        this->textureFourmiReine.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/reine.png");
        this->textureFourmiEsclavagiste.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/esclavagiste.png");
        this->textureVide.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/vide.png");
        this->textureObstacle.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/obstacle.png");
        this->textureColonie.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/colonie.png");
        this->textureNourriture.loadFromFile("/Users/lothaireguee/Documents/ENSI/S7/CPP/ant-colony/app/assets/nourriture.png");

        this->render();

        while (window.isOpen()) {
            std::cout << "render" << std::endl;
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            for (auto &boxShape : this->boxShapeList) {
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

    void GUI::render() {
        sim::Simulateur *s{sim::Simulateur::get_simulateur()};
        for (int i = 0; i < sim::consts::DIMENSION_CARTE_X; i++) {
            for (int j = 0; j < sim::consts::DIMENSION_CARTE_Y; j++) {
                sim::carte::TypeCase c = s->get_carte()->get_case(i, j)->get_type();
                sf::Sprite sprite;
                // set color
//                sprite.setTexture(textureVide);
                std::cout << c << std::endl;
                switch (c) {
                    case sim::carte::VIDE:
                        sprite.setTexture(this->textureVide);
                        break;
                    case sim::carte::OBSTACLE:
                        sprite.setTexture(this->textureObstacle);
                        break;
                    case sim::carte::COLONIE:
                        sprite.setTexture(this->textureColonie);
                        break;
                    case sim::carte::NOURRITURE:
                        sprite.setTexture(this->textureNourriture);
                        break;
                }

                // set position
                sprite.setPosition(sf::Vector2f(i * SPRITE_SIZE, j * SPRITE_SIZE));
                sprite.setScale(sf::Vector2f(SPRITE_SIZE / 1000.f, SPRITE_SIZE / 1000.f));
                this->boxShapeList.push_back(sprite);

            }
        }
    }
}