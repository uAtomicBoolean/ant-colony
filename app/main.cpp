#include "simulateur.h"
#include "gui/gui.h"
#include <filesystem>
#include <iostream>
#include <fstream>

int main() {

    std::filesystem::path cwd = std::filesystem::current_path() / "filename.txt";
    std::ofstream file(cwd.string());
    file.close();

    sim::Simulateur *simulateur{sim::Simulateur::get_simulateur()};
    simulateur->genere_carte();

    gui::GUI gui = gui::GUI();
    gui.init(&gui);

    return 0;
}
