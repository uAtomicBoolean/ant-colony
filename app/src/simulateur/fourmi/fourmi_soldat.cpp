#include <iostream>
#include "fourmi_soldat.h"
#include "carte.h"
#include "simulateur.h"
#include <random>

namespace sim::fourmi {
    void FourmiSoldat::deplacer() {

        /*// Si la fourmi doit retourner à la colonie, on la fait revenir
        if(this->get_retour_colonie()) {
            if(this->chemin.empty() || this->get_case_actuelle()->get_type() == carte::TypeCase::COLONIE) {
                this->set_retour_colonie(false);
                this->duree_ronde = 0;
                return;
            }
            this->chemin.pop_back();
            return;
        }
        else {
            this->incremente_duree_ronde();
        }

        bool a_fini = false;
        while (!a_fini) {
            std::cout << this->get_case_actuelle()->get_position().x << " " << this->get_case_actuelle()->get_position().y << std::endl;
            sim::carte::Case *case_actuelle{this->get_case_actuelle()};

            // Si sur cette case il y a une fourmi esclavagiste, on attaque
            if (case_actuelle->get_nb_fourmis() > 1) {
                sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
                std::vector<sim::fourmi::FourmiEsclavagiste *> *fourmis_esclavagistes{sim->get_fourmis_esclavagistes()};
                for (auto &fourmi_esclavagiste: *fourmis_esclavagistes) {
                    if (fourmi_esclavagiste->get_case_actuelle()->get_position().x == case_actuelle->get_position().x &&
                        fourmi_esclavagiste->get_case_actuelle()->get_position().y == case_actuelle->get_position().y) {
                        std::cout << "attaque" << std::endl;
                        FourmiSoldat::attaquer(fourmi_esclavagiste);
                        a_fini = true;
                        break;
                    }
                }
            }

            if (a_fini) {
                break;
            }

            sim::carte::Case *case_voisine = sim::carte::Carte::get_case_voisine8d(case_actuelle);
            std::cout << "case voisine : " << case_voisine->get_position().x << " " << case_voisine->get_position().y << std::endl;

            // Dans le cas où la case voisine est une case valide, et que le soldat n'est pas en combat, il se déplace
            bool est_valide = sim::carte::Carte::check_case(case_voisine) && case_voisine->is_explore();
            if (est_valide) {
                // Si elle est valide, on se déplace
                this->chemin.push_back(case_voisine);
                a_fini = true;
                case_actuelle->set_nb_fourmis(-1);
                case_voisine->set_nb_fourmis(1);
                std::cout << "case valide" << std::endl;
            }
        }*/
    }

    void FourmiSoldat::attaquer(sim::fourmi::FourmiEsclavagiste *fourmi_esclavagiste) {
        // Supprimer la fourmi esclavagiste
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        std::vector<sim::fourmi::FourmiEsclavagiste *> *fourmis_esclavagistes{sim->get_fourmis_esclavagistes()};
        for (auto it = fourmis_esclavagistes->begin(); it != fourmis_esclavagistes->end(); ++it) {
            if (*it == fourmi_esclavagiste) {
                fourmis_esclavagistes->erase(it);
                break;
            }
        }
    }

    void FourmiSoldat::incremente_duree_ronde() {
        if (this->duree_ronde == sim::consts::DUREE_RONDE_SOLDAT - 1) {
            this->aller_vers_colonie();
        }
        this->duree_ronde++;
    }

    void FourmiSoldat::aller_vers_colonie() {
        this->set_retour_colonie(true);
    }

    bool FourmiSoldat::get_retour_colonie() {
        return this->retour_colonie;
    }

    void FourmiSoldat::set_retour_colonie(bool retour) {
        this->retour_colonie = retour;
    }
}