#ifndef ANT_COLONY_GUI_H
#define ANT_COLONY_GUI_H

#include "simulateur/simulateur.h"
#include <SFML/Graphics.hpp>

namespace gui {
    // Functions
    void init(sim::Simulateur *s);
    void render(sim::Simulateur *s);
}

#endif //ANT_COLONY_GUI_H
