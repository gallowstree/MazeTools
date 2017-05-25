#ifndef TEST_CLIENT_MAZERENDERPROPERTIES_H
#define TEST_CLIENT_MAZERENDERPROPERTIES_H


#include <SFML/Graphics.hpp>

class MazeRenderingProperties {
public:

    MazeRenderingProperties();

    float wallThickness = 2;
    float tileSize = 20;
    sf::Color cellColor = sf::Color::Black;
    sf::Color wallColor = sf::Color::White;

    sf::Color gridColor = sf::Color::Color(128, 128, 128, 128);
};


#endif //TEST_CLIENT_MAZERENDERPROPERTIES_H
