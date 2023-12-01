#ifndef ANT_COLONY_CARTE_H
#define ANT_COLONY_CARTE_H

#include "types.h"
#include "simulateur/colonie/fourmi/fourmi.h"


namespace simulateur::carte {
    class Carte {
    private:
        int taille;

    };

    enum TypeCase {
        VIDE,
        NOURRITURE,
        OBSTACLE,
        COLONIE
    };

    class Case {
    private:
        TypeCase type;
        simulateur::types::position_t position;
        bool est_explore;
        simulateur::fourmi::Fourmi *fourmis[];
    };
}

#endif //ANT_COLONY_CARTE_H
