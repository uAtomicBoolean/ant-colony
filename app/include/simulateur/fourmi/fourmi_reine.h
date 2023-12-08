#ifndef ANT_COLONY_FOURMI_REINE_H
#define ANT_COLONY_FOURMI_REINE_H

#include "fourmi.h"


namespace sim::fourmi {
    class FourmiReine : public sim::fourmi::Fourmi {
    private:
        /**
         * Pond une fourmi choisie aleatoirement.
         */
        void pondre_fourmi();

    public:
        /**
         * Pond deux fourmis.
         * @param premiere_ponte Si premiere ponte, alors la premiere fourmi est une eclaireuse.
         */
        void pondre(bool premiere_ponte);
    };
}

#endif //ANT_COLONY_FOURMI_REINE_H
