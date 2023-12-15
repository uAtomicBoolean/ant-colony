#include "simulateur.h"
#include <thread>
#include <iostream>


namespace sim {
    // Initialisation en pointeur null pour le Singleton.
    Simulateur *Simulateur::pointeur_sim = nullptr;

    Simulateur::Simulateur() {
        this->simu_active = false;
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

    int Simulateur::get_jours() const {
        return this->nb_jours;
    }

    int Simulateur::get_nombre_fourmis() {
        return static_cast<int>(this->colonie.get_fourmis()->size());
    }

    sim::carte::Carte *Simulateur::get_carte() {
        return &this->carte;
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
            // GESTION DE LA REINE.
            // On verifie que la reine est encore en vie.
            if (this->colonie.get_reine()->get_age() > sim::consts::AGE_MAX_REINE ||
                this->colonie.get_stock_nourriture() < sim::consts::CONSO_NOURRITURE_REINE) {
                this->simu_active = false;
                std::cout << "Fin de la simulation, la reine est morte !" << std::endl;
                std::cout << "Nombre de fourmis : " << this->colonie.get_fourmis()->size() << std::endl;
                std::cout << "Nombre de jours : " << this->nb_jours << std::endl;
                this->colonie.ajoute_nourriture(-999);
                break;
            }

            if (this->nb_heures % sim::consts::NB_TOURS_PAR_JOUR == 0) {
                this->colonie.get_reine()->vieillir();
                this->colonie.consomme_nourriture(sim::consts::CONSO_NOURRITURE_REINE);

                // La toute premiere fourmis pondue par la reine est forcement une eclaireuse.
                this->colonie.get_reine()->pondre(premier_pas);
                if (premier_pas) premier_pas = false;
            }

            // GESTION DES AUTRES FOURMIS.
            this->gere_fourmis_pas_simu(this->nb_heures);
            this->gere_pheromones();

            ++this->nb_heures;
            this->nb_jours = this->nb_heures / sim::consts::NB_TOURS_PAR_JOUR;

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    void Simulateur::gere_fourmis_pas_simu(int heures) {
        std::vector<sim::fourmi::Fourmi *> *fourmis{this->colonie.get_fourmis()};

        bool nouveau_jour = heures % sim::consts::NB_TOURS_PAR_JOUR == 0;

        for (int k{0}; k < fourmis->size(); ++k) {
            auto fourmi = fourmis->at(k);

            // GESTION DE L'AGE DES FOURMIS.
            if (nouveau_jour) fourmi->vieillir();

            if (fourmi->get_age() > sim::consts::AGE_MAX) {
                sim::carte::Case *case_actu = fourmi->get_case_actuelle();

                if (fourmi->get_type() == sim::fourmi::TypeFourmi::OUVRIERE) {
                    sim::fourmi::FourmiOuvriere *ouvriere{dynamic_cast<fourmi::FourmiOuvriere *>(fourmi)};
                    case_actu->set_quant_nourriture(ouvriere->get_charge());
                    case_actu->set_type(sim::carte::TypeCase::NOURRITURE);
                }

                case_actu->update_nb_fourmis(-1);
                fourmis->erase(fourmis->begin() + k);
                delete fourmi;
                continue;
            }

            // NOURRIR LES FOURMIS.
            if (nouveau_jour) {
                if (this->colonie.get_stock_nourriture() < sim::consts::CONSO_NOURRITURE) {
                    fourmis->erase(fourmis->begin() + k);
                    delete fourmi;
                    continue;
                }
                this->colonie.consomme_nourriture(sim::consts::CONSO_NOURRITURE);
            }

            if (!fourmi->est_juvenile()) {
                fourmi->deplacer();
            }
        }
    }

    void Simulateur::gere_pheromones() {
        // TODO
    }

    std::vector<sim::fourmi::FourmiEsclavagiste *> *Simulateur::get_fourmis_esclavagistes() {
        return &this->fourmis_esclavagistes;
    }
}