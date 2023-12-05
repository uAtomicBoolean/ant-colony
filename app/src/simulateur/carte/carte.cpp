#include <iostream>
#include <random>
#include "carte.h"
#include "case.h"


namespace sim::carte {

    Carte::Carte() {
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> distribution(0.f, 100.f);

        // Premiere generation de la carte. Toutes les cases sont vides.
        // Cela facilite grandement le placement des obstacles apres.
        // Point faible : pas opti.
        for (int y{0}; y < sim::consts::DIMENSION_CARTE_Y; ++y) {
            std::vector<sim::carte::Case> ligne;
            for (int x{0}; x < sim::consts::DIMENSION_CARTE_X; ++x) {
                sim::types::position_t pos_case{x, y};
                sim::carte::Case current_case{TypeCase::VIDE, pos_case};
                ligne.push_back(current_case);
            }
            this->cases.push_back(ligne);
        }
    }

    void Carte::genere_carte() {
        std::cout << "Génération de la carte" << std::endl;
    }

    sim::carte::Case **Carte::get_cases() {
        return nullptr;
    }

    sim::carte::Case *Carte::get_case(int x, int y) {
        return &this->cases[x][y];
    }
};
