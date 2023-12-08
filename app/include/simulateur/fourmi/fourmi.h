#ifndef ANT_COLONY_FOURMI_H
#define ANT_COLONY_FOURMI_H

#include "types.h"
#include "case.h"


namespace sim::fourmi {
    class Fourmi {
    private:
        int age{};
        sim::carte::Case *case_actuelle{};

    public:
        Fourmi();

        explicit Fourmi(sim::carte::Case *case_actuelle);

        virtual void deplacer();

        void set_case_actuelle(sim::carte::Case *case_actuelle);

        sim::carte::Case *get_case_actuelle();
    };
}

#endif //ANT_COLONY_FOURMI_H
