#include "colonie.h"
#include "fourmi_reine.h"

namespace sim::colonie {
    void Colonie::add_case_colonie(const carte::Case &col_case) {
        this->cases_colonie.push_back(col_case);

        // On ajoute la reine uniquement dans la premiere case de la colonie.
        if (this->reine == nullptr) {
            this->reine = new fourmi::FourmiReine();
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

    std::vector<sim::fourmi::FourmiOuvriere> *Colonie::get_ouvrieres() {
        return &this->ouvrieres;
    }

    std::vector<sim::fourmi::FourmiEclaireur> *Colonie::get_eclaireuses() {
        return &this->eclaireuses;
    }

    std::vector<sim::fourmi::FourmiSoldat> *Colonie::get_soldat() {
        return &this->soldats;
    }
}