#include "posn.h"
#include "queen.h"
#include <cstdlib>

Queen::Queen(ChessBoard* b, char c, bool player) : Piece(b, c, player){}

int Queen::val() {
    return 9;
}

int Queen::canReach(const Posn posn) {
    int rowDist = posn.row - pos.row;
    int colDist = posn.col - pos.col;
    Posn direction(0,0);
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
    Posn temp(pos.row, pos.col);
    if ((direction.row != 0) && (direction.col != 0)) {
        if (abs(rowDist) != abs(colDist)) return 0;
        for (int i = 1; i < abs(rowDist); ++i) {
            temp.row += i * direction.row;
            temp.col += i * direction.col;
            if (board->isOccupied(temp,owner) > 0) return 0;
        }
    } else if (direction.row != 0) {
        for (int i = 1; i < abs(rowDist); ++i) {
            temp.row += i * direction.row;
            if (board->isOccupied(temp,owner) > 0) return 0;
        }
    } else {
        for (int i = 1; i < abs(colDist); ++i) {
            temp.col += i * direction.col;
            if (board->isOccupied(temp,owner) > 0) return 0;
        }
    }
    return 1;
}
