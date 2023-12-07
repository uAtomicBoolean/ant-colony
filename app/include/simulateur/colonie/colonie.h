#ifndef ANT_COLONY_COLONIE_H
#define ANT_COLONY_COLONIE_H

#include <vector>
#include "case.h"
#include "fourmi_reine.h"


namespace sim::colonie {
    class Colonie {
    private:
        sim::fourmi::FourmiReine *reine{};
        std::vector<sim::fourmi::Fourmi> fourmis{};
        std::vector<sim::carte::Case> cases_colonie{};
    public:
        Colonie();

        void add_case_colonie(const sim::carte::Case &col_case);
    };
}

#endif //ANT_COLONY_COLONIE_H
