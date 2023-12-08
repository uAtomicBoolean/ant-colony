#ifndef ANT_COLONY_FOURMI_OUVRIERE_H
#define ANT_COLONY_FOURMI_OUVRIERE_H

#include <vector>
#include "types.h"
#include "fourmi.h"


namespace sim::fourmi {
    class FourmiOuvriere : public sim::fourmi::Fourmi {
    private:
        bool est_chargee{};
        float reserve_pheromone{};
        // Sans doute plus interessant de garder une liste de pointeur sur les cases parcourues.
        std::vector<sim::types::position_t> chemin_colonie{};

    public:
        void depose_pheromone();

        void chercher_nourriture();

        void prendre_nourriture();

        void depose_nourriture();
    };
}

#endif //ANT_COLONY_FOURMI_OUVRIERE_H
