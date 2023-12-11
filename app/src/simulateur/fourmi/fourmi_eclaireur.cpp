#include "fourmi_eclaireur.h"
#include "carte.h"
#include "simulateur.h"
#include <random>


namespace sim::fourmi {
    void FourmiEclaireur::deplacer() {
        bool a_fini = false;
        while (!a_fini) {
            //  Explore au hasard, bloquer par les obstacles
            sim::carte::Case *case_actuelle{this->get_case_actuelle()};
            sim::carte::Case *case_voisine = sim::carte::Carte::get_case_voisine8d(case_actuelle);

            // Regarde si la case voisine est valide
            bool est_valide = sim::carte::Carte::check_case(case_voisine);
            if (est_valide) {
                // Si elle est valide, on se déplace
                this->chemin.push_back(case_voisine);
                a_fini = true;
                this->explorer();
                case_actuelle->set_nb_fourmis(-1);
                case_voisine->set_nb_fourmis(1);
            }
        }
    }

    void FourmiEclaireur::explorer() {
        sim::carte::Case *case_actuelle{this->get_case_actuelle()};
        if (!case_actuelle->is_explore()) {
            case_actuelle->set_explore(true);
        }
    }
}