#ifndef ANT_COLONY_FOURMI_ECLAIREUR_H
#define ANT_COLONY_FOURMI_ECLAIREUR_H

#include "fourmi.h"
#include "constantes.h"


namespace sim::fourmi {
    class FourmiEclaireur : public sim::fourmi::Fourmi {
        // On utilise le constructeur de Fourmi.
        using Fourmi::Fourmi;

    protected:

    public:
        void deplacer() override;

        std::vector<sim::carte::Case *> get_cases_voisines() override;
    };
}

#endif //ANT_COLONY_FOURMI_ECLAIREUR_H
