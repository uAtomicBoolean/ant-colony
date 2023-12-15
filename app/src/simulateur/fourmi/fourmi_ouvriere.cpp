#include <random>
#include <algorithm>
#include <iostream>
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
            if (this->multiplier_pheromone < 0) {
                double middle_value{
                        sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX / static_cast<double>(this->chemin.size())};
                this->multiplier_pheromone = middle_value / (static_cast<double>(this->chemin.size()) / 2);
            }
            // TODO Faire en sorte que les fourmis mettent moins de temps pour retourner a la colonie.
            //  Deux options :
            //      - faire une ligne droite vers la colonie
            //      - réduire le chemin en évitant toutes les boucles et le bordel dans les positions.
            this->get_case_actuelle()->update_nb_fourmis(-1);
            this->chemin.pop_back();
            sim::carte::Case *case_actu{this->get_case_actuelle()};
            case_actu->update_nb_fourmis(1);

            // "Reset" complet de la fourmi quand elle arrive a la colonie.
            if (case_actu->get_type() == sim::carte::TypeCase::COLONIE)
                this->depose_nourriture();
            else
                case_actu->increment_pheromone(this->multiplier_pheromone * static_cast<double>(this->chemin.size()));


        } else {
            // Deplacement en recherche de nourriture.
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
            if (case_act->get_type() == sim::carte::TypeCase::NOURRITURE) this->prendre_nourriture(case_act);
        }
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
            case_a->set_type(sim::carte::TypeCase::VIDE);
        }
    }

    void FourmiOuvriere::depose_nourriture() {
        sim::Simulateur::get_simulateur()->get_colonie()->ajoute_nourriture(this->charge);
        this->charge = 0;
        this->est_chargee = false;
        this->multiplier_pheromone = -1;
        this->reserve_pheromone = sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX;
    }

    std::vector<sim::carte::Case *> FourmiOuvriere::get_cases_voisines() {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};

        std::vector<sim::carte::Case *> cases_voisines{};
        bool contient_nourriture{false};

        // TODO Implementer la gestion des pheromones.
        // Exemple de gestion : 70% de chances que la fourmis choississe des cases pheromonees, 30% pour les cases.
        // Les 70% sont ensuite répartis entre les différentes cases phéromonées.
        // Du genre : somme des pheromones des cases / pheromone d'une case.

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

                if (case_iter->get_type() == sim::carte::TypeCase::NOURRITURE) {
                    if (!contient_nourriture) cases_voisines.clear();
                    contient_nourriture = true;
                    cases_voisines.push_back(case_iter);
                }
                if (!contient_nourriture) cases_voisines.push_back(case_iter);
            }
        }
        return cases_voisines;
    }
}