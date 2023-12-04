#include <iostream>
#include <random>
#include "carte.h"


namespace simulateur::carte {
    Carte::Carte() {
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> distribution(0.f, 100.f);

        // TODO Comment gérer la création des obstacles proprement ?
        // Une arraylist qui stocke des positions qui indiquent les futures cases obstacles.
        // Ou alors, on build toutes les lignes et cases, puis on modifie le type des cases.

        for (int y{0}; y < simulateur::constantes::DIMENSION_CARTE_Y; ++y) {
            std::vector<simulateur::carte::Case> ligne;
            for (int x{0}; x < simulateur::constantes::DIMENSION_CARTE_X; ++x) {
                float proba{distribution(gen)};

                // TODO Voir comment gérer la proba des obstacles pour simplifier le code.
                if (proba < 30.f) {
                    float proba_obstacle{distribution(gen)};
                    if (proba < 50.f) {
                        // Est une case.
                    }
                } else if (proba >= 30.f && proba <= 30.02f) {
                    // Est une case de 10 unités de nourriture
                }
            }
            this->cases.push_back(ligne);
        }
    }

    void Carte::genere_carte() {
        std::cout << "Génération de la carte" << std::endl;
    }

    simulateur::carte::Case **Carte::get_cases() {
        return nullptr;
    }

    simulateur::carte::Case *Carte::get_case(int x, int y) {
        return &this->cases[x][y];
    }
};
