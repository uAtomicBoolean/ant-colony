#include <random>
#include <iostream>
#include <algorithm>
#include "carte.h"
#include "case.h"
#include "simulateur.h"


namespace sim::carte {
    void Carte::placer_obstacle(const types::position_t &pos_start, int taille_obstacle) {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> distrib(1, 4);
        int direction = distrib(gen);

        // 2 ou 4 -> axe Y ; 1 ou 3 -> axe X.
        sim::carte::Case *current_case{this->get_case(pos_start.x, pos_start.y)};
        for (int k{1}; k <= taille_obstacle; ++k) {
            // Vérifie si on ne va pas hors limite lorsqu'on place les obstacles.
            if (pos_start.x - k < -1 || pos_start.x + k > sim::consts::DIMENSION_CARTE_X || pos_start.y - k < -1 ||
                pos_start.y + k > sim::consts::DIMENSION_CARTE_Y)
                return;

            if (current_case->get_type() == TypeCase::VIDE) {
                current_case->set_type(TypeCase::OBSTACLE);
            }
            switch (direction) {
                case 1:
                    current_case = this->get_case(pos_start.x - k, pos_start.y);
                    break;
                case 2:
                    current_case = this->get_case(pos_start.x, pos_start.y - k);
                    break;
                case 3:
                    current_case = this->get_case(pos_start.x + k, pos_start.y);
                    break;
                case 4:
                    current_case = this->get_case(pos_start.x, pos_start.y + k);
                    break;
                default:
                    break;
            }
        }
    }


    void Carte::placer_gros_stocks_nourriture() {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> distrib_y(1, sim::consts::DIMENSION_CARTE_Y - 1);
        std::uniform_int_distribution<int> distrib_x(1, sim::consts::DIMENSION_CARTE_X - 1);

        for (int nb{0}; nb < sim::consts::NOMBRE_GROS_STOCK_NOURRITURE; ++nb) {
            int pos_y{distrib_y(gen)};
            int pos_x{distrib_x(gen)};

            for (int y{-1}; y <= 1; ++y) {
                for (int x{-1}; x <= 1; ++x) {
                    if (y % 2 == 0 || x == 0) {
                        this->get_case(pos_x + x, pos_y + y)->set_type(TypeCase::NOURRITURE);
                        this->get_case(pos_x + x, pos_y + y)->set_quant_nourriture(
                                sim::consts::NOURRITURE_DISPO_GROS_STOCK);
                    }
                }
            }
        }
    }

    void Carte::genere_carte() {
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> distribution(0.f, 100.f);

        for (int y{0}; y < sim::consts::DIMENSION_CARTE_Y; ++y) {
            for (int x{0}; x < sim::consts::DIMENSION_CARTE_X; ++x) {
                sim::carte::Case *current_case{this->get_case(x, y)};
                current_case->set_position(sim::types::position_t{x, y});

                if (current_case->get_type() != TypeCase::VIDE) continue;

                sim::types::position_t pos_case{x, y};
                float proba{distribution(gen)};

                if (proba < sim::consts::PROBA_OBSTACLE) {
                    float proba_obstacle{distribution(gen)};
                    auto iterator = sim::consts::PROBA_TAILLE_OBSTACLE.lower_bound(proba_obstacle);
                    if (iterator != sim::consts::PROBA_TAILLE_OBSTACLE.end())
                        this->placer_obstacle(pos_case, iterator->second);

                } else if (proba >= sim::consts::PROBA_OBSTACLE &&
                           proba < sim::consts::PROBA_OBSTACLE + sim::consts::PROBA_NOURRITURE) {
                    current_case->set_type(TypeCase::NOURRITURE);
                    current_case->set_position(pos_case);
                    current_case->set_quant_nourriture(sim::consts::NOURRITURE_DISPO);
                }
            }
        }


        int case_col_x = sim::consts::DIMENSION_CARTE_X / 2;
        int case_col_y = sim::consts::DIMENSION_CARTE_Y / 2;
        this->get_case(case_col_x, case_col_y)->set_type(TypeCase::COLONIE);
        sim::Simulateur::get_simulateur()->get_colonie()
                ->add_case_colonie(this->get_case(case_col_x, case_col_y));

        this->placer_gros_stocks_nourriture();
    }

    sim::carte::Case **Carte::get_cases() {
        return nullptr;
    }

    sim::carte::Case *Carte::get_case(int x, int y) {
        return &this->cases[x][y];
    }

    bool Carte::check_case(sim::carte::Case *case_to_check) {
        if (case_to_check == nullptr) return false;
        if (case_to_check->get_nb_fourmis() >= sim::consts::CAPACITE_FOURMI_MAX_CASE) return false;
        if (case_to_check->get_type() == TypeCase::OBSTACLE) {
            return false;
        }
        return true;
    }

