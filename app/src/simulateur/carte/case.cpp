#include "case.h"


namespace simulateur::carte {
    Case::Case(TypeCase type, simulateur::types::position_t position) {
        this->type = type;
        this->position = position;
        this->est_explore = false;
    }

    TypeCase Case::get_type() {
        return this->type;
    }


    simulateur::types::position_t Case::get_position() {
        return this->position;
    }
}