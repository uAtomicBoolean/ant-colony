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
        bool est_explore;
        simulateur::types::position_t position;
//        simulateur::fourmi::Fourmi *fourmi; // /ant-colony/app/include/simulateur/carte/carte.h:23:21: error: no member named 'fourmi' in namespace 'simulateur'

    public:
        TypeCase get_type();

        simulateur::types::position_t get_position();
    };


    class Carte {
    private:
        int taille;
        Case cases[simulateur::constantes::DIMENSION_CARTE_Y][simulateur::constantes::DIMENSION_CARTE_X];

    public:
        int get_taille_x();

        int get_taille_y();

        Case **get_cases();

        Case get_case(int x, int y);

        void genere_carte();
    };
}

#endif //ANT_COLONY_CARTE_H
