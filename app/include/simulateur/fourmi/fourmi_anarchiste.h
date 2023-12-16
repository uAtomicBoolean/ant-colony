#ifndef ANT_COLONY_FOURMI_ANARCHISTE_H
#define ANT_COLONY_FOURMI_ANARCHISTE_H

#include "fourmi.h"


namespace sim::fourmi {
    class FourmiAnarchiste : public sim::fourmi::Fourmi {
        // On utilise le constructeur de Fourmi.
        using Fourmi::Fourmi;

    private:
        int transport_larve{};

    public:
        void deplacer() override;

        void voler();
    };
}


#endif //ANT_COLONY_FOURMI_ANARCHISTE_H
