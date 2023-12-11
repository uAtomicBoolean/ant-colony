#include <random>
#include <iostream>
#include "simulateur.h"
#include "fourmi_reine.h"


namespace sim::fourmi {
    void fourmi::FourmiReine::pondre(bool premiere_ponte) {
        sim::Simulateur *sim{sim::Simulateur::get_simulateur()};
        sim::carte::Case *case_depart{sim->get_colonie()->get_cases_colonie()->at(0)};

        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> distrib(0.f, 100.f);

        for (int nb_ponte{0}; nb_ponte < sim::consts::PONTE; ++nb_ponte) {
            if (premiere_ponte) {
                sim->get_colonie()->get_fourmis()->push_back(new FourmiEclaireur(case_depart));
                premiere_ponte = false;
                continue;
            }

            float proba_fourmi{distrib(gen)};
            auto iterator = sim::consts::PROBA_PONTE_FOURMIS.lower_bound(proba_fourmi);
            if (iterator == sim::consts::PROBA_PONTE_FOURMIS.end()) continue;

            switch (iterator->second) {
                case 1:
                    sim->get_colonie()->get_fourmis()->push_back(new FourmiOuvriere(case_depart));
                    break;
                case 2:
                    sim->get_colonie()->get_fourmis()->push_back(new FourmiSoldat(case_depart));
                    break;
                case 3:
                    sim->get_colonie()->get_fourmis()->push_back(new FourmiEclaireur(case_depart));
                    break;
                default:
                    break;
            }
        }
    }
}