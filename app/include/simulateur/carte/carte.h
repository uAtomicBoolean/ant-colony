#ifndef ANT_COLONY_CARTE_H
#define ANT_COLONY_CARTE_H

#include <array>
#include "types.h"
#include "constantes.h"
#include "fourmi.h"
#include "case.h"


namespace sim::carte {
    class Carte {
    private:
        std::array<std::array<sim::carte::Case, sim::consts::DIMENSION_CARTE_Y>, sim::consts::DIMENSION_CARTE_X> cases{};

        void placer_obstacle(const sim::types::position_t &pos_start, int taille_obstacle);

        void placer_gros_stocks_nourriture();

    public:
        sim::carte::Case *get_case(int x, int y);

        void genere_carte();

        static bool check_case(sim::carte::Case *case_to_check, bool check_case);
    };
}

#endif //ANT_COLONY_CARTE_H
