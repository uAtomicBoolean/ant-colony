#ifndef ANT_COLONY_SIMULATEUR_H
#define ANT_COLONY_SIMULATEUR_H

#include "gui.h"
#include "carte.h"
#include "colonie.h"
#include "fourmi_esclavagiste.h"


namespace sim {
    class Simulateur {
    private:
        static Simulateur *pointeur_sim;

        bool simu_active{};
        gui::GUI *gui{};
        sim::carte::Carte carte{};
        sim::colonie::Colonie colonie{};
        std::vector<sim::fourmi::FourmiEsclavagiste *> fourmis_esclavagistes{};

        Simulateur();

    public:
        // Suppression du constructeur de copie.
        Simulateur(const Simulateur &sim) = delete;

        static Simulateur *get_simulateur();

        void set_gui(gui::GUI *nouveau_gui);

        static void demarre_simulation();

        sim::carte::Carte *get_carte();

        sim::colonie::Colonie *get_colonie();

        void switch_gui_pret();

        void set_simu_active(bool active);

        void genere_carte();

        void simulation();

        void gere_fourmis_pas_simu(int heures);

        void gere_pheromones();

        std::vector<sim::fourmi::FourmiEsclavagiste *> *get_fourmis_esclavagistes();
    };
}

#endif //ANT_COLONY_SIMULATEUR_H
