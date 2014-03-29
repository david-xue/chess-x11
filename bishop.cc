#include "posn.h"
#include "bishop.h"
#include <cstdlib>

int Bishop::val() {
    return 3;
}

int Bishop::canReach(const Posn posn) {
    int rowDist = posn.row - pos.row;
    int colDist = posn.col - pos.col;
    if (abs(rowDist) != abs(colDist)) return 0;
    Posn directionPosn;
    if ((rowDist > 0) && (colDist > 0)) {
        direction.row = direction.col = 1;
        /*
        for (int i = pos.row + 1; i < posn.row; ++i) {
            if (board->isOccupied(Posn(i,pos.col),owner) > 0) return 0;
        } */
    } else if ((rowDist < 0) && (colDist > 0)) {
        direction.row = -1;
        direction.col = 1;
        /*
        for (int i = pos.row - 1; i > posn.row; --i) {
            if (board->isOccupied(Posn(i,pos.col),owner) > 0) return 0;
        }
        */
    } else if ((rowDist > 0) && (colDist < 0)) {
        direction.row = 1;
        direction.col = -1;
        /*
        for (int i = pos.col + 1; i < posn.row; ++i) {
            if (board->isOccupied(Posn(pos.row,i),owner) > 0) return 0;
        }
        */
    } else if ((rowDist == 0) && (colDist < 0)) {
        direction.row = -1;
        direction.col = -1;
        /*for (int i = pos.col - 1; i > posn.row; --i) {
            if (board->isOccupied(Posn(pos.row,i),owner) > 0) return 0;
        }*/
    } else {
        return 0;
    }
    if (!moved) moved = true;
    return 1;
}
