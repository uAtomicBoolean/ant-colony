#include <random>
#include "simulateur.h"
#include "fourmi_ouvriere.h"


namespace sim::fourmi {
    double FourmiOuvriere::get_charge() const {
        return this->charge;
    }

    void FourmiOuvriere::deplacer() {
        if (this->type != TypeFourmi::OUVRIERE) return;

        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        if (this->est_chargee) {
            this->get_case_actuelle()->update_nb_fourmis(-1);
            this->chemin.pop_back();
            sim::carte::Case *case_actu{this->get_case_actuelle()};

            // "Reset" complet de la fourmi quand elle arrive a la colonie.
            if (case_actu->get_type() == sim::carte::TypeCase::COLONIE) {
                sim->get_colonie()->ajoute_nourriture(this->charge);
                this->chemin.clear();
                this->charge = 0;
                this->est_chargee = false;
                this->reserve_pheromone = sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX;
            }

            // TODO déponse des phéromones sur le chemin du retour.
            // La dose de phéromone doit diminiuer au fur et a mesure que la fourmi se rapproche de la colonie.

        } else {
            std::vector<sim::carte::Case *> cases_voisines{
                    sim->get_carte()->get_case_voisine_ouvriere(this->get_case_actuelle())};

            if (cases_voisines.empty()) return;

            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<> distrib(0, static_cast<int>(cases_voisines.size()) - 1);

            this->get_case_actuelle()->update_nb_fourmis(-1);
            this->chemin.push_back(cases_voisines.at(distrib(gen)));

            sim::carte::Case *case_act{this->get_case_actuelle()};
            case_act->update_nb_fourmis(1);

            if (case_act->get_type() == sim::carte::TypeCase::NOURRITURE) {
                this->est_chargee = true;

                if (case_act->get_quant_nourriture() >= sim::consts::CAP_TRANSPORT_NOUR_OUVRIERE) {
                    case_act->set_quant_nourriture(
                            case_act->get_quant_nourriture() - sim::consts::CAP_TRANSPORT_NOUR_OUVRIERE);
                    this->charge = sim::consts::CAP_TRANSPORT_NOUR_OUVRIERE;
                } else {
                    this->charge = case_act->get_quant_nourriture();
                    case_act->set_quant_nourriture(0);
                }
            }
        }

    }

    void FourmiOuvriere::depose_pheromone() {

    }

    void FourmiOuvriere::prendre_nourriture() {

    }

    void FourmiOuvriere::depose_nourriture() {

    }
}