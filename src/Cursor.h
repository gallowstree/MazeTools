//
// Created by Alvarado, Alejandro on 5/25/17.
//

#ifndef TEST_CLIENT_CURSOR_H
#define TEST_CLIENT_CURSOR_H
class Cursor {
public:
    int row = 0;
    int col = 0;
    bool isTileHighlighted(int row, int col) {
        return row == this->row && col == this->col;
    }
};

#endif //TEST_CLIENT_CURSOR_H
