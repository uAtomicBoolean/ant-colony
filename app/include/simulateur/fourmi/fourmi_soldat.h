#ifndef ANT_COLONY_FOURMI_SOLDAT_H
#define ANT_COLONY_FOURMI_SOLDAT_H

#include "fourmi.h"
#include "fourmi_anarchiste.h"


namespace sim::fourmi {
    class FourmiSoldat : public sim::fourmi::Fourmi {
        // On utilise le constructeur de Fourmi.
        using Fourmi::Fourmi;
        
    private:
        bool retour_colonie{};

    public:
        void deplacer() override;

        std::vector<sim::carte::Case *> get_cases_voisines() override;

        void attaquer(sim::fourmi::Fourmi *fourmi);

        void incremente_duree_ronde();

        int duree_ronde = 0;

        void aller_vers_colonie();

        bool get_retour_colonie();

        void set_retour_colonie(bool retour);

    };
}

#endif //ANT_COLONY_FOURMI_SOLDAT_H
