#ifndef TEST_CLIENT_MAZERENDERPROPERTIES_H
#define TEST_CLIENT_MAZERENDERPROPERTIES_H


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Cursor.h"


class MazeRenderingProperties {
public:

    MazeRenderingProperties();

    float wallThickness = 2;
    float tileSize = 20;
    sf::Color tileColor = sf::Color::Black;
    sf::Color highlightedTileColor = sf::Color::Color(180, 60, 60, 128);
    sf::Color wallColor = sf::Color::White;
    sf::Color gridColor = sf::Color::Color(255, 255, 255, 10);
    Cursor* cursor = nullptr;
};


#endif //TEST_CLIENT_MAZERENDERPROPERTIES_H
