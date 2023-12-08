#ifndef ANT_COLONY_FOURMI_H
#define ANT_COLONY_FOURMI_H

#include <vector>
#include "types.h"
#include "case.h"


namespace sim::fourmi {
    class Fourmi {
    protected:
        int age{};
        std::vector<sim::carte::Case *> chemin{};

    public:
        Fourmi();

        explicit Fourmi(sim::carte::Case *case_actuelle);

        virtual void deplacer();

        int get_age() const;

        void vieillir();

        sim::carte::Case *get_case_actuelle();
    };
}

#endif //ANT_COLONY_FOURMI_H
