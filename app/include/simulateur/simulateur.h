#ifndef ANT_COLONY_SIMULATEUR_H
#define ANT_COLONY_SIMULATEUR_H

#include "carte.h"
#include "colonie.h"
#include "fourmi_anarchiste.h"


namespace sim {
    class Simulateur {
    private:
        static Simulateur *pointeur_sim;

        int nb_heures{0};
        int nb_jours{0};

        bool simu_active{};
        sim::carte::Carte carte{};
        sim::colonie::Colonie colonie{};

        Simulateur();

    public:
        // Suppression du constructeur de copie.
        Simulateur(const Simulateur &sim) = delete;

        static Simulateur *get_simulateur();

        static void demarre_simulation();

        int get_jours() const;

        int get_nombre_fourmis();

        sim::carte::Carte *get_carte();

        sim::colonie::Colonie *get_colonie();

        void set_simu_active(bool active);

        void genere_carte();

        void simulation();

        void gere_fourmis_pas_simu(int heures);

        void gere_pheromones();
    };
}

#endif //ANT_COLONY_SIMULATEUR_H
