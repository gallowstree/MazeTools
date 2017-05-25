//
// Created by Alvarado, Alejandro on 5/25/17.
//

#include "MazeEditor.h"

bool MazeEditor::toggleWall(int row, int col, int direction) {
    if ( row < 0 || col < 0 || row >= maze->getRows() || col >= maze->getCols())
        return false;

    Tile* t = maze->getTileAt(row, col);
    bool newValue = !t->hasWallAt[direction];
    t->hasWallAt[direction] = newValue;

    if (direction == DIRECTION_LEFT && col > 0) {
        maze->getTileAt(row, col - 1)->hasWallAt[DIRECTION_RIGHT] = newValue;
    }
    else if (direction == DIRECTION_RIGHT && col < maze->getCols() - 1) {
        maze->getTileAt(row, col + 1)->hasWallAt[DIRECTION_LEFT] = newValue;
    }
    else if (direction == DIRECTION_UP && row > 0) {
        maze->getTileAt(row - 1, col)->hasWallAt[DIRECTION_DOWN] = newValue;
    }
    else if (direction == DIRECTION_DOWN && row < maze->getRows() - 1) {
        maze->getTileAt(row + 1, col)->hasWallAt[DIRECTION_UP] = newValue;
    }

    return true;
}

MazeEditor::MazeEditor(Maze *maze, MazeRenderingProperties *renderProps) : maze(maze), renderProps(renderProps){
    cursor = new Cursor();
    renderProps->cursor = cursor;
}

void MazeEditor::moveCursor(int direction) {
    if (direction == DIRECTION_UP && cursor->row > 0)
        cursor->row--;
    else if (direction == DIRECTION_DOWN && cursor->row < maze->getRows() - 1)
        cursor->row++;
    else if (direction == DIRECTION_RIGHT && cursor->col < maze->getCols() - 1)
        cursor->col++;
    else if (direction == DIRECTION_LEFT && cursor->col > 0)
        cursor->col--;
}

void MazeEditor::toggleWallAtCursorPosition(int direction) {
    toggleWall(cursor->row, cursor->col, direction);
}
