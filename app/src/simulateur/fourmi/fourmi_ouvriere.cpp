#include <random>
#include <algorithm>
#include "simulateur.h"
#include "fourmi_ouvriere.h"


namespace sim::fourmi {
    double FourmiOuvriere::get_charge() const {
        return this->charge;
    }

    void FourmiOuvriere::deplacer() {
        if (this->type != TypeFourmi::OUVRIERE) return;

        // Retour a la colonie.
        if (this->est_chargee) {
            this->get_case_actuelle()->update_nb_fourmis(-1);
            this->chemin.pop_back();
            sim::carte::Case *case_actu{this->get_case_actuelle()};

            // "Reset" complet de la fourmi quand elle arrive a la colonie.
            if (case_actu->get_type() == sim::carte::TypeCase::COLONIE) this->depose_nourriture();

            // TODO Gestion des phéromonse sur le chemin du retour.

        } else {
            // Deplacement en recherche de nourriture.
            std::vector<sim::carte::Case *> cases_voisines{this->get_cases_voisines()};

            if (cases_voisines.empty()) {
                this->check_histo_cases = false;
                return;
            }

            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<> distrib(0, static_cast<int>(cases_voisines.size()) - 1);

            this->get_case_actuelle()->update_nb_fourmis(-1);
            this->chemin.push_back(cases_voisines.at(distrib(gen)));
            this->check_histo_cases = true;

            sim::carte::Case *case_act{this->get_case_actuelle()};
            case_act->update_nb_fourmis(1);

            if (case_act->get_type() == sim::carte::TypeCase::NOURRITURE) this->prendre_nourriture(case_act);
        }

    }

    void FourmiOuvriere::depose_pheromone() {
        // TODO
        // La dose de phéromone doit diminiuer au fur et a mesure que la fourmi se rapproche de la colonie.
    }

    void FourmiOuvriere::prendre_nourriture(sim::carte::Case *case_a) {
        this->est_chargee = true;

        if (case_a->get_quant_nourriture() >= sim::consts::CAP_TRANSPORT_NOUR_OUVRIERE) {
            case_a->set_quant_nourriture(
                    case_a->get_quant_nourriture() - sim::consts::CAP_TRANSPORT_NOUR_OUVRIERE);
            this->charge = sim::consts::CAP_TRANSPORT_NOUR_OUVRIERE;
        } else {
            this->charge = case_a->get_quant_nourriture();
            case_a->set_quant_nourriture(0);
        }
    }

    void FourmiOuvriere::depose_nourriture() {
        sim::Simulateur::get_simulateur()->get_colonie()->ajoute_nourriture(this->charge);
        this->chemin.clear();
        this->charge = 0;
        this->est_chargee = false;
        this->reserve_pheromone = sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX;
    }

    std::vector<sim::carte::Case *> FourmiOuvriere::get_cases_voisines() {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};

        std::vector<sim::carte::Case *> cases_voisines{};
        bool contient_nourriture{false};

        // TODO Implementer la gestion des pheromones.

        sim::types::position_t pos_cc{this->get_case_actuelle()->get_position()};
        for (int y{pos_cc.y - 1}; y <= pos_cc.y + 1; ++y) {
            for (int x{pos_cc.x - 1}; x <= pos_cc.x + 1; ++x) {
                if (x == pos_cc.x && y == pos_cc.y || x < 0 || y < 0 || x >= sim::consts::DIMENSION_CARTE_X ||
                    y >= sim::consts::DIMENSION_CARTE_Y)
                    continue;

                sim::carte::Case *case_iter{sim->get_carte()->get_case(x, y)};

                if (case_iter->get_type() == sim::carte::TypeCase::OBSTACLE ||
                    case_iter->get_nb_fourmis() == sim::consts::CAPACITE_FOURMI_MAX_CASE ||
                    !case_iter->is_explore())
                    continue;

                if (this->check_histo_cases &&
                    Fourmi::case_dans_histo(&this->chemin, case_iter->get_position()))
                    continue;

                if (case_iter->get_type() == sim::carte::TypeCase::NOURRITURE) contient_nourriture = true;
                cases_voisines.push_back(case_iter);
            }
        }

        if (contient_nourriture) {
            cases_voisines.erase(std::remove_if(cases_voisines.begin(), cases_voisines.end(), [](sim::carte::Case *c) {
                return c->get_type() == sim::carte::TypeCase::NOURRITURE;
            }), cases_voisines.end());
        }
        return cases_voisines;
    }
}