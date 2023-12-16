#ifndef ANT_COLONY_GUI_H
#define ANT_COLONY_GUI_H

#include <SFML/Graphics.hpp>
#include "simulateur.h"
#include "constantes.h"


namespace gui {
    class GUI {
    private:
        // Constants
        static const int COMPONENT_SIZE{600};
        static const int SPRITE_SIZE{COMPONENT_SIZE / sim::consts::DIMENSION_CARTE_X};
        static const int FONT_SIZE{14};
        inline static const std::string FONT_NAME{"../app/assets/arial.ttf"};

        // Textures
        sf::Texture textureFourmiOuvriere{};
        sf::Texture textureFourmiSoldat{};
        sf::Texture textureFourmiEclaireur{};
        sf::Texture textureFourmiReine{};
        sf::Texture textureFourmiAnarchiste{};
        sf::Texture textureFourmiDebug{};
        sf::Texture textureGroupe{};
        sf::Texture textureVide{};
        sf::Texture textureObstacle{};
        sf::Texture textureColonie{};
        sf::Texture textureNourriture{};
        sf::Texture textureExplore{};
        sf::Texture texturePheromone{};

        sf::RectangleShape onglet_infos{sf::Vector2f(150, 90)};
        sf::RectangleShape bordure_infos{sf::Vector2f(160, 100)};

        sf::Font font_textes{};

        sf::Text quant_jours{};
        sf::Text quant_fourmis{};
        sf::Text quant_nourriture{};

    public:
        GUI();

        void init();

        void build_textes(sim::Simulateur *sim);

        void update_textes(sim::Simulateur *sim);

        void render(sf::RenderWindow &win, sim::Simulateur *sim) const;

        void draw_onglet_infos(sf::RenderWindow *win);
    };
}

#endif //ANT_COLONY_GUI_H
