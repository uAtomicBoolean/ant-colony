#ifndef ANT_COLONY_FOURMI_ECLAIREUR_H
#define ANT_COLONY_FOURMI_ECLAIREUR_H

#include "fourmi.h"


namespace simulateur::fourmi {
    class FourmiEclaireur : public simulateur::fourmi::Fourmi {
    public:
        void explorer();
    };
}
#endif //ANT_COLONY_FOURMI_ECLAIREUR_H
