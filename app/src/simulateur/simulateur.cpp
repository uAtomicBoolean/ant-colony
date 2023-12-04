#include "simulateur/simulateur.h"

namespace simulateur {
    simulateur::carte::Carte *Simulateur::get_carte() {
        return &this->carte;
    }

    void Simulateur::genere_carte() {
        carte.genere_carte();
    }

    void Simulateur::creer_colonie() {
        colonie.creer_colonie();
    }
}