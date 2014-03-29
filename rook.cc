#include "posn.h"
#include "king.h"
#include <cstdlib>

int Rook::val() {
    return 5;
}

bool hasMoved () {return moved;}

void setMoved () {
    moved = true;
}

int Rook::canReach(const Posn posn) {
    int rowDist = posn.row - pos.row;
    int colDist = posn.col - pos.col;
    if ((rowDist > 0) && (colDist == 0)) {
        for (int i = pos.row + 1; i < posn.row; ++i) {
            if (board->isOccupied(Posn(i,pos.col),owner) > 0) return 0;
        }
    } else if ((rowDist < 0) && (colDist == 0){
        for (int i = pos.row - 1; i > posn.row; --i) {
            if (board->isOccupied(Posn(i,pos.col),owner) > 0) return 0;
        }
    } else if ((rowDist == 0) && (colDist > 0){
        for (int i = pos.col + 1; i < posn.row; ++i) {
            if (board->isOccupied(Posn(pos.row,i),owner) > 0) return 0;
        }
    } else if ((rowDist == 0) && (colDist < 0){
        for (int i = pos.col - 1; i > posn.row; --i) {
            if (board->isOccupied(Posn(pos.row,i),owner) > 0) return 0;
        }
    } else {
        return 0;
    }
    if (!moved) moved = true;
    return 1;
}
