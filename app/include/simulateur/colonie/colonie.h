#ifndef ANT_COLONY_COLONIE_H
#define ANT_COLONY_COLONIE_H

#include <vector>
#include "case.h"
#include "fourmi_eclaireur.h"
#include "fourmi_ouvriere.h"
#include "fourmi_reine.h"
#include "fourmi_soldat.h"


namespace sim::colonie {
    class Colonie {
    private:
        double stock_nourriture{2};

        sim::fourmi::FourmiReine *reine{};
        std::vector<sim::fourmi::FourmiOuvriere> ouvrieres{};
        std::vector<sim::fourmi::FourmiEclaireur> eclaireuses{};
        std::vector<sim::fourmi::FourmiSoldat> soldats{};
        std::vector<sim::carte::Case> cases_colonie{};

        std::vector<sim::fourmi::Fourmi *> fourmis{};

    public:
        void add_case_colonie(const sim::carte::Case &col_case);

        double get_stock_nourriture() const;

        void ajoute_nourriture(double ajout);

        void consomme_nourriture(double conso);

        sim::fourmi::FourmiReine *get_reine();

        std::vector<sim::fourmi::Fourmi *> *get_fourmis();

        sim::fourmi::Fourmi *get_fourmi(sim::types::position_t position);
    };
}

#endif //ANT_COLONY_COLONIE_H
