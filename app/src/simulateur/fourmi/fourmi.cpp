#include "fourmi.h"
#include "constantes.h"
#include "simulateur.h"


namespace sim::fourmi {
    Fourmi::Fourmi() = default;

    Fourmi::Fourmi(sim::carte::Case *case_actuelle, TypeFourmi type) {
        this->chemin.push_back(case_actuelle);
        this->type = type;

        switch (type) {
            case TypeFourmi::ECLAIREUR:
                this->duree_juvenile = sim::consts::DUREE_JUVENILE_ECLAIREUR;
                break;
            case TypeFourmi::OUVRIERE:
                this->duree_juvenile = sim::consts::DUREE_JUVENILE_OUVRIERE;
                break;
            default:
                this->duree_juvenile = -1;
        }
    }

    int Fourmi::get_age() const {
        return this->age;
    }

    TypeFourmi Fourmi::get_type() const {
        return this->type;
    }

    sim::carte::Case *Fourmi::get_case_actuelle() {
        return this->chemin.back();
    }

    bool Fourmi::est_juvenile() {
        return this->age <= this->duree_juvenile;
    }

    void Fourmi::vieillir() {
        ++this->age;
    }

    void Fourmi::deplacer() {
        // To override
    }

    std::vector<sim::carte::Case *> Fourmi::get_cases_voisines() {
        // To override
        return std::vector<sim::carte::Case *>();
    }
}
