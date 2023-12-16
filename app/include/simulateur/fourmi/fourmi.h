#ifndef ANT_COLONY_FOURMI_H
#define ANT_COLONY_FOURMI_H

#include <vector>
#include "types.h"
#include "case.h"


namespace sim::fourmi {
    enum TypeFourmi {
        REINE,
        OUVRIERE,
        SOLDAT,
        ECLAIREUR,
        ANARCHISTE,
    };

    enum TypeMoveOuvriere {
        NORMAL,
        PHEROMONE,
        NOURRITURE,
    };

    class Fourmi {
    protected:
        int age{};
        int duree_juvenile{};
        TypeFourmi type;

        bool check_histo_cases{true};

        std::vector<sim::carte::Case *> chemin{};

    public:
        Fourmi();

        explicit Fourmi(sim::carte::Case *case_actuelle, TypeFourmi type);

        bool est_juvenile();

        int get_age() const;

        TypeFourmi get_type() const;

        virtual void deplacer();

        virtual std::vector<sim::carte::Case *> get_cases_voisines();

        void vieillir();

        sim::carte::Case *get_case_actuelle();

        /**
         * Regarde si la case t_case n'est pas dans les 5 dernieres cases parcourues.
         * @param histo_cases Un vector contenant les 5 dernieres cases parcourues.
         * @param t_case La case ciblee.
         * @return Un booleen indiquant si la case n'est pas dans l'historique.
         */
        static bool
        case_dans_histo(std::vector<sim::carte::Case *> *chemin, sim::types::position_t pos_case);
    };
}

#endif //ANT_COLONY_FOURMI_H