    std::vector<sim::carte::Case *> Carte::get_cases_voisines_eclaireur(sim::carte::Case *case_centrale) {
        std::vector<sim::carte::Case *> cases_voisines{};
        bool contient_case_inexploree{false};

        sim::types::position_t pos_cc{case_centrale->get_position()};
        for (int y{pos_cc.y - 1}; y <= pos_cc.y + 1; ++y) {
            for (int x{pos_cc.x - 1}; x <= pos_cc.x + 1; ++x) {
                if (x == pos_cc.x && y == pos_cc.y || x < 0 || y < 0 || x >= sim::consts::DIMENSION_CARTE_X ||
                    y >= sim::consts::DIMENSION_CARTE_Y)
                    continue;
                sim::carte::Case *current_case{this->get_case(x, y)};
                if (current_case->get_type() == sim::carte::TypeCase::OBSTACLE) continue;
                if (!current_case->is_explore()) contient_case_inexploree = true;
                cases_voisines.push_back(current_case);
            }
        }

        if (contient_case_inexploree) {
            cases_voisines.erase(std::remove_if(cases_voisines.begin(), cases_voisines.end(), [](sim::carte::Case *c) {
                return c->is_explore();
            }), cases_voisines.end());
        }
        return cases_voisines;
    }


    std::vector<sim::carte::Case *> Carte::get_case_voisine_exploree(sim::carte::Case *case_centrale) {
        std::vector<sim::carte::Case *> cases_voisines{};
        bool contient_nourriture{false};

        sim::types::position_t pos_cc{case_centrale->get_position()};
        for (int y{pos_cc.y - 1}; y <= pos_cc.y + 1; ++y) {
            for (int x{pos_cc.x - 1}; x <= pos_cc.x + 1; ++x) {
                if (x == pos_cc.x && y == pos_cc.y || x < 0 || y < 0 || x >= sim::consts::DIMENSION_CARTE_X ||
                    y >= sim::consts::DIMENSION_CARTE_Y)
                    continue;
                sim::carte::Case *current_case{this->get_case(x, y)};
                if (current_case->get_type() == sim::carte::TypeCase::OBSTACLE ||
                    current_case->get_type() == sim::carte::TypeCase::VIDE)
                    continue;
                if (current_case->get_type() == sim::carte::TypeCase::NOURRITURE) contient_nourriture = true;
                cases_voisines.push_back(current_case);
            }
        }

        if (contient_nourriture) {
            cases_voisines.erase(std::remove_if(cases_voisines.begin(), cases_voisines.end(), [](sim::carte::Case *c) {
                return c->get_type() == sim::carte::TypeCase::NOURRITURE;
            }), cases_voisines.end());
        }
        return cases_voisines;
    }


    sim::carte::Case *get_case_voisine4d(sim::carte::Case *case_to_check) {
        Carte *carte = sim::Simulateur::get_simulateur()->get_carte();
        // random from 1 to 8
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> distrib(1, 4);
        int direction = distrib(gen);
        switch (direction) {
            case 1:
                return sim::Simulateur::get_simulateur()->get_carte()->get_case(case_to_check->get_position().x - 1,
                                                                                case_to_check->get_position().y);
            case 2:
                return sim::Simulateur::get_simulateur()->get_carte()->get_case(case_to_check->get_position().x,
                                                                                case_to_check->get_position().y - 1);
            case 3:
                return sim::Simulateur::get_simulateur()->get_carte()->get_case(case_to_check->get_position().x + 1,
                                                                                case_to_check->get_position().y);
            case 4:
                return sim::Simulateur::get_simulateur()->get_carte()->get_case(case_to_check->get_position().x,
                                                                                case_to_check->get_position().y + 1);
            default:
                return nullptr;
        }
    }


    sim::carte::Case *Carte::get_case_voisine8d(sim::carte::Case *case_to_check) {
        Carte *carte = sim::Simulateur::get_simulateur()->get_carte();
        // random from 1 to 8
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> distrib(1, 8);
        int direction = distrib(gen);
        switch (direction) {
            case 1:
                return carte->get_case(case_to_check->get_position().x - 1, case_to_check->get_position().y);
            case 2:
                return carte->get_case(case_to_check->get_position().x, case_to_check->get_position().y - 1);
            case 3:
                return carte->get_case(case_to_check->get_position().x + 1, case_to_check->get_position().y);
            case 4:
                return carte->get_case(case_to_check->get_position().x, case_to_check->get_position().y + 1);
            case 5:
                return carte->get_case(case_to_check->get_position().x - 1, case_to_check->get_position().y - 1);
            case 6:
                return carte->get_case(case_to_check->get_position().x + 1, case_to_check->get_position().y - 1);
            case 7:
                return carte->get_case(case_to_check->get_position().x + 1, case_to_check->get_position().y + 1);
            case 8:
                return carte->get_case(case_to_check->get_position().x - 1, case_to_check->get_position().y + 1);
            default:
                return nullptr;
        }
    }
};
