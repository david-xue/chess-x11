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
    } else if ((rowDist < 0) && (colDist > 0)) {
        direction.row = -1;
        direction.col = 1; 
    } else if ((rowDist > 0) && (colDist < 0)) {
        direction.row = 1;
        direction.col = -1;
    } else if ((rowDist < 0) && (colDist < 0)) {
        direction.row = -1;
        direction.col = -1;
    } else {
        return 0;
    }
    Posn temp;
    for (int i = 1; i < abs(rowDist); ++i) {
        temp.row = pos.row + i * directionPosn.row;
        temp.col = pos.col + i * directionPosn.col;
        if (board->isOccupied(temp,owner) > 0) return return 0;
    }
    return 1;
}
