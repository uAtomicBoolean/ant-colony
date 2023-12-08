#ifndef ANT_COLONY_SIMULATEUR_H
#define ANT_COLONY_SIMULATEUR_H

#include "carte.h"
#include "colonie.h"


namespace sim {
    class Simulateur {
    private:
        static Simulateur *pointeur_sim;

        bool simu_active{};
        bool gui_pret{};
        sim::carte::Carte carte{};
        sim::colonie::Colonie colonie{};

        Simulateur();

    public:
        // Suppression du constructeur de copie.
        Simulateur(const Simulateur &sim) = delete;

        static Simulateur *get_simulateur();

        sim::carte::Carte *get_carte();

        sim::colonie::Colonie *get_colonie();

        void switch_gui_pret();

        void genere_carte();

        void demarre_simulation();
    };
}

#endif //ANT_COLONY_SIMULATEUR_H
