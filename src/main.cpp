
#include <cstdio>
#include "MazeNavCommon/Maze.h"
#include "MazeRenderingProperties.h"
#include "MazeRenderer.h"
#include "MazeEditor.h"
#include "RemoteControl.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <MazeNavCommon/MazeSerializer.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <MazeNavCommon/Search.h>
#include "MazeNavCommon/PriorityQueue.h"
using namespace std;
bool keyDown = false;

//void handleKeyPressed(sf::Keyboard::Key key);
bool handleKeyReleased(sf::Keyboard::Key key);

//void sendData(char data[]);

void saveMaze();

void loadMaze() ;

void mainLoop(sf::RenderWindow &window);

Maze* maze;
MazeRenderingProperties* props = nullptr;
MazeRenderer* renderer = nullptr;
MazeEditor* editor = nullptr;
bool editMode = true;

RemoteControl* remote = nullptr;

void testMazeGetSuccessors() {
    auto succ = new Tile*[4]();
    maze->getSuccessors(4,1,succ);

    assert(succ[DIRECTION_UP]->col == 1 && succ[DIRECTION_UP]->row == 3);
    assert(succ[DIRECTION_DOWN] == nullptr);
}

void testSerializerTileToBinary()
{
    MazeSerializer s;
    Tile* t = new Tile();
    t->hasWallAt[DIRECTION_LEFT] = true;
    t->hasWallAt[DIRECTION_UP] = true;
    t->hasWallAt[DIRECTION_RIGHT] = true;
    t->hasWallAt[DIRECTION_DOWN] = true;

    assert(s.toBinary(t) == 0b0001111);

    t->hasWallAt[DIRECTION_LEFT] = true;
    t->hasWallAt[DIRECTION_UP] = true;
    t->hasWallAt[DIRECTION_RIGHT] = false;
    t->hasWallAt[DIRECTION_DOWN] = false;

    assert(s.toBinary(t) == 0b0000011);
}

void testSerializerPack()
{
    MazeSerializer s;
    Tile* t = new Tile();
    Tile* t2 = new Tile();
    t->hasWallAt[DIRECTION_LEFT] = true;
    t->hasWallAt[DIRECTION_UP] = false;
    t->hasWallAt[DIRECTION_RIGHT] = true;
    t->hasWallAt[DIRECTION_DOWN] = false;

    t2->hasWallAt[DIRECTION_LEFT] = true;
    t2->hasWallAt[DIRECTION_UP] = true;
    t2->hasWallAt[DIRECTION_RIGHT] = false;
    t2->hasWallAt[DIRECTION_DOWN] = false;

    assert(s.pack(t, t2)== 0b01010011);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(900, 900), "My window");
    maze = new Maze(10, 10);

    maze->startTile = maze->getTileAt(0,0);
    maze->goalTile = maze->getTileAt(7,7);

    while (true) {
        props = new MazeRenderingProperties();
        props->tileSize = 80;
        props->wallThickness = 6;
        props->wallColor = sf::Color::Red;
        renderer = new MazeRenderer(props);
        editor = new MazeEditor(maze, props);
        remote = new RemoteControl();
        mainLoop(window);

        delete editor;
        delete renderer;
        delete props;
    }
    return 0;
}

void mainLoop(sf::RenderWindow &window) {
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
                if (handleKeyReleased(event.key.code)) { return;};
            }
        }

        window.clear(sf::Color::Black);
        renderer->render(maze, window);
        window.display();
    }
}


bool handleKeyReleased(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::M) {
        editMode = !editMode;
    }
    if (editMode) {
        if (key == sf::Keyboard::Key::Left) editor->moveCursor(DIRECTION_LEFT);
        else if (key == sf::Keyboard::Key::Right) editor->moveCursor(DIRECTION_RIGHT);
        else if (key == sf::Keyboard::Key::Down) editor->moveCursor(DIRECTION_DOWN);
        else if (key == sf::Keyboard::Key::Up) editor->moveCursor(DIRECTION_UP);

        else if (key == sf::Keyboard::Key::D) editor->toggleWallAtCursorPosition(DIRECTION_RIGHT);
        else if (key == sf::Keyboard::Key::S) editor->toggleWallAtCursorPosition(DIRECTION_DOWN);
        else if (key == sf::Keyboard::Key::W) editor->toggleWallAtCursorPosition(DIRECTION_UP);
        else if (key == sf::Keyboard::Key::A) editor->toggleWallAtCursorPosition(DIRECTION_LEFT);

        else if (key == sf::Keyboard::Key::F) saveMaze();
        else if (key == sf::Keyboard::Key::L) {loadMaze();
            return true;}
    } else {
        if (key == sf::Keyboard::Key::Left) remote->counterclockwise(90);
        else if (key == sf::Keyboard::Key::Right) remote->clockwise(90);
        else if (key == sf::Keyboard::Key::Down) remote->backwards(20);
        else if (key == sf::Keyboard::Key::Up) remote->forward(20);
        else if (key == sf::Keyboard::Key::D)
        {
            Queue<int> * route = new Queue<int>();
            Search::dfs(maze,route);
            route->print();
            delete route;
        }
        else if (key == sf::Keyboard::Key::B)
        {
            Queue<int> route;
            Search::bfs(maze,&route);
            route.print();
        }
        else if (key == sf::Keyboard::Key::A)
        {
            Queue<int> route;
            Search::astar(maze,&route);
            route.print();
        }

    }

    return false;
}

void promptForFilename(string& filename) {
    cout << "Enter filename: " << endl;
    cin  >> filename;
}

void loadMaze() {
    MazeSerializer s;
    string filename;
    promptForFilename(filename);

    ifstream file (filename, ios::ate | ios::binary);
    ifstream::pos_type pos = file.tellg();
    char* buffer = new char[pos]();
    file.seekg(0, ios::beg);
    file.read(buffer, pos);
    file.close();

    if (maze != nullptr)
        delete maze;

    cout << "read " << pos << " bytes!" << endl;
    maze = s.fromBinary(buffer);

    delete[] buffer;
    //testMazeGetSuccessors();
}

void saveMaze() {
    MazeSerializer s;
    string filename;
    promptForFilename(filename);

    ofstream file (filename, ios::out | ios::binary);
    size_t fileSize = s.calculateSize(maze);
    char* buffer = new char[fileSize]();
    s.toBinary(maze, buffer);

    cout << "Writing " << fileSize << " bytes..." <<endl;
    file.write(buffer, fileSize);
    file.close();
    cout << "Done!" << endl;

    delete[] buffer;
}
