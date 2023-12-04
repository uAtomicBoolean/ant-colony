#ifndef ANT_COLONY_CASE_H
#define ANT_COLONY_CASE_H

#include "types.h"
#include "fourmi.h"


namespace simulateur::carte {
    enum TypeCase {
        VIDE,
        NOURRITURE,
        OBSTACLE,
        COLONIE
    };


    class Case {
    private:
        TypeCase type;
        bool est_explore;
        simulateur::types::position_t position;
        simulateur::fourmi::Fourmi *fourmi;

    public:
        TypeCase get_type();

        simulateur::types::position_t get_position();
    };
};


#endif //ANT_COLONY_CASE_H
