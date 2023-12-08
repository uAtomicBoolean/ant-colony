#include "case.h"


namespace sim::carte {
    Case::Case() {
        this->type = TypeCase::VIDE;
    }

    int Case::get_nb_fourmis() const {
        return this->nb_fourmis;
    }

    void Case::update_nb_fourmis(int increment) {
        this->nb_fourmis += increment;
    }

    bool Case::is_explore() const {
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

    TypeCase Case::get_type() {
        return this->type;
    }


    sim::types::position_t Case::get_position() {
        return this->position;
    }
}