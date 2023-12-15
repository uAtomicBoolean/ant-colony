#include "case.h"


namespace sim::carte {
    Case::Case() {
        this->type = TypeCase::VIDE;
    }

    int Case::get_nb_fourmis() const {
        return this->nb_fourmis;
    }

    void Case::update_nb_fourmis(int increment) {
        if (this->nb_fourmis <= 0 && increment < 0) {
            this->nb_fourmis = 0;
            return;
        }
        this->nb_fourmis += increment;
    }

    bool Case::is_explore() const {
        return this->est_explore;
    }

    void Case::set_type(TypeCase type_case) {
        this->type = type_case;
    }

    void Case::set_position(int x, int y) {
        this->position = {x, y};
    }

    void Case::set_quant_nourriture(double quant_nour) {
        this->quant_nourriture = quant_nour;
    }

    void Case::increment_pheromone(double quant) {
        this->quant_pheromone += quant;
    }

    sim::types::position_t Case::get_position() const {
        return this->position;
    }

    double Case::get_quant_nourriture() const {
        return this->quant_nourriture;
    }

    double Case::get_quant_pheromone() const {
        return this->quant_pheromone;
    }

    TypeCase Case::get_type() {
        return this->type;
    }

    void Case::set_explore(bool b) {
        this->est_explore = b;
    }
}