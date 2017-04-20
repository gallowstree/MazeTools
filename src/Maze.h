//
// Created by Alvarado, Alejandro on 4/15/17.
//

#ifndef TEST_CLIENT_LABYRINTH_H
#define TEST_CLIENT_LABYRINTH_H


#include "Tile.h"

class Maze {

private:
    Tile **tiles;
    size_t rows = 10;
    size_t cols = 10;
    int tileSize = 20;

public:
    Maze(size_t rows, size_t cols);
    Tile& getTileAt(int row, int col) const;

    size_t getRows() const;
    size_t getCols() const;
};


#endif //TEST_CLIENT_LABYRINTH_H
