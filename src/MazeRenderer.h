#ifndef TEST_CLIENT_MAZEDRAWER_H
#define TEST_CLIENT_MAZEDRAWER_H


#include <SFML/Graphics.hpp>
#include "MazeNavCommon/Maze.h"
#include "MazeRenderingProperties.h"

class MazeRenderer {
public:

    MazeRenderer(MazeRenderingProperties* props);

    void render(const Maze *maze, sf::RenderWindow &w);

    void drawTile(const Tile *t, sf::RenderWindow &w);

private:
    MazeRenderingProperties* renderProps = nullptr;


};


#endif //TEST_CLIENT_MAZEDRAWER_H
