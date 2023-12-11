#include <iostream>
#include "fourmi_soldat.h"
#include "carte.h"
#include "simulateur.h"
#include <random>

namespace sim::fourmi {
    void FourmiSoldat::deplacer() {
        bool a_fini = false;
        while (!a_fini) {
            std::cout << this->get_case_actuelle()->get_position().x << " " << this->get_case_actuelle()->get_position().y << std::endl;
            sim::carte::Case *case_actuelle{this->get_case_actuelle()};
            sim::carte::Case *case_voisine = sim::carte::Carte::get_case_voisine8d(case_actuelle);
            std::cout << "case voisine : " << case_voisine->get_position().x << " " << case_voisine->get_position().y << std::endl;



            // Dans le cas où la case voisine est une case valide, et que le soldat n'est pas en combat, il se déplace
            bool est_valide = sim::carte::Carte::check_case(case_voisine) && case_voisine->is_explore();
            if (est_valide) {
                // Si elle est valide, on se déplace
                this->chemin.push_back(case_voisine);
                a_fini = true;
                std::cout << "case valide" << std::endl;
            }
        }
    }

    void FourmiSoldat::attaquer() {

    }

    void FourmiSoldat::verifier_duree_ronde() {

    }
}