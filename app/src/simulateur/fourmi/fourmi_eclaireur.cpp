#include "simulateur.h"
#include "fourmi_eclaireur.h"
#include <random>
#include <algorithm>


namespace sim::fourmi {
    void FourmiEclaireur::deplacer() {
        if (this->type != TypeFourmi::ECLAIREUR) return;

        std::vector<sim::carte::Case *> cases_voisines{this->get_cases_voisines()};

        if (cases_voisines.empty()) return;

        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> distrib(0, static_cast<int>(cases_voisines.size()) - 1);

        this->get_case_actuelle()->update_nb_fourmis(-1);
        this->chemin.push_back(cases_voisines.at(distrib(gen)));
        this->get_case_actuelle()->update_nb_fourmis(1);
        this->get_case_actuelle()->set_explore(true);
    }

    std::vector<sim::carte::Case *> FourmiEclaireur::get_cases_voisines() {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        std::vector<sim::carte::Case *> cases_voisines{};
        bool contient_case_inexploree{false};

        sim::types::position_t pos_cc{this->get_case_actuelle()->get_position()};
        for (int y{pos_cc.y - 1}; y <= pos_cc.y + 1; ++y) {
            for (int x{pos_cc.x - 1}; x <= pos_cc.x + 1; ++x) {
                if (x == pos_cc.x && y == pos_cc.y || x < 0 || y < 0 || x >= sim::consts::DIMENSION_CARTE_X ||
                    y >= sim::consts::DIMENSION_CARTE_Y)
                    continue;

                sim::carte::Case *case_iter{sim->get_carte()->get_case(x, y)};
                if (case_iter->get_type() == sim::carte::TypeCase::OBSTACLE ||
                    case_iter->get_nb_fourmis() == sim::consts::CAPACITE_FOURMI_MAX_CASE)
                    continue;
                if (!case_iter->is_explore()) contient_case_inexploree = true;
                cases_voisines.push_back(case_iter);
            }
        }

        if (contient_case_inexploree) {
            cases_voisines.erase(std::remove_if(cases_voisines.begin(), cases_voisines.end(), [](sim::carte::Case *c) {
                return c->is_explore();
            }), cases_voisines.end());
        }
        return cases_voisines;
    }
}