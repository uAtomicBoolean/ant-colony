#include "simulateur.h"
#include "gui/gui.h"
#include <filesystem>
#include <iostream>
#include <fstream>

int main() {

    std::filesystem::path cwd = std::filesystem::current_path() / "filename.txt";
    std::ofstream file(cwd.string());
    file.close();

    sim::Simulateur simulateur = sim::Simulateur();
    simulateur.genere_carte();

    gui::init(&simulateur);

    return 0;
}
