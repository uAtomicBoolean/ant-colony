#ifndef ANT_COLONY_COLONIE_H
#define ANT_COLONY_COLONIE_H

#include <vector>
#include "case.h"


namespace sim::colonie {
    class Colonie {
    private:
        std::vector<sim::carte::Case> cases_colonie;
    public:
        void creer_colonie();
    };
}

#endif //ANT_COLONY_COLONIE_H
