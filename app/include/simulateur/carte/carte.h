#ifndef ANT_COLONY_CARTE_H
#define ANT_COLONY_CARTE_H

#include <vector>
#include "types.h"
#include "constantes.h"
#include "fourmi.h"
#include "case.h"


namespace simulateur::carte {


    class Carte {
    private:
        std::vector<std::vector<simulateur::carte::Case>> cases;

    public:
        Carte();

        simulateur::carte::Case **get_cases();

        simulateur::carte::Case *get_case(int x, int y);

        void genere_carte();
    };
}

#endif //ANT_COLONY_CARTE_H
