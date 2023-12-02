#ifndef ANT_COLONY_FOURMI_ESCLAVAGISTE_H
#define ANT_COLONY_FOURMI_ESCLAVAGISTE_H

#include "simulateur/colonie/fourmi/fourmi.h"


namespace simulateur::fourmi {
    class FourmiEsclavagiste : public simulateur::fourmi::Fourmi {
    private:
        int transport_nourriture;
        int transport_larve;

    public:
        void voler();
    };
}


#endif //ANT_COLONY_FOURMI_ESCLAVAGISTE_H
