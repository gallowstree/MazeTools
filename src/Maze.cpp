#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include "Maze.h"

Tile& Maze::getTileAt(int row, int col)const {
    return this->tiles[row][col];
}

Maze::Maze(size_t rows, size_t cols) : cols(cols),
                                       rows(rows)
{
    this->tiles = new Tile*[rows];
    srand(time(0));

    for (int r = 0; r < rows; r++)
    {
        this->tiles[r] = new Tile[cols];
        for (int c = 0; c < cols; c++)
        {
            Tile* t = new Tile();
            t->row = r;
            t->col = c;

            for (int w = 0; w < 4; w++)
                t->hasWallAt[w] = (bool) (rand() % 2);
            tiles[r][c] = *t;
        }
    }
}

size_t Maze::getRows()const {
    return this->rows;
}


size_t Maze::getCols()const {
    return this->cols;
}

