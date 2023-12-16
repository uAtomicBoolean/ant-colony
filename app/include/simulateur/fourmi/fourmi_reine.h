#ifndef ANT_COLONY_FOURMI_REINE_H
#define ANT_COLONY_FOURMI_REINE_H

#include "fourmi.h"


namespace sim::fourmi {
    class FourmiReine : public sim::fourmi::Fourmi {
        // On utilise le constructeur de Fourmi.
        using Fourmi::Fourmi;

    public:
        int proba_anarchiste{10};
        /**
         * Pond deux fourmis.
         * @param premiere_ponte Si premiere ponte, alors la premiere fourmi est une eclaireuse.
         */
        void pondre(bool premiere_ponte);
    };
}

#endif //ANT_COLONY_FOURMI_REINE_H
