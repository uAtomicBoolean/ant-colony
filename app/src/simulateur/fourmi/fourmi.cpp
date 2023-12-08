#include "fourmi.h"


namespace sim::fourmi {
    Fourmi::Fourmi() = default;

    Fourmi::Fourmi(sim::carte::Case *case_actuelle) {
        this->case_actuelle = case_actuelle;
    }

    void Fourmi::deplacer() {
        
    }

    void Fourmi::set_case_actuelle(sim::carte::Case *case_actuelle) {
        this->case_actuelle = case_actuelle;
    }

    sim::carte::Case *Fourmi::get_case_actuelle() {
        return this->case_actuelle;
    }
}
