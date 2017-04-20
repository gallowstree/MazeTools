#include "MazeRenderer.h"
#include "MazeRenderingProperties.h"


MazeRenderer::MazeRenderer(MazeRenderingProperties props) : renderProps(props) {

}

void MazeRenderer::render(const Maze maze, sf::RenderWindow& w)
{
    for (int row = 0; row < maze.getRows(); row++)
    {
        for (int col = 0; col < maze.getCols(); col++)
        {
            drawTile(maze.getTileAt(row, col), w);
        }
    }
}

void MazeRenderer::drawTile(const Tile& t, sf::RenderWindow& w)
{
    auto rect = sf::RectangleShape(sf::Vector2f(renderProps.tileSize,renderProps.tileSize));
    rect.setPosition(t.row * renderProps.tileSize, t.col * renderProps.tileSize);
    rect.setFillColor(renderProps.cellColor);
    w.draw(rect);


    for (int i = 0; i < 4; i++)
    {
        if (t.hasWallAt[i])
        {
            auto wall = sf::RectangleShape();
            wall.setFillColor(renderProps.wallColor);

            auto pos = sf::Vector2f();
            pos.x = i < 2 ? t.row * renderProps.tileSize : t.row * renderProps.tileSize + renderProps.tileSize;
            pos.y = i < 2 ? t.col * renderProps.tileSize : t.col * renderProps.tileSize + renderProps.tileSize;

            auto size = sf::Vector2f();
            size.x = (i % 2) == 0 ? renderProps.wallThickness : renderProps.tileSize;
            size.y = (i % 2) == 0 ? renderProps.tileSize : renderProps.wallThickness;

            wall.setPosition(pos);
            wall.setSize(size);
            w.draw(wall);
        }
    }
}
