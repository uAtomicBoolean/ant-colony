#ifndef ANT_COLONY_FOURMI_H
#define ANT_COLONY_FOURMI_H

#include "types.h"
#include "simulateur/carte/carte.h"


namespace simulateur::fourmi {
    class Fourmi {
    private:
        int age;
        // TODO erreur lors de la declaration de l'attribut.
        // simulateur::carte::Case *case;
        simulateur::types::position_t position;

    public:
        virtual void deplacer();

        void displayFourmi();
    };
}

#endif //ANT_COLONY_FOURMI_H
