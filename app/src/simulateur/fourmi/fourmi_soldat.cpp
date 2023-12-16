#include "fourmi_soldat.h"
#include "carte.h"
#include "simulateur.h"
#include <random>

namespace sim::fourmi {
    void FourmiSoldat::deplacer() {
        if (this->type != TypeFourmi::SOLDAT) return;

        // Retour a la colonie.
        if (this->retour_colonie) {
            this->get_case_actuelle()->update_nb_fourmis(-1);
            this->chemin.pop_back();
            sim::carte::Case *case_actu{this->get_case_actuelle()};
            case_actu->update_nb_fourmis(1);

            // Implémenter attaquer si fourmi anarchiste
            if (this->get_case_actuelle()->get_nb_fourmis() > 1) {
                sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
                std::vector<sim::fourmi::FourmiAnarchiste *> *fourmis_anarchistes{sim->get_fourmis_anarchistes()};
                for (auto &fourmi_anarchiste: *fourmis_anarchistes) {
                    if (fourmi_anarchiste->get_case_actuelle()->get_position().x ==
                        this->get_case_actuelle()->get_position().x &&
                        fourmi_anarchiste->get_case_actuelle()->get_position().y ==
                        this->get_case_actuelle()->get_position().y) {
                        FourmiSoldat::attaquer(fourmi_anarchiste);
                        break;
                    }
                }
            }
        } else {
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

        // "Reset" complet de la fourmi quand elle arrive a la colonie.
        if (this->get_case_actuelle()->get_type() == sim::carte::TypeCase::COLONIE)
            this->set_retour_colonie(false);
        else
            this->incremente_duree_ronde();
    }

    std::vector<sim::carte::Case *> FourmiSoldat::get_cases_voisines() {
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

    void FourmiSoldat::attaquer(sim::fourmi::FourmiAnarchiste *fourmi_anarchiste) {
        // Supprimer la fourmi anarchiste
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        std::vector<sim::fourmi::FourmiAnarchiste *> *fourmis_anarchistes{sim->get_fourmis_anarchistes()};
        for (auto it = fourmis_anarchistes->begin(); it != fourmis_anarchistes->end(); ++it) {
            if (*it == fourmi_anarchiste) {
                fourmis_anarchistes->erase(it);
                break;
            }
        }
    }

    void FourmiSoldat::incremente_duree_ronde() {
        ++this->duree_ronde;
        if (this->duree_ronde == sim::consts::DUREE_RONDE_SOLDAT) {
            this->set_retour_colonie(true);
            this->duree_ronde = 0;
        }
    }

    bool FourmiSoldat::get_retour_colonie() {
        return this->retour_colonie;
    }

    void FourmiSoldat::set_retour_colonie(bool retour) {
        this->retour_colonie = retour;
    }
}