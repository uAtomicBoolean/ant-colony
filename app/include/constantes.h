#ifndef ANT_COLONY_CONSTANTES_H
#define ANT_COLONY_CONSTANTES_H


#include <map>


namespace sim::consts {
    // Les taux et proba sont tous en % (ex: 50 = 50%).

    const int DIMENSION_CARTE_X = 211; // 211 cases
    const int DIMENSION_CARTE_Y = 201; // 201 cases
    const int POS_COLONY_X = DIMENSION_CARTE_X / 2;
    const int POS_COLONY_Y = DIMENSION_CARTE_Y / 2;

    const int NOURRITURE_DEPART = 20; // 2 unités de nourriture
    const int NB_TOURS_PAR_JOUR = 24; // 24 tours pour faire un jour

    const int CAPACITE_FOURMI_MAX_CASE = 12; // 12 fourmis par case

    constexpr int AGE_MAX = 1 * 365; // 1 an
    constexpr int AGE_MAX_REINE = 10 * 365; // 10 ans
    const int TAILLE_UNITE_NOURRITURE = 1; // Donc la reine consomme 0.01 par tour.
    const double POURCEN_CONSO_NOURRITURE = .001f; // 0.1% par jour
    const double POURCENT_CONSO_NOURRITURE_REINE = .01f; // 1% par jour
    const double CONSO_NOURRITURE = TAILLE_UNITE_NOURRITURE * POURCEN_CONSO_NOURRITURE;
    const double CONSO_NOURRITURE_REINE = TAILLE_UNITE_NOURRITURE * POURCENT_CONSO_NOURRITURE_REINE;

    const double PROBA_NOURRITURE = .02f;
    /**
     * Nourriture disponible de base sur une case de nourriture.
     */
    const int NOURRITURE_DISPO = 10;
    const int NOURRITURE_DISPO_GROS_STOCK = 20000;

    const int NOMBRE_GROS_STOCK_NOURRITURE = 2;
    // Nombre de stocks de nourriture de 20k * 5 cases pour former 100k unités de nourriture

    const int CAP_TRANSPORT_NOUR_OUVRIERE = 1;

    const float PROBA_OBSTACLE = 5.f; // 30% de la surface totale de la carte
    const std::map<int, int> PROBA_TAILLE_OBSTACLE = {
            {50.f,  1},
            {80.f,  2},
            {90.f,  3},
            {95.f,  4},
            {99.f,  5},
            {100.f, 6},
    };

    const int DUREE_JUVENILE_OUVRIERE = 15;
    const int DUREE_JUVENILE_ECLAIREUR = 2;

    const int PONTE = 2; // 2 par jour
    const std::map<int, int> PROBA_PONTE_FOURMIS = {
            {79.f, 1},  // Ouvriere
            {94.f, 2},  // Soldat
            {99.f, 3},  // Eclaireur
    };

    const int DUREE_RONDE_SOLDAT = 100; // 100 jours
    const int DUREE_VIE_ANARCHISTE = 10; // 10 jours

    // Nombre de cases a regarder dans le chemin d'une fourmi lorsque'elle se deplace pour eviter de tourner en rond.
    const int TAILLE_HISTO_CASES = 30;

    // Une valeur permettant de calculer la quantite de pheromones a deposer sur une case.
    const int MAX_DIST_PHEROMONE = 150;
    const int PHEROMONE_MAX_CASE = 100; // 1000 unités de phéromones par case
    const int TAUX_EVAPORATION_PHEROMONE = 5; // par tour
    const double TAUX_DE_DIFFUSION_PHEROMONE = .2; // par tour
    const int CAPACITE_FOURMI_PHEROMONE_MAX = 500; // 500 unités de phéromones par fourmi
    const double PERCENT_PHERO_PAR_CASE = 0.05;

    const int PROBA_FOURMI_ANARCHISTE_MIN = 5; // 5 jours
    const int PROBA_FOURMI_ANARCHISTE_MAX = 10; // 10 jours
}

#endif //ANT_COLONY_CONSTANTES_H
