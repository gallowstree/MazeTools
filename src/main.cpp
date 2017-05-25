
#include <cstdio>
#include "MazeNavCommon/Maze.h"
#include "MazeRenderingProperties.h"
#include "MazeRenderer.h"
#include "ServerSocket.h"
#include "MazeEditor.h"
#include <SFML/Network.hpp>

bool keyDown = false;

//void handleKeyPressed(sf::Keyboard::Key key);

void handleKeyReleased(sf::Keyboard::Key key);

//void sendData(char data[]);

Maze maze(10,10);
MazeRenderingProperties props;
MazeRenderer renderer(&props);
MazeEditor editor(&maze, &props);

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "My window");

    props.tileSize = 80;
    props.wallThickness = 6;
    props.wallColor = sf::Color::Red;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                //handleKeyPressed(event.key.code);
            }
            else if (event.type == sf::Event::KeyReleased) {
                handleKeyReleased(event.key.code);
            }
        }

        window.clear(sf::Color::Black);
        renderer.render(maze, window);
        window.display();
    }


    return 0;
}


void handleKeyReleased(sf::Keyboard::Key key) {

    if (key == sf::Keyboard::Key::Left) editor.moveCursor(DIRECTION_LEFT);
    else if (key == sf::Keyboard::Key::Right) editor.moveCursor(DIRECTION_RIGHT);
    else if (key == sf::Keyboard::Key::Down) editor.moveCursor(DIRECTION_DOWN);
    else if (key == sf::Keyboard::Key::Up) editor.moveCursor(DIRECTION_UP);

    else if (key == sf::Keyboard::Key::D) editor.toggleWallAtCursorPosition(DIRECTION_RIGHT);
    else if (key == sf::Keyboard::Key::S) editor.toggleWallAtCursorPosition(DIRECTION_DOWN);
    else if (key == sf::Keyboard::Key::W) editor.toggleWallAtCursorPosition(DIRECTION_UP);
    else if (key == sf::Keyboard::Key::A) editor.toggleWallAtCursorPosition(DIRECTION_LEFT);
}


//TODO: Move this to a remoteControl class or something
/*
void handleKeyReleased(sf::Keyboard::Key key) {
    keyDown = false;
    if (key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::Left )
        return;

    //sendData("MOTOR\nSTOP\n");
}

void handleKeyPressed(sf::Keyboard::Key key) {
    if (keyDown)
        return;
    keyDown = true;
    if (key == sf::Keyboard::Key::Up)
        sendData("MOTOR\nFORWARD\n100\n");
    else if (key == sf::Keyboard::Key::Down)
        sendData("MOTOR\nBACKWARDS\n100\n");
    else if (key == sf::Keyboard::Key::Right)
        sendData("MOTOR\nCLOCKWISE\n90\n");
    else if (key == sf::Keyboard::Key::Left)
        sendData("MOTOR\nCOUNTERCLOCKWISE\n90\n");
}

void sendData(char data[]) {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("192.168.1.28", 4420);
    if (status != sf::Socket::Done)
    {
        printf("error connecting\n");
    }
    printf("Sending %s\n", data);
    socket.send(data, strlen(data));
    socket.disconnect();
}

*/

