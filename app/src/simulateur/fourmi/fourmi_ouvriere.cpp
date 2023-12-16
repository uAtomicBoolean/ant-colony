#include <random>
#include <algorithm>
#include <iostream>
#include "simulateur.h"
#include "fourmi_ouvriere.h"


namespace sim::fourmi {
    void FourmiOuvriere::move_to_case(sim::carte::Case *new_case) {
        this->get_case_actuelle()->update_nb_fourmis(-1);
        this->chemin.push_back(new_case);
        this->get_case_actuelle()->update_nb_fourmis(1);
    }

    void FourmiOuvriere::deplacement_normal(std::vector<sim::carte::Case *> *cases_voisines) {
        if (cases_voisines->empty()) {
            this->check_histo_cases = false;
            return;
        }
        this->check_histo_cases = true;

        double somme_distances{0};
        for (const sim::carte::Case *case_a: *cases_voisines) {
            somme_distances += case_a->get_dist_colonie();
        }

        std::map<double, sim::carte::Case *> probas_cases{};
        double somme_probas{0};
        for (sim::carte::Case *case_a: *cases_voisines) {
            double proba_case{(case_a->get_dist_colonie() * 100) / somme_distances};
            probas_cases[proba_case + somme_probas] = case_a;
            somme_probas += proba_case;
        }

        // Choix de la case.
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> distrib(0.f, 100.f);
        float proba_choix{distrib(gen)};
        auto iterator = probas_cases.lower_bound(proba_choix);
        if (iterator != probas_cases.end())
            this->move_to_case(iterator->second);
    }

    void FourmiOuvriere::deplacement_nourriture(std::vector<sim::carte::Case *> *cases_voisines) {
        this->move_to_case(cases_voisines->at(0));
        this->prendre_nourriture(this->get_case_actuelle());
    }

    void FourmiOuvriere::deplacement_pheromone(std::vector<sim::carte::Case *> *cases_voisines) {
        // TODO Debugger ce deplacement pour voir pourquoi il ne fonctionne pas.
        //  Les probas des phéromones sont potentiellement trop similaires.
        //  Sinon, c'est peut être la fonction get_cases_voisines qui ne fonctionne pas dans le cas des phéromones.

        double somme_pheromones{0};
        for (const sim::carte::Case *case_a: *cases_voisines) {
            somme_pheromones += case_a->get_quant_pheromone();
        }

        std::map<double, sim::carte::Case *> probas_cases{};
        double somme_probas{0};
        for (sim::carte::Case *case_a: *cases_voisines) {
            double proba_case{(case_a->get_quant_pheromone() * 100) / somme_pheromones};
            probas_cases[proba_case + somme_probas] = case_a;
            somme_probas += proba_case;
        }

        // Choix de la case.
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> distrib(0.f, 100.f);
        float proba_choix{distrib(gen)};
        auto iterator = probas_cases.lower_bound(proba_choix);
        if (iterator != probas_cases.end())
            this->move_to_case(iterator->second);
    }

    void FourmiOuvriere::deplacement_retour() {
        if (this->multiplier_pheromone < 0) {
            double middle_value{
                    sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX / static_cast<double>(this->chemin.size())};
            this->multiplier_pheromone = middle_value / (static_cast<double>(this->chemin.size()) / 2);
        }

        this->get_case_actuelle()->update_nb_fourmis(-1);
        this->chemin.pop_back();
        sim::carte::Case *case_actu{this->get_case_actuelle()};
        case_actu->update_nb_fourmis(1);

        // "Reset" complet de la fourmi quand elle arrive a la colonie.
        if (case_actu->get_type() == sim::carte::TypeCase::COLONIE)
            this->depose_nourriture();
        else {
            double dose_pheromones{this->multiplier_pheromone * static_cast<double>(this->chemin.size())};
            case_actu->increment_pheromone(dose_pheromones);
            this->reserve_pheromone -= dose_pheromones;
        }
    }

    double FourmiOuvriere::get_charge() const {
        return this->charge;
    }

    void FourmiOuvriere::deplacer() {
        if (this->type != TypeFourmi::OUVRIERE) return;

        // Retour a la colonie.
        if (this->est_chargee) {
            this->deplacement_retour();
        } else {
            std::vector<sim::carte::Case *> cases_voisines{this->get_cases_voisines()};
            if (this->type_move == TypeMoveOuvriere::PHEROMONE) {
                this->deplacement_pheromone(&cases_voisines);
            } else if (this->type_move == TypeMoveOuvriere::NOURRITURE) this->deplacement_nourriture(&cases_voisines);
            else this->deplacement_normal(&cases_voisines);

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
        this->reserve_pheromone = 500;
        this->multiplier_pheromone = -1;
        this->reserve_pheromone = sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX;
    }

    std::vector<sim::carte::Case *> FourmiOuvriere::get_cases_voisines() {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};

        std::vector<sim::carte::Case *> cases_voisines{};
        bool contient_nourriture{false};
        bool contient_pheromone{false};

        sim::types::position_t pos_cc{this->get_case_actuelle()->get_position()};
        for (int y{pos_cc.y - 1}; y <= pos_cc.y + 1; ++y) {
            for (int x{pos_cc.x - 1}; x <= pos_cc.x + 1; ++x) {
                if (x == pos_cc.x && y == pos_cc.y || x < 0 || y < 0 || x >= sim::consts::DIMENSION_CARTE_X ||
                    y >= sim::consts::DIMENSION_CARTE_Y)
                    continue;

                sim::carte::Case *case_iter{sim->get_carte()->get_case(x, y)};
                sim::carte::TypeCase type_case{case_iter->get_type()};

                if (type_case == sim::carte::TypeCase::OBSTACLE ||
                    case_iter->get_nb_fourmis() == sim::consts::CAPACITE_FOURMI_MAX_CASE ||
                    !case_iter->is_explore())
                    continue;

                if (case_iter->get_quant_pheromone() > 0 && type_case != sim::carte::TypeCase::NOURRITURE) {
                    if (!contient_pheromone) cases_voisines.clear();
                    contient_pheromone = true;
                    cases_voisines.push_back(case_iter);
                    continue;
                } else if (type_case == sim::carte::TypeCase::NOURRITURE) {
                    if (!contient_nourriture) cases_voisines.clear();
                    contient_nourriture = true;
                    cases_voisines.push_back(case_iter);
                    contient_pheromone = false;
                } else {
                    if (this->check_histo_cases && Fourmi::case_dans_histo(&this->chemin, case_iter->get_position()))
                        continue;
                    cases_voisines.push_back(case_iter);
                }
            }
        }

        if (contient_nourriture) this->type_move = TypeMoveOuvriere::NOURRITURE;
        else if (contient_pheromone) this->type_move = TypeMoveOuvriere::PHEROMONE;
        else {
            // Tri des cases par distance de la colonie.
            sim::types::position_t pos_colonie{sim->get_colonie()->get_cases_colonie()->at(0)->get_position()};
            std::sort(
                    cases_voisines.begin(),
                    cases_voisines.end(),
                    [pos_colonie](const sim::carte::Case *c1, const sim::carte::Case *c2) {
                        const double dist1{c1->get_dist_colonie()};
                        const double dist2{c2->get_dist_colonie()};
                        return dist1 < dist2;
                    });
            this->type_move = TypeMoveOuvriere::NORMAL;
        }
        return cases_voisines;
    }
}