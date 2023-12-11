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
        ESCLAVAGISTE,
    };

    class Fourmi {
    protected:
        int age{};
        int duree_juvenile{};
        TypeFourmi type;
        std::vector<sim::carte::Case *> chemin{};

    public:
        Fourmi();

        explicit Fourmi(sim::carte::Case *case_actuelle, TypeFourmi type);

        Fourmi(sim::carte::Case *case_actuelle, TypeFourmi type, int dur_juvenile);

        int get_duree_juvenile() const;

        virtual void deplacer();

        int get_age() const;

        void vieillir();

        sim::carte::Case *get_case_actuelle();
    };
}

#endif //ANT_COLONY_FOURMI_H
