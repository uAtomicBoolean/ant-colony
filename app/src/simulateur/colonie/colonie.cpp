#include <iostream>
#include "colonie.h"

namespace sim::colonie {
    Colonie::Colonie() {

    }

    void Colonie::add_case_colonie(const carte::Case &col_case) {
        this->cases_colonie.push_back(col_case);
        if (this->reine == nullptr) {
            std::cout << "Reine manquante !" << std::endl;
        }
    }
}