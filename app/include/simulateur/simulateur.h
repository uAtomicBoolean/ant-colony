#ifndef ANT_COLONY_SIMULATEUR_H
#define ANT_COLONY_SIMULATEUR_H

#include "carte.h"
#include "colonie.h"


namespace sim {
    class Simulateur {
    private:
        sim::colonie::Colonie colonie{};
        sim::carte::Carte carte{};
    public:
        sim::carte::Carte *get_carte();

        void genere_carte();

        void creer_colonie();
    };

}

#endif //ANT_COLONY_SIMULATEUR_H
