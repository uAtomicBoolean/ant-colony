#include <iostream>
#include "fourmi_eclaireur.h"
#include "carte.h"
#include <random>


namespace sim::fourmi {
    void FourmiEclaireur::deplacer() {
        bool a_bouge = false;
        while (!a_bouge) {
            //  Explore au hasard, bloquer par les obstacles
            std::cout << this->get_case_actuelle()->get_position().x << " " << this->get_case_actuelle()->get_position().y << std::endl;
            // random from 1 to 8
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<> distrib(1, 8);
            int direction = distrib(gen);
            std::cout << "direction : " << direction << std::endl;
            sim::carte::Case *case_actuelle{this->get_case_actuelle()};
            // *get_case_voisine4d(sim::carte::Case *case_to_check, int direction);
            sim::carte::Case *case_voisine = sim::carte::Carte::get_case_voisine8d(case_actuelle, direction);
            std::cout << "case voisine : " << case_voisine->get_position().x << " " << case_voisine->get_position().y << std::endl;
            // check if the case is not an obstacle
            bool est_valide = sim::carte::Carte::check_case(case_voisine);
            if (est_valide) {
                // if the case is valid, we move the ant to this case
                this->chemin.push_back(case_voisine);
                a_bouge = true;
                std::cout << "case valide" << std::endl;
            } else {
                // if the case is not valid, we move the ant to the current case
                this->chemin.push_back(case_actuelle);
                std::cout << "case non valide" << std::endl;
            }
        }
    }
}