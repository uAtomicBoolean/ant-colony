#ifndef ANT_COLONY_COLONIE_H
#define ANT_COLONY_COLONIE_H

#include "simulateur/carte/carte.h"
#include "simulateur/colonie/colonie.h"


namespace simulateur {
    class Simulateur {
    private:
        simulateur::carte::Carte carte;
    public:
        void genere_carte();

        void creer_colonie();

        void update();
    };

}

#endif //ANT_COLONY_CLION_COLONIE_H
