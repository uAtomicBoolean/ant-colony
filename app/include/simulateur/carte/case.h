#ifndef ANT_COLONY_CASE_H
#define ANT_COLONY_CASE_H

#include <vector>
#include "types.h"
#include "fourmi.h"


namespace sim::carte {
    enum TypeCase {
        VIDE,
        NOURRITURE,
        OBSTACLE,
        COLONIE
    };


    class Case {
    private:
        TypeCase type{};
        bool est_explore{};
        sim::types::position_t position{};
        std::vector<sim::fourmi::Fourmi> *fourmi{};

    public:
        Case(TypeCase type, sim::types::position_t position);

        TypeCase get_type();

        sim::types::position_t get_position();

        Case(Case *pCase);
    };
};


#endif //ANT_COLONY_CASE_H
