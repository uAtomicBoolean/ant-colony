#ifndef ANT_COLONY_CONSTANTES_H
#define ANT_COLONY_CONSTANTES_H


#include <map>

namespace sim::consts {
    // Les taux et proba sont tous en % (ex: 50 = 50%).

    const int DIMENSION_CARTE_X = 211; // 211 cases
    const int DIMENSION_CARTE_Y = 201; // 201 cases
    const int NOURRITURE_DEPART = 2; // 2 unités de nourriture
    const int NB_TOURS_PAR_JOUR = 24; // 24 tours pour faire un jour

    const int CAPACITE_FOURMI_MAX_FOURMILIERE = 100; // 100 fourmis par fourmilière
    const int CAPACITE_FOURMI_MAX_CASE = 12; // 12 fourmis par case

    constexpr int AGE_MAX = 1 * 365; // 1 an
    constexpr int AGE_MAX_REINE = 10 * 365; // 10 ans
    const int TAILLE_UNITE_NOURRITURE = 1; // Donc la reine consomme 0.01 par tour.
    const double POURCEN_CONSO_NOURRITURE = .001f; // 0.1% par jour
    const double POURCENT_CONSO_NOURRITURE_REINE = .01f; // 1% par jour
    const double CONSO_NOURRITURE = TAILLE_UNITE_NOURRITURE * POURCEN_CONSO_NOURRITURE;
    const double CONSO_NOURRITURE_REINE = TAILLE_UNITE_NOURRITURE * POURCENT_CONSO_NOURRITURE_REINE;
    const int PONTE = 2; // 2 par jour

    const double PROBA_NOURRITURE = .02f;
    /**
     * Nourriture disponible de base sur une case de nourriture.
     */
    const int NOURRITURE_DISPO = 10;
    const int NOURRITURE_DISPO_GROS_STOCK = 20000;

    const int NOMBRE_GROS_STOCK_NOURRITURE = 2;
    // Nombre de stocks de nourriture de 20k * 5 cases pour former 100k unités de nourriture

    const float PROBA_OBSTACLE = 15.f; // 30% de la surface totale de la carte
    const std::map<int, int> PROBA_TAILLE_OBSTACLE = {
            {49.f, 1},
            {79.f, 2},
            {89.f, 3},
            {94.f, 4},
            {98.f, 5},
            {99.f, 6},
    };

    const int DUREE_JUVENILE_OUVRIERE = 15;
    const int DUREE_JUVENILE_ECLAIREUR = 2;

    const int PROBA_REINE_POND_OUVRIERE = 80.f; // 80% de chances de pondre une ouvrière
    const int PROBA_REINE_POND_SOLDAT = 15.f;
    const int PROBA_REINE_POND_ECLAIREUR = 5.f;

    const int DUREE_RONDE_SOLDAT = 100; // 100 jours
    const int DUREE_VIE_ESCLAVAGISTE = 10; // 10 jours

    const int PHEROMONE_MAX_CASE = 1000; // 1000 unités de phéromones par case
    const int TAUX_EVAPORATION_PHEROMONE = 5; // par tour
    const double TAUX_DE_DIFFUSION_PHEROMONE = .2; // par tour
    const int CAPACITE_FOURMI_PHEROMONE_MAX = 500; // 500 unités de phéromones par fourmi

    const int PROBA_FOURMI_ESCLAVAGISTE_MIN = 5; // 5 jours
    const int PROBA_FOURMI_ESCLAVAGISTE_MAX = 10; // 10 jours
}

#endif //ANT_COLONY_CONSTANTES_H
