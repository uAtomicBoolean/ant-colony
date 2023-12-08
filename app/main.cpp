#include "simulateur.h"
#include "gui/gui.h"
#include <filesystem>
#include <fstream>
#include <thread>


int main() {

    std::filesystem::path cwd = std::filesystem::current_path() / "filename.txt";
    std::ofstream file(cwd.string());
    file.close();

    sim::Simulateur *simulateur{sim::Simulateur::get_simulateur()};
    simulateur->genere_carte();

    std::thread thread_simu(sim::Simulateur::demarre_simulation);

    gui::GUI gui = gui::GUI();
    gui.init();

    thread_simu.join();
    
    return 0;
}
