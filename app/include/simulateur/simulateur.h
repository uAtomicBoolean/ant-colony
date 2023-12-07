#ifndef ANT_COLONY_SIMULATEUR_H
#define ANT_COLONY_SIMULATEUR_H

#include "carte.h"
#include "colonie.h"


namespace sim {
    class Simulateur {
    private:
        static Simulateur *pointeur_sim;

        Simulateur() {}

        sim::colonie::Colonie colonie{};
        sim::carte::Carte carte{};

    public:
        // Suppression du constructeur de copie.
        Simulateur(const Simulateur &sim) = delete;

        static Simulateur *get_simulateur();

        sim::carte::Carte *get_carte();

        sim::colonie::Colonie *get_colonie();

        void genere_carte();
    };
}

#endif //ANT_COLONY_SIMULATEUR_H
