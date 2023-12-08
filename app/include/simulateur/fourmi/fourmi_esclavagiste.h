#ifndef ANT_COLONY_FOURMI_ESCLAVAGISTE_H
#define ANT_COLONY_FOURMI_ESCLAVAGISTE_H

#include "fourmi.h"


namespace sim::fourmi {
    class FourmiEsclavagiste : public sim::fourmi::Fourmi {
    private:
        int transport_nourriture{};
        int transport_larve{};

    public:
        void voler();
    };
}


#endif //ANT_COLONY_FOURMI_ESCLAVAGISTE_H
