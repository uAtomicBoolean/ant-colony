#include <random>
#include "simulateur.h"
#include "fourmi_ouvriere.h"


namespace sim::fourmi {
    void FourmiOuvriere::deplacer() {
        if (this->type != TypeFourmi::OUVRIERE) return;

        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        std::vector<sim::carte::Case *> cases_voisines{
                sim->get_carte()->get_case_voisine_exploree(this->get_case_actuelle())};

        if (cases_voisines.empty()) return;

        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> distrib(0, static_cast<int>(cases_voisines.size()) - 1);

        // TODO gérer les phéromones.
        // TODO gérer la récupération de la nourriture.

        // TODO Gérer le retour à la colonie si on a de la nourriture.

        this->get_case_actuelle()->update_nb_fourmis(-1);
        this->chemin.push_back(cases_voisines.at(distrib(gen)));
        this->get_case_actuelle()->update_nb_fourmis(1);
        this->get_case_actuelle()->set_explore(true);

    }

    void FourmiOuvriere::depose_pheromone() {

    }

    void FourmiOuvriere::chercher_nourriture() {

    }

    void FourmiOuvriere::prendre_nourriture() {

    }

    void FourmiOuvriere::depose_nourriture() {

    }
}