#include "simulateur.h"
#include <thread>
#include <iostream>


namespace sim {
    // Initialisation en pointeur null pour le Singleton.
    Simulateur *Simulateur::pointeur_sim = nullptr;

    Simulateur::Simulateur() {
        this->simu_active = false;
        this->gui_pret = false;
    }


    Simulateur *Simulateur::get_simulateur() {
        if (Simulateur::pointeur_sim == nullptr) {
            Simulateur::pointeur_sim = new Simulateur();
        }
        return Simulateur::pointeur_sim;
    }

    void Simulateur::demarre_simulation() {
        Simulateur::get_simulateur()->simulation();
    }

    sim::carte::Carte *Simulateur::get_carte() {
        return &this->carte;
    }

    void Simulateur::switch_gui_pret() {
        this->gui_pret = !this->gui_pret;
    }

    void Simulateur::set_simu_active(bool active) {
        this->simu_active = active;
    }

    void Simulateur::genere_carte() {
        carte.genere_carte();
    }

    sim::colonie::Colonie *Simulateur::get_colonie() {
        return &this->colonie;
    }

    void Simulateur::simulation() {
        this->simu_active = true;

        bool premier_pas = true;
        while (this->simu_active) {
            if (!this->gui_pret) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                continue;
            }

            ++this->nb_heures;

            // On verifie que la reine est encore en vie.
            if (this->colonie.get_reine()->get_age() > sim::consts::AGE_MAX_REINE ||
                this->colonie.get_stock_nourriture() < sim::consts::CONSO_NOURRITURE_REINE) {
                this->simu_active = false;
                break;
            }
            this->colonie.get_reine()->vieillir();
            this->colonie.consomme_nourriture(sim::consts::CONSO_NOURRITURE_REINE);

            // La toute premiere fourmis pondue par la reine est forcement une eclaireuse.
            this->colonie.get_reine()->pondre(premier_pas);
            if (premier_pas) premier_pas = false;

            this->gere_fourmis_pas_simu(this->colonie.get_ouvrieres());
            this->gere_fourmis_pas_simu(this->colonie.get_eclaireuses());
            this->gere_fourmis_pas_simu(this->colonie.get_soldat());
        }
    }

    template<typename T>
    void Simulateur::gere_fourmis_pas_simu(T *fourmis) {
        // Gestion de l'âge des fourmis
        //      Incrementation de l'age.
        //      Tue les fourmis trop vieille.
        // Nourrir les fourmis.
        //      Tuer les fourmis qui ne peuvent pas se nourrir.
        // Déplacement des fourmis.
    }
}