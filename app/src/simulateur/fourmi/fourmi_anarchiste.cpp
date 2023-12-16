#include "fourmi_anarchiste.h"
#include <random>

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

    void FourmiAnarchiste::voler() {
        // TODO
    }
}