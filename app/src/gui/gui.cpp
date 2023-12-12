#include "simulateur.h"
#include "gui.h"
#include "case.h"
#include <SFML/Graphics.hpp>
#include <iostream>


namespace gui {
    GUI::GUI() = default;

    void GUI::init() {
        sf::RenderWindow window(sf::VideoMode(gui::GUI::COMPONENT_SIZE * 2, gui::GUI::COMPONENT_SIZE), "Ant Colony!");
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};


        sf::View view_default{window.getDefaultView()};
        view_default.setCenter(sf::Vector2f(gui::GUI::COMPONENT_SIZE / 2.99f, gui::GUI::COMPONENT_SIZE / 2.85f));
        view_default.zoom(0.2f);

        sf::View view_infos{};
        sf::RectangleShape onglet_infos(sf::Vector2f(150, 90));
        onglet_infos.setFillColor(sf::Color::White);
        onglet_infos.setPosition(5, 5);

        sf::RectangleShape bordure_infos(sf::Vector2f(160, 100));
        bordure_infos.setFillColor(sf::Color::Black);
        bordure_infos.setPosition(0, 0);

        sf::Font font_text_infos{};
        if (!font_text_infos.loadFromFile("../app/assets/PPAgrandir-WideMedium.ttf")) {
            std::cout << "Erreur lors du chargement de la police PPAgrandir-WideMedium.ttf !\n";
            exit(1);
        }

        sf::Text quant_jours{};
        quant_jours.setFont(font_text_infos);
        quant_jours.setString("Jour : " + std::to_string(sim->get_jours()));
        quant_jours.setCharacterSize(20);
        quant_jours.setPosition(sf::Vector2f(10, 10));
        quant_jours.setFillColor(sf::Color::Black);
        quant_jours.setScale(1.0f, 1.5f);

        sf::Text quant_fourmis{};
        quant_fourmis.setFont(font_text_infos);
        quant_fourmis.setString("Fourmis : " + std::to_string(sim->get_nombre_fourmis()));
        quant_fourmis.setCharacterSize(20);
        quant_fourmis.setPosition(sf::Vector2f(10, 50));
        quant_fourmis.setFillColor(sf::Color::Black);
        quant_fourmis.setScale(1.0f, 1.5f);

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
        this->textureExplore.loadFromFile("../app/assets/explore.png");

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    sim::Simulateur::get_simulateur()->set_simu_active(false);
                    window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                view_default.zoom(1.01f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                view_default.zoom(0.99f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                view_default.move(0, -0.5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view_default.move(0, 0.5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                view_default.move(-0.5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view_default.move(0.5, 0);
            }

            window.setFramerateLimit(30);
            window.clear();

            window.setView(view_default);
            this->render(window, sim);

            window.setView(view_infos);
            window.draw(bordure_infos);
            window.draw(onglet_infos);
            window.draw(quant_jours);
            window.draw(quant_fourmis);

            window.display();
        }
    }

    void GUI::render(sf::RenderWindow &win, sim::Simulateur *sim) const {

        for (int i = 0; i < sim::consts::DIMENSION_CARTE_X; i++) {
            for (int j = 0; j < sim::consts::DIMENSION_CARTE_Y; j++) {
                sim::carte::Case *caseXY = sim->get_carte()->get_case(i, j);
                sim::carte::TypeCase c = caseXY->get_type();
                sf::Sprite sprite;
                int nb_fourmis = caseXY->get_nb_fourmis();

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
                    win.draw(sprite);
                } else if (caseXY->is_explore()) {
                    sprite.setTexture(this->textureExplore);
                    sprite.setPosition(sf::Vector2f(i * SPRITE_SIZE, j * SPRITE_SIZE));
                    sprite.setScale(sf::Vector2f(SPRITE_SIZE / 1000.f, SPRITE_SIZE / 1000.f));
                    win.draw(sprite);
                }

                if (nb_fourmis != 0 && c != sim::carte::TypeCase::COLONIE) {
                    sf::Sprite sprite_fourmi{};

                    auto pos = sim::types::position_t{i, j};
                    auto fourmi = sim->get_colonie()->get_fourmi(pos);
                    if (nb_fourmis == 1 && fourmi != nullptr) {
                        // On ignore la reine car elle n'est jamais affichee.
                        switch (fourmi->get_type()) {
                            case sim::fourmi::OUVRIERE:
                                sprite_fourmi.setTexture(this->textureFourmiOuvriere);
                                break;
                            case sim::fourmi::SOLDAT:
                                sprite_fourmi.setTexture(this->textureFourmiSoldat);
                                break;
                            case sim::fourmi::ECLAIREUR:
                                sprite_fourmi.setTexture(this->textureFourmiEclaireur);
                                break;
                            case sim::fourmi::ESCLAVAGISTE:
                                sprite_fourmi.setTexture(this->textureFourmiEsclavagiste);
                                break;
                        }
                    } else {
                        sprite_fourmi.setTexture(this->textureGroupe);
                    }

                    sprite_fourmi.setPosition(sf::Vector2f(i * SPRITE_SIZE, j * SPRITE_SIZE));
                    sprite_fourmi.setScale(sf::Vector2f(SPRITE_SIZE / 1000.f, SPRITE_SIZE / 1000.f));
                    sprite_fourmi.setTexture(this->textureFourmiEclaireur);
                    win.draw(sprite_fourmi);
                }
            }
        }
    }

}