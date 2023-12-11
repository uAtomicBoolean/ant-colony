#ifndef ANT_COLONY_FOURMI_SOLDAT_H
#define ANT_COLONY_FOURMI_SOLDAT_H

#include "fourmi.h"


namespace sim::fourmi {
    class FourmiSoldat : public sim::fourmi::Fourmi {
        // On utilise le constructeur de Fourmi.
        using Fourmi::Fourmi;
        
    private:
        bool retour_colonie{};
        bool protege_reine{};

    public:
        void deplacer() override;

        // Faut-il passer la fourmi esclavagiste a attaquer en parametre.
        void attaquer();

        void verifier_duree_ronde();
    };
}

#endif //ANT_COLONY_FOURMI_SOLDAT_H
