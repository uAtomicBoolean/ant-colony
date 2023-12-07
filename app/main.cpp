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

    for (int y = 0; y < sim::consts::DIMENSION_CARTE_Y; ++y) {
        for (int x = 0; x < sim::consts::DIMENSION_CARTE_X; ++x) {
            
        }
    }

    gui::GUI gui = gui::GUI();
    gui.init();

    return 0;
}
