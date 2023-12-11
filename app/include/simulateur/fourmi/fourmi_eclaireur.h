#ifndef ANT_COLONY_FOURMI_ECLAIREUR_H
#define ANT_COLONY_FOURMI_ECLAIREUR_H

#include "fourmi.h"
#include "constantes.h"


namespace sim::fourmi {
    class FourmiEclaireur : public sim::fourmi::Fourmi {
    protected:
        const int duree_juvenile{sim::consts::DUREE_JUVENILE_ECLAIREUR};

    public:
        void explorer();

        void deplacer() override;
    };
}
#endif //ANT_COLONY_FOURMI_ECLAIREUR_H
