#include "simulateur.h"
#include "fourmi_eclaireur.h"
#include <random>

namespace sim::fourmi {
    void FourmiEclaireur::deplacer() {
        if (this->type != TypeFourmi::ECLAIREUR) return;

        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        std::vector<sim::carte::Case *> cases_voisines{
                sim->get_carte()->get_cases_voisines_eclaireur(this->get_case_actuelle())};

        if (cases_voisines.empty()) return;

        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> distrib(0, static_cast<int>(cases_voisines.size()) - 1);

        this->get_case_actuelle()->set_nb_fourmis(-1);
        this->chemin.push_back(cases_voisines.at(distrib(gen)));
        this->get_case_actuelle()->set_nb_fourmis(1);
        this->get_case_actuelle()->set_explore(true);
    }
}