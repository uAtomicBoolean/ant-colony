#include <iostream>
#include "colonie.h"

namespace sim::colonie {
    Colonie::Colonie() {

    }

    void Colonie::add_case_colonie(const carte::Case &col_case) {
        this->cases_colonie.push_back(col_case);

        // On ajoute la reine uniquement dans la premiere case de la colonie.
        if (this->reine == nullptr) {
            this->reine = new fourmi::FourmiReine();
            //this->fourmis.push_back(this->reine);
        }
        std::cout << "Liste des fourmis : " << this->fourmis.size() << std::endl;
    }
}