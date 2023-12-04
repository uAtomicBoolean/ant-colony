#include "case.h"


namespace simulateur::carte {
    TypeCase Case::get_type() {
        return this->type;
    }


    simulateur::types::position_t Case::get_position() {
        return this->position;
    }
}