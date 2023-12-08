#include "simulateur.h"
#include "fourmi_reine.h"


namespace sim::fourmi {
    void FourmiReine::pondre_fourmi() {

    }

    void fourmi::FourmiReine::pondre(bool premiere_ponte) {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        if (premiere_ponte) {
            sim->get_colonie()->get_eclaireuses()->push_back(*(new FourmiEclaireur()));
        }
    }
}