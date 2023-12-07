#include "simulateur.h"

namespace sim {
    sim::carte::Carte *Simulateur::get_carte() {
        return &this->carte;
    }

    void Simulateur::genere_carte() {
        carte.genere_carte();
    }
}