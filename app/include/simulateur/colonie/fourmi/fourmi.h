#ifndef ANT_COLONY_FOURMI_H
#define ANT_COLONY_FOURMI_H

#include "types.h"


namespace sim::fourmi {
    class Fourmi {
    private:
        int age{};
        sim::types::position_t position{};

    public:
        Fourmi();

        explicit Fourmi(sim::types::position_t pos);

        virtual void deplacer();
    };
}

#endif //ANT_COLONY_FOURMI_H
