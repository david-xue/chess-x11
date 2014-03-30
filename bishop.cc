#include "posn.h"
#include "bishop.h"
#include "piece.h"
#include <cstdlib>


Bishop::Bishop(ChessBoard* b, char c, bool player) : Piece(b, c, player){}
class ChessBoard;
int Bishop::val() {
    return 3;
}

int Bishop::canReach(const Posn posn) {
    int rowDist = posn.row - pos.row;
    int colDist = posn.col - pos.col;
    if (abs(rowDist) != abs(colDist)) return 0;
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
        return 0;
    }
    Posn temp (0,0);
    for (int i = 1; i < abs(rowDist); ++i) {
        temp.row = pos.row + i * direction.row;
        temp.col = pos.col + i * direction.col;
        if (board->isOccupied(temp,owner) > 0) return 0;
    }
    return 1;
}
