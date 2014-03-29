#include "posn.h"
#include "queen.h"
#include <cstdlib>

int Queen::val() {
    return 9;
}

int Queen::canReach(const Posn posn) {
    int rowDist = posn.row - pos.row;
    int colDist = posn.col - pos.col;
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
    }
    Posn temp;
    if ((direction.row != 0) && (direction.col != 0)) {
        if (abs(rowDist) != abs(colDist)) return 0;
        for (int i = 1; i < abs(rowDist); ++i) {
            temp.row = pos.row + i * directionPosn.row;
            temp.col = pos.col + i * directionPosn.col;
            if (board->isOccupied(temp,owner) > 0) return return 0;
        }
    } else if (direction.row != 0) {
        for (int i = 1; i < abs(rowDist); ++i) {
            temp.row = pos.row + i * directionPosn.row;
            if (board->isOccupied(temp,owner) > 0) return return 0;
        }
    } else {
        for (int i = 1; i < abs(colDist); ++i) {
            temp.col = pos.col + i * directionPosn.col;
            if (board->isOccupied(temp,owner) > 0) return return 0;
        }
    }
    return 1;
}
