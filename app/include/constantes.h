#ifndef ANT_COLONY_CLION_CONSTANTES_H
#define ANT_COLONY_CLION_CONSTANTES_H


namespace simulateur::constantes {
    // Les taux et proba sont tous en % (ex: 50 = 50%).

    const int DIMENSION_CARTE_X = 211; // 211 cases
    const int DIMENSION_CARTE_Y = 201; // 201 cases
    const int NOURRITURE_DEPART = 2; // 2 unités de nourriture
    const int NB_TOURS_PAR_JOUR = 24; // 24 tours pour faire un jour

    const int CAPACITE_FOURMI_MAX_FOURMILIERE = 100; // 100 fourmis par fourmilière
    const int CAPACITE_FOURMI_MAX_CASE = 12; // 12 fourmis par case

    const int AGE_MAX = 1; // 1 an
    const int AGE_MAX_REINE = 10; // 10 ans
    const double CONSOMMATION_NOURRITURE = .1; // 0.1% par jour
    const int CONSOMMATION_NOURRITURE_REINE = 1; // 1% par jour
    const int PONDAGE = 2; // 2 par jour

    const double PROBA_NOURRITURE = .02;
    const int NOURRITURE_DISPO = 10; // 10 unités de nourriture

    const int BIG_STOCK_NOURRITURE = 2;
    // Nombre de stocks de nourriture de 20k * 5 cases pour former 100k unités de nourriture

    const int PROBA_OBSTACLE = 30; // 30% de la surface totale de la carte
    const int PROBA_OBSTACLE_TAILLE_1 = 50; // 50% de chances de tomber sur un obstacle de taille 1
    const int PROBA_OBSTACLE_TAILLE_2 = 30;
    const int PROBA_OBSTACLE_TAILLE_3 = 10;
    const int PROBA_OBSTACLE_TAILLE_4 = 5;
    const int PROBA_OBSTACLE_TAILLE_5 = 4;
    const int PROBA_OBSTACLE_TAILLE_6 = 1;

    const int PROBA_REINE_POND_OUVRIERE = 80; // 80% de chances de pondre une ouvrière
    const int PROBA_REINE_POND_SOLDAT = 15;
    const int PROBA_REINE_POND_ECLAIREUR = 5;

    const int DUREE_RONDE_SOLDAT = 100; // 100 jours
    const int DUREE_VIE_ESCLAVAGISTE = 10; // 10 jours

    const int PHEROMONE_MAX_CASE = 1000; // 1000 unités de phéromones par case
    const int TAUX_EVAPORATION_PHEROMONE = 5; // par tour
    const double TAUX_DE_DIFFUSION_PHEROMONE = .2; // par tour
    const int CAPACITE_FOURMI_PHEROMONE_MAX = 500; // 500 unités de phéromones par fourmi

    const int PROBA_FOURMI_ESCLAVAGISTE_MIN = 5; // 5 jours
    const int PROBA_FOURMI_ESCLAVAGISTE_MAX = 10; // 10 jours
}

#endif //ANT_COLONY_CLION_CONSTANTES_H
