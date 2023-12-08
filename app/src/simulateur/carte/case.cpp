#include "case.h"


namespace sim::carte {
    Case::Case() {
        this->type = TypeCase::VIDE;
    }

    TypeCase Case::get_type() {
        return this->type;
    }


    sim::types::position_t Case::get_position() {
        return this->position;
    }

    bool Case::is_explore() {
        return this->est_explore;
    }

    void Case::set_type(TypeCase type_case) {
        this->type = type_case;
    }

    void Case::set_position(sim::types::position_t pos) {
        this->position = pos;
    }

    void Case::set_quant_nourriture(double quant_nour) {
        this->quant_nourriture = quant_nour;
    }
}