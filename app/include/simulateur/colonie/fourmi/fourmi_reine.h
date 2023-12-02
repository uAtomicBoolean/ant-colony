#ifndef ANT_COLONY_FOURMI_REINE_H
#define ANT_COLONY_FOURMI_REINE_H

#include "simulateur/colonie/fourmi/fourmi.h"


namespace simulateur::fourmi {
    class FourmiReine : public simulateur::fourmi::Fourmi {
    public:
        void pondre();
    };
}

#endif //ANT_COLONY_FOURMI_REINE_H
