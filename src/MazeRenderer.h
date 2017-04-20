#ifndef TEST_CLIENT_MAZEDRAWER_H
#define TEST_CLIENT_MAZEDRAWER_H


#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "MazeRenderingProperties.h"

class MazeRenderer {
public:
    MazeRenderingProperties renderProps;

    MazeRenderer(MazeRenderingProperties props);

    void render(const Maze maze, sf::RenderWindow &w);

    void drawTile(const Tile &t, sf::RenderWindow &w);
};


#endif //TEST_CLIENT_MAZEDRAWER_H