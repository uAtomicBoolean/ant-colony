#include "fourmi_anarchiste.h"
#include "simulateur.h"
#include <random>
#include <iostream>

namespace sim::fourmi {
    void FourmiAnarchiste::deplacer() {
        if (this->type != TypeFourmi::ANARCHISTE) return;

        // Deplacement
        std::vector<sim::carte::Case *> cases_voisines{this->get_cases_voisines()};

        if (cases_voisines.empty()) {
            this->check_histo_cases = false;
            return;
        }
        this->check_histo_cases = true;


        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> distrib(0, static_cast<int>(cases_voisines.size()) - 1);

        this->get_case_actuelle()->update_nb_fourmis(-1);
        this->chemin.push_back(cases_voisines.at(distrib(gen)));

        sim::carte::Case *case_act{this->get_case_actuelle()};
        case_act->update_nb_fourmis(1);
    }

    std::vector<sim::carte::Case *> FourmiAnarchiste::get_cases_voisines() {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        std::vector<sim::carte::Case *> cases_voisines{};

        sim::carte::Case *case_actu{this->get_case_actuelle()};

        sim::types::position_t pos_cc{case_actu->get_position()};
        for (int y{pos_cc.y - 1}; y <= pos_cc.y + 1; ++y) {
            for (int x{pos_cc.x - 1}; x <= pos_cc.x + 1; ++x) {
                if (x == pos_cc.x && y == pos_cc.y || x < 0 || y < 0 || x >= sim::consts::DIMENSION_CARTE_X ||
                    y >= sim::consts::DIMENSION_CARTE_Y)
                    continue;

                sim::carte::Case *case_iter{sim->get_carte()->get_case(x, y)};
                if (case_iter->get_type() == sim::carte::TypeCase::OBSTACLE ||
                    case_iter->get_nb_fourmis() == sim::consts::CAPACITE_FOURMI_MAX_CASE ||
                    !sim::carte::Carte::check_case(case_iter, true))
                    continue;

                if (this->check_histo_cases &&
                    Fourmi::case_dans_histo(&this->chemin, case_iter->get_position()))
                    continue;

                cases_voisines.push_back(case_iter);
            }
        }
        return cases_voisines;
    }

    void FourmiAnarchiste::voler() {
        // TODO
    }
}