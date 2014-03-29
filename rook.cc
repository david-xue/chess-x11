#include "posn.h"
#include "rook.h"
#include <cstdlib>

int Rook::val() {
    return 5;
}

bool Rook::hasMoved () {return moved;}

void Rook::setMoved (const bool moved) {
    this->moved = moved;
}

int Rook::canReach(const Posn posn) {
    int rowDist = posn.row - pos.row;
    int colDist = posn.col - pos.col;
    Posn direction (0,0);
    if ((rowDist > 0) && (colDist == 0)) {
        direction.row = 1;
    } else if ((rowDist < 0) && (colDist == 0)) {
        direction.row = -1; 
    } else if ((rowDist == 0) && (colDist > 0)) {
        direction.col = 1;
    } else if ((rowDist == 0) && (colDist < 0)) {
        direction.col = -1;
    } else {
        return 0;
    }
    Posn temp (0,0);
    if (direction.row != 0) {
        for (int i = 1; i < abs(rowDist); ++i) {
            temp.row = pos.row + i * direction.row;
            if (board->isOccupied(temp,owner) > 0) return 0;
        }
    } else {
        for (int i = 1; i < abs(colDist); ++i) {
            temp.col = pos.col + i * direction.col;
            if (board->isOccupied(temp,owner) > 0) return 0;
        }
    }
    if (!moved) moved = true;
    return 1;
}
