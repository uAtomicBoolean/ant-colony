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
        int nb_fourmis{0};
        bool est_explore{};
        double quant_nourriture{};

        TypeCase type{};
        sim::types::position_t position{};

    public:
        Case();

        int get_nb_fourmis() const;

        /**
         * Met a jour le nombre de fourmis actuellement dans la case.
         * @param increment Un entier egal a 1 ou -1 indiquant si une fourmi arrive ou part de la case.
         */
        void update_nb_fourmis(int increment);

        bool is_explore() const;

        void set_type(TypeCase type);

        void set_position(sim::types::position_t pos);

        void set_quant_nourriture(double quant_nour);

        TypeCase get_type();

        sim::types::position_t get_position();

        void set_explore(bool b);
    };
};


#endif //ANT_COLONY_CASE_H
