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
        double reserve_pheromone{sim::consts::CAPACITE_FOURMI_PHEROMONE_MAX};
        bool est_chargee{false};
        double charge{};
        TypeMoveOuvriere type_move{TypeMoveOuvriere::NORMAL};

        std::vector<sim::types::position_t> cases_pheromonees{};

        void move_to_case(sim::carte::Case *new_case);

        void deplacement_nourriture(std::vector<sim::carte::Case *> *cases_voisines);

        void deplacement_pheromone(std::vector<sim::carte::Case *> *cases_voisines);

        void deplacement_normal(std::vector<sim::carte::Case *> *cases_voisines);

        void deplacement_retour();

    public:
        double get_charge() const;

        void deplacer() override;

        std::vector<sim::carte::Case *> get_cases_voisines() override;

        void prendre_nourriture(sim::carte::Case *case_a);

        void depose_nourriture();
    };
}

#endif //ANT_COLONY_FOURMI_OUVRIERE_H
