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
        float reserve_pheromone{sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX};
        bool est_chargee{false};
        double charge{};

    public:
        double get_charge() const;

        void deplacer() override;

        std::vector<sim::carte::Case *> get_cases_voisines() override;

        void depose_pheromone();

        void prendre_nourriture();

        void depose_nourriture();
    };
}

#endif //ANT_COLONY_FOURMI_OUVRIERE_H
