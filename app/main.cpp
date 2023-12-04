#include "simulateur/simulateur.h"
#include "gui/gui.h"

int main() {

    simulateur::Simulateur simulateur = simulateur::Simulateur();
    simulateur.genere_carte();
    simulateur.creer_colonie();

    gui::render(&simulateur);

    return 0;
}
