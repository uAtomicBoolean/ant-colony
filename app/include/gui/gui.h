#ifndef ANT_COLONY_GUI_H
#define ANT_COLONY_GUI_H

#include "simulateur/simulateur.h"
#include <SFML/Graphics.hpp>

namespace gui {
    class GUI {
    public:
        GUI();

        // Constants
        static const int COMPONENT_SIZE = 600;
        static const int SPRITE_SIZE = COMPONENT_SIZE / sim::consts::DIMENSION_CARTE_X;

        // Objects
        std::vector<sf::Sprite> boxShapeList{};

        // Textures
        sf::Texture textureFourmiOuvriere{};
        sf::Texture textureFourmiSoldat{};
        sf::Texture textureFourmiEclaireur{};
        sf::Texture textureFourmiReine{};
        sf::Texture textureFourmiEsclavagiste{};
        sf::Texture textureVide{};
        sf::Texture textureObstacle{};
        sf::Texture textureColonie{};
        sf::Texture textureNourriture{};

        // Functions
        void init(gui::GUI *gui);
        void render();
    };
}

#endif //ANT_COLONY_GUI_H
