#ifndef ANT_COLONY_FOURMI_ECLAIREUR_H
#define ANT_COLONY_FOURMI_ECLAIREUR_H

#include "fourmi.h"


namespace sim::fourmi {
    class FourmiEclaireur : public sim::fourmi::Fourmi {
    public:
        void explorer();
        void deplacer() override;
    };
}
#endif //ANT_COLONY_FOURMI_ECLAIREUR_H
