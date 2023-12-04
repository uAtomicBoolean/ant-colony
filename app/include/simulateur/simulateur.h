#ifndef ANT_COLONY_SIMULATEUR_H
#define ANT_COLONY_SIMULATEUR_H

#include "carte.h"
#include "colonie.h"


namespace simulateur {
    class Simulateur {
    private:
        simulateur::colonie::Colonie colonie;
        simulateur::carte::Carte carte;
    public:
        simulateur::carte::Carte *get_carte();

        void genere_carte();

        void creer_colonie();
    };

}

#endif //ANT_COLONY_SIMULATEUR_H
