#include <iostream>
#include "fourmi.h"


namespace sim::fourmi {
    Fourmi::Fourmi() = default;

    Fourmi::Fourmi(const sim::types::position_t pos) {
        this->position = pos;
    }

    void Fourmi::deplacer() {
        std::cout << "Je me déplace, popolo..." << std::endl;
    }
}
