#ifndef ANT_COLONY_CARTE_H
#define ANT_COLONY_CARTE_H

#include "types.h"
#include "simulateur/colonie/fourmi/fourmi.h"
#include "constantes.h"


namespace simulateur::carte {
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


    class Carte {
    private:
        int taille;
        Case cases[simulateur::constantes::DIMENSION_CARTE_Y][simulateur::constantes::DIMENSION_CARTE_X];

    public:
        int get_taille_x();

        int get_taille_y();

        Case get_case(int x, int y);
    };
}

#endif //ANT_COLONY_CARTE_H
