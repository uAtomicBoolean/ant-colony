#ifndef ANT_COLONY_CARTE_H
#define ANT_COLONY_CARTE_H

#include "types.h"
#include "constantes.h"
#include "fourmi.h"
#include "case.h"


namespace simulateur::carte {


    class Carte {
    private:
        simulateur::carte::Case cases[simulateur::constantes::DIMENSION_CARTE_X][simulateur::constantes::DIMENSION_CARTE_Y];

    public:
        simulateur::carte::Case **get_cases();

        simulateur::carte::Case *get_case(int x, int y);

        void genere_carte();
    };
}

#endif //ANT_COLONY_CARTE_H
