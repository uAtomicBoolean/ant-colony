#ifndef ANT_COLONY_CASE_H
#define ANT_COLONY_CASE_H

#include <vector>
#include "types.h"


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
        double quant_nourriture{};
        bool est_explore{};
        sim::types::position_t position{};
        int nb_fourmis{};

    public:
        Case();

        bool is_explore();

        void set_type(TypeCase type);

        void set_position(sim::types::position_t pos);

        void set_quant_nourriture(double quant_nour);

        TypeCase get_type();

        sim::types::position_t get_position();
    };
};


#endif //ANT_COLONY_CASE_H
