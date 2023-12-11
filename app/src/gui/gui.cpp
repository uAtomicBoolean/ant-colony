#include "simulateur.h"
#include "gui.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace gui {
    GUI::GUI() = default;

    void GUI::init() {
        sf::RenderWindow window(sf::VideoMode(gui::GUI::COMPONENT_SIZE * 2, gui::GUI::COMPONENT_SIZE), "Ant Colony!");
        sf::View view = window.getDefaultView();
        view.setCenter(sf::Vector2f(gui::GUI::COMPONENT_SIZE / 2.99f, gui::GUI::COMPONENT_SIZE / 2.85f));
        view.zoom(0.2f);
        window.setView(view);

        sf::RectangleShape sideMenu;
        sideMenu.setFillColor(sf::Color::White);
        sideMenu.setSize(sf::Vector2f(gui::GUI::COMPONENT_SIZE, gui::GUI::COMPONENT_SIZE));
        sideMenu.setPosition(sf::Vector2f(gui::GUI::COMPONENT_SIZE, 0));

        this->textureFourmiOuvriere.loadFromFile("../app/assets/ouvriere.png");
        this->textureFourmiSoldat.loadFromFile("../app/assets/soldat.png");
        this->textureFourmiEclaireur.loadFromFile("../app/assets/eclaireur.png");
        this->textureFourmiReine.loadFromFile("../app/assets/reine.png");
        this->textureFourmiEsclavagiste.loadFromFile("../app/assets/esclavagiste.png");
        this->textureGroupe.loadFromFile("../app/assets/groupe.png");
        this->textureVide.loadFromFile("../app/assets/vide.png");
        this->textureObstacle.loadFromFile("../app/assets/obstacle.png");
        this->textureColonie.loadFromFile("../app/assets/colonie.png");
        this->textureNourriture.loadFromFile("../app/assets/nourriture.png");

        this->render();

        sim::Simulateur *s{sim::Simulateur::get_simulateur()};
        s->set_gui(this);


        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    sim::Simulateur::get_simulateur()->set_simu_active(false);
                    window.close();
                }
            }

            window.clear();
            for (auto &boxShape: this->boxShapeList) {
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                view.move(0, -0.5);
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view.move(0, 0.5);
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                view.move(-0.5, 0);
                window.setView(view);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view.move(0.5, 0);
                window.setView(view);
            }
            window.display();
        }
    }

    void GUI::render() {
        this->boxShapeList.clear();

        sim::Simulateur *s{sim::Simulateur::get_simulateur()};

        for (int i = 0; i < sim::consts::DIMENSION_CARTE_X; i++) {
            for (int j = 0; j < sim::consts::DIMENSION_CARTE_Y; j++) {
                sim::carte::TypeCase c = s->get_carte()->get_case(i, j)->get_type();
                sf::Sprite sprite;
                int nb_fourmis = s->get_carte()->get_case(i, j)->get_nb_fourmis();

                switch (c) {
                    case sim::carte::OBSTACLE:
                        sprite.setTexture(this->textureObstacle);
                        break;
                    case sim::carte::COLONIE:
                        sprite.setTexture(this->textureColonie);
                        break;
                    case sim::carte::NOURRITURE:
                        sprite.setTexture(this->textureNourriture);
                        break;
                    default:
                        break;
                }

                if (c != sim::carte::TypeCase::VIDE) {
                    sprite.setPosition(sf::Vector2f(i * SPRITE_SIZE, j * SPRITE_SIZE));
                    sprite.setScale(sf::Vector2f(SPRITE_SIZE / 1000.f, SPRITE_SIZE / 1000.f));
                    this->boxShapeList.push_back(sprite);
                }

                if (nb_fourmis != 0 && c != sim::carte::TypeCase::COLONIE) {
                    sf::Sprite sprite_fourmi;
                    sprite_fourmi.setPosition(sf::Vector2f(i * SPRITE_SIZE, j * SPRITE_SIZE));
                    sprite_fourmi.setScale(sf::Vector2f(SPRITE_SIZE / 1000.f, SPRITE_SIZE / 1000.f));
                    sprite_fourmi.setTexture(this->textureFourmiEclaireur);
                    this->boxShapeList.push_back(sprite_fourmi);
                }
            }
        }
    }
}