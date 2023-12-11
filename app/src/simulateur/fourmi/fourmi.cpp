#include "fourmi.h"


namespace sim::fourmi {
    Fourmi::Fourmi() = default;

    Fourmi::Fourmi(sim::carte::Case *case_actuelle) {
        this->chemin.push_back(case_actuelle);
    }

    int Fourmi::get_age() const {
        return this->age;
    }

    void Fourmi::vieillir() {
        ++this->age;
    }

    void Fourmi::deplacer() {
        // To override
    }

    sim::carte::Case *Fourmi::get_case_actuelle() {
        return this->chemin.back();
    }

    int Fourmi::get_duree_juvenile() const {
        return this->duree_juvenile;
    }
}
