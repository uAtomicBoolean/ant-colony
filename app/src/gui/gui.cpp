#include "simulateur.h"
#include "gui.h"
#include "case.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace gui {
    GUI::GUI() = default;

    void GUI::init() {
        sf::RenderWindow window(
                sf::VideoMode(gui::GUI::COMPONENT_SIZE * 2, gui::GUI::COMPONENT_SIZE),
                "Ant Colony!"
        );
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};


        sf::View view_default{window.getDefaultView()};
        view_default.setCenter(sf::Vector2f(gui::GUI::COMPONENT_SIZE / 2.99f, gui::GUI::COMPONENT_SIZE / 2.85f));
        view_default.zoom(0.2f);

        // Onglet contenant les informations de la simulation.
        sf::View view_infos{};

        if (!this->font_textes.loadFromFile(GUI::FONT_NAME)) {
            std::cout << "Erreur lors du chargement de la police !\n";
            exit(1);
        }

        this->build_textes(sim);


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
                view_default.zoom(1.03f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                view_default.zoom(0.97f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                view_default.move(0, -1.5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view_default.move(0, 1.5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                view_default.move(-1.5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view_default.move(1.5, 0);
            }

            window.setFramerateLimit(30);
            window.clear();

            window.setView(view_default);
            this->render(window, sim);

            // Mise a jour des informations.
            window.setView(view_infos);

            this->update_textes(sim);
            this->draw_onglet_infos(&window);

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
                    sprite_fourmi.setPosition(sf::Vector2f(i * SPRITE_SIZE, j * SPRITE_SIZE));
                    sprite_fourmi.setScale(sf::Vector2f(SPRITE_SIZE / 1000.f, SPRITE_SIZE / 1000.f));
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

                    win.draw(sprite_fourmi);
                }
            }
        }
    }

    void GUI::build_textes(sim::Simulateur *sim) {
        this->onglet_infos.setFillColor(sf::Color::White);
        this->onglet_infos.setPosition(5, 5);

        this->bordure_infos.setFillColor(sf::Color::Black);
        this->bordure_infos.setPosition(0, 0);

        this->quant_jours.setFont(this->font_textes);
        this->quant_jours.setString("Jour : " + std::to_string(sim->get_jours()));
        this->quant_jours.setCharacterSize(GUI::FONT_SIZE);
        this->quant_jours.setPosition(sf::Vector2f(10, 10));
        this->quant_jours.setFillColor(sf::Color::Black);
        this->quant_jours.setScale(1.0f, 1.5f);

        this->quant_fourmis.setFont(this->font_textes);
        this->quant_fourmis.setString("Fourmis : " + std::to_string(sim->get_nombre_fourmis()));
        this->quant_fourmis.setCharacterSize(GUI::FONT_SIZE);
        this->quant_fourmis.setPosition(sf::Vector2f(10, 35));
        this->quant_fourmis.setFillColor(sf::Color::Black);
        this->quant_fourmis.setScale(1.0f, 1.5f);

        this->quant_nourriture.setFont(this->font_textes);
        this->quant_nourriture.setString("Nourriture : " + std::to_string(sim->get_colonie()->get_stock_nourriture()));
        this->quant_nourriture.setCharacterSize(GUI::FONT_SIZE);
        this->quant_nourriture.setPosition(sf::Vector2f(10, 60));
        this->quant_nourriture.setFillColor(sf::Color::Black);
        this->quant_nourriture.setScale(1.0f, 1.5f);
    }

    void GUI::update_textes(sim::Simulateur *sim) {
        this->quant_jours.setString("Jour : " + std::to_string(sim->get_jours()));
        this->quant_fourmis.setString("Fourmis : " + std::to_string(sim->get_nombre_fourmis()));

        std::stringstream stream_nourriture{};
        stream_nourriture << std::fixed << std::setprecision(3) << sim->get_colonie()->get_stock_nourriture();
        this->quant_nourriture.setString("Nourriture : " + stream_nourriture.str());
    }

    void GUI::draw_onglet_infos(sf::RenderWindow *win) {
        win->draw(this->bordure_infos);
        win->draw(this->onglet_infos);
        win->draw(this->quant_jours);
        win->draw(this->quant_fourmis);
        win->draw(this->quant_nourriture);
    }

}