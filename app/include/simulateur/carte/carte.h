#ifndef ANT_COLONY_CARTE_H
#define ANT_COLONY_CARTE_H

#include <vector>
#include "types.h"
#include "constantes.h"
#include "fourmi.h"
#include "case.h"


namespace sim::carte {


    class Carte {
    private:
        std::vector<std::vector<sim::carte::Case>> cases{};

        void placer_obstacle(const sim::types::position_t &pos_start);

    public:
        Carte();

        sim::carte::Case **get_cases();

        sim::carte::Case *get_case(int x, int y);

        void genere_carte();
    };
}

#endif //ANT_COLONY_CARTE_H
