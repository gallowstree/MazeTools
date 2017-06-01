//
// Created by Alvarado, Alejandro on 5/25/17.
//

#ifndef TEST_CLIENT_MAZEEDITOR_H
#define TEST_CLIENT_MAZEEDITOR_H


#include <MazeNavCommon/Maze.h>
#include "MazeRenderingProperties.h"
#include "Cursor.h"


class MazeEditor {
public:
    MazeEditor(Maze *maze, MazeRenderingProperties* renderProps);

    void toggleWallAtCursorPosition(int direction);
    bool toggleWall(int row, int col, int direction);
    void moveCursor(int direction);

private:
    Maze* maze;
    MazeRenderingProperties* renderProps = nullptr;
    Cursor* cursor = nullptr;
};



#endif //TEST_CLIENT_MAZEEDITOR_H
