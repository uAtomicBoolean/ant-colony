#include "colonie.h"
#include "fourmi_reine.h"

namespace sim::colonie {
    void Colonie::add_case_colonie(carte::Case *col_case) {
        this->cases_colonie.push_back(col_case);

        // On ajoute la reine uniquement dans la premiere case de la colonie.
        if (this->reine == nullptr) {
            this->reine = new fourmi::FourmiReine(col_case, sim::fourmi::TypeFourmi::REINE);
        }
    }

    double Colonie::get_stock_nourriture() const {
        return this->stock_nourriture;
    }

    void Colonie::ajoute_nourriture(double ajout) {
        this->stock_nourriture += ajout;
    }

    void Colonie::consomme_nourriture(double conso) {
        this->stock_nourriture -= conso;
    }

    sim::fourmi::FourmiReine *Colonie::get_reine() {
        return this->reine;
    }

    std::vector<sim::fourmi::Fourmi *> *Colonie::get_fourmis() {
        return &this->fourmis;
    }

    sim::fourmi::Fourmi *Colonie::get_fourmi(sim::types::position_t position) {
        for (auto &fourmi: this->fourmis) {
            if (fourmi->get_case_actuelle()->get_position().x == position.x &&
                fourmi->get_case_actuelle()->get_position().y == position.y) {
                return fourmi;
            }
        }
        return nullptr;
    }

    std::vector<sim::carte::Case *> *Colonie::get_cases_colonie() {
        return &this->cases_colonie;
    }
}