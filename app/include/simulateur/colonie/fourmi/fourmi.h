#ifndef ANT_COLONY_FOURMI_H
#define ANT_COLONY_FOURMI_H

#include "types.h"


namespace simulateur::fourmi {
    class Fourmi {
    private:
        int age;
        simulateur::types::position_t position;

    public:
        virtual void deplacer();

        void displayFourmi();
    };
}

#endif //ANT_COLONY_FOURMI_H
