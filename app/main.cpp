#include "simulateur.h"
#include "gui/gui.h"

int main() {

    sim::Simulateur simulateur = sim::Simulateur();
    simulateur.genere_carte();

    gui::render(&simulateur);

    return 0;
}
