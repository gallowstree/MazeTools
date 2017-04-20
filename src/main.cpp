
#include <cstdio>
#include "Maze.h"
#include "MazeRenderingProperties.h"
#include "MazeRenderer.h"


int main()
{
    Maze maze(40,30);
    MazeRenderingProperties props;
    MazeRenderer renderer(props);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        renderer.render(maze, window);
        window.display();
    }

    return 0;
}



