#include <iostream>
#include "carte.h"

namespace simulateur::carte {
    void Carte::genere_carte() {
        std::cout << "Génération de la carte" << std::endl;
    }

    simulateur::carte::Case **Carte::get_cases() {
        return nullptr;
    }

    simulateur::carte::Case *Carte::get_case(int x, int y) {
        return &this->cases[x][y];
    }
};
