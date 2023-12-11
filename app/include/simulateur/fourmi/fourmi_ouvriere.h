#ifndef ANT_COLONY_FOURMI_OUVRIERE_H
#define ANT_COLONY_FOURMI_OUVRIERE_H

#include <vector>
#include "types.h"
#include "fourmi.h"
#include "constantes.h"


namespace sim::fourmi {
    class FourmiOuvriere : public sim::fourmi::Fourmi {
        // On utilise le constructeur de Fourmi.
        using Fourmi::Fourmi;

    private:
        const int duree_juvenile{sim::consts::DUREE_JUVENILE_OUVRIERE};
        float reserve_pheromone{sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX};
        bool est_chargee{};

    public:
        void deplacer() override;

        void depose_pheromone();

        void chercher_nourriture();

        void prendre_nourriture();

        void depose_nourriture();
    };
}

#endif //ANT_COLONY_FOURMI_OUVRIERE_H
