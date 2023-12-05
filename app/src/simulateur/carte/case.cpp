#include "case.h"


namespace sim::carte {
    Case::Case(TypeCase type, sim::types::position_t position) {
        this->type = type;
        this->position = position;
        this->est_explore = false;
    }

    TypeCase Case::get_type() {
        return this->type;
    }


    sim::types::position_t Case::get_position() {
        return this->position;
    }
}