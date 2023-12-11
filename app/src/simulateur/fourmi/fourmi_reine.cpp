#include "simulateur.h"
#include "fourmi_reine.h"


namespace sim::fourmi {
    void fourmi::FourmiReine::pondre(bool premiere_ponte) {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};

        for (int nb_ponte{0}; nb_ponte < sim::consts::PONTE; ++nb_ponte) {
            if (premiere_ponte) {
                sim->get_colonie()->get_fourmis()->push_back(new FourmiEclaireur());
                premiere_ponte = false;
            }
        }
    }
}