#include <iostream>
#include "simulateur/colonie/fourmi/fourmi.h"


namespace simulateur::fourmi {
    void Fourmi::deplacer() {
        std::cout << "Je me déplace, popolo..." << std::endl;
    }

    void Fourmi::displayFourmi() {
        std::cout << "Encore une fourmi ?" << std::endl;
    }
}
