#ifndef ANT_COLONY_FOURMI_SOLDAT_H
#define ANT_COLONY_FOURMI_SOLDAT_H

#include "fourmi.h"


namespace simulateur::fourmi {
    class FourmiSoldat : public simulateur::fourmi::Fourmi {
    private:
        bool retour_colonie;
        bool protege_reine;

    public:
        // Faut-il passer la fourmi esclavagiste a attaquer en parametre.
        void attaquer();

        void verifier_duree_ronde();
    };
}

#endif //ANT_COLONY_FOURMI_SOLDAT_H
