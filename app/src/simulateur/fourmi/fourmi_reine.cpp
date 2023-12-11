#include "simulateur.h"
#include "fourmi_reine.h"


namespace sim::fourmi {
    void fourmi::FourmiReine::pondre(bool premiere_ponte) {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        sim::carte::Case *case_depart{sim->get_colonie()->get_cases_colonie()->at(0)};

        for (int nb_ponte{0}; nb_ponte < sim::consts::PONTE; ++nb_ponte) {
            if (premiere_ponte) {
                sim->get_colonie()->get_fourmis()->push_back(new FourmiEclaireur(case_depart));
                premiere_ponte = false;
            }
        }
    }
}