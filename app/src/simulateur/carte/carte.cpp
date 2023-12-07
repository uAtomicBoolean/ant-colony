#include <random>
#include "carte.h"
#include "case.h"


namespace sim::carte {
    void Carte::placer_obstacle(const types::position_t &pos_start, int taille_obstacle) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 4);
        int direction = distrib(gen);

        // 2 ou 4 -> axe Y ; 1 ou 3 -> axe X.
        sim::carte::Case current_case{this->cases[pos_start.y][pos_start.x]};
        current_case.set_type(TypeCase::OBSTACLE);
        for (int k{1}; k <= taille_obstacle; ++k) {
            current_case.set_type(TypeCase::OBSTACLE);
            switch (direction) {
                case 1:
                    current_case = this->cases[pos_start.y][pos_start.x - k];
                    break;
                case 2:
                    current_case = this->cases[pos_start.y - k][pos_start.x];
                    break;
                case 3:
                    current_case = this->cases[pos_start.y][pos_start.x + k];
                    break;
                case 4:
                    current_case = this->cases[pos_start.y + k][pos_start.x];
                    break;
            }
        }
    }

    void Carte::genere_carte() {
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> distribution(0.f, 100.f);

        for (int y{0}; y < sim::consts::DIMENSION_CARTE_Y; ++y) {
            for (int x{0}; x < sim::consts::DIMENSION_CARTE_X; ++x) {
                if (this->cases[y][x].get_type() != TypeCase::VIDE) continue;

                sim::types::position_t pos_case{x, y};
                float proba{distribution(gen)};

                if (proba < sim::consts::PROBA_OBSTACLE) {
                    float proba_obstacle{distribution(gen)};
                    auto iterator = sim::consts::PROBA_TAILLE_OBSTACLE.lower_bound(proba_obstacle);
                    if (iterator != sim::consts::PROBA_TAILLE_OBSTACLE.end())
                        this->placer_obstacle(pos_case, iterator->second);

                } else if (proba >= sim::consts::PROBA_OBSTACLE && proba < sim::consts::PROBA_NOURRITURE) {
                    this->cases[y][x].set_type(TypeCase::NOURRITURE);
                    this->cases[y][x].set_position(pos_case);
                }
            }
        }

        // Ajout de la colonie.
        this->cases[sim::consts::DIMENSION_CARTE_Y / 2][sim::consts::DIMENSION_CARTE_X / 2].set_type(TypeCase::COLONIE);

        // Ajout des deux stocks massifs de nourriture.
    }

    sim::carte::Case **Carte::get_cases() {
        return nullptr;
    }

    sim::carte::Case *Carte::get_case(int x, int y) {
        return &this->cases[x][y];
    }
};
