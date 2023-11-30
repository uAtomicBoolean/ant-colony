#include <iostream>
#include "./include/colonie.hpp"
#include "./include/gui.hpp"


int main() {
	std::cout << "Oui\n";
	std::cout << simulateur::colonie::test_ac() << "\n";
	simulateur::gui::test_gui();
	return 0;
}
