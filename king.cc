#include "posn.h"
#include "king.h"
#include <vector>
#include <cstdlib>

// Does King need its own constructor because of moved? (I think this depends on the compiler)
King::King(ChessBoard* b, char c, bool o): 
    board(b), name(c), owner(o), moved(false) {
    pos.row = pos.col = -1;
}

int King::val() {
    // what is it? 4? or some huge value?
    return 10000;
}
 
int King::canReach(const Posn posn) {
    int rowDist = abs(posn.row - pos.row);
    int colDist = abs(posn.col - pos.col);
    if (((rowDist == 0) && (colDist == 1)) || ((rowDist == 1) && (colDist == 0))) {
        moved = true;
        return 1;
    } else {
        if (isCastling(posn)) {
            moved = true;
            return 2;
        else {
            return 0;
        }
    }
}

bool King::isCastling(const Posn posn) {
    if (!moved) {
            if (pos.row != posn.row) return false;
            if ((pos.row != 0) && owner) return false;
            if ((pos.row != 7) && (!owner)) return false;

            if (pos.col != 4) return false;
            Posn tempP = {pos.row, 0}; 
            if (posn.col == 2) {
                tempP.col = 3;
                if ((board->isOccupied(posn, tempP, owner) != 0) && (board->isAttacked(tempP, !owner))) return false;
                tempP.col = 1;
                if (board->isOccupied(posn, tempP, owner) != 0) return false;
            } else (posn.col == 6) {
                tempP.col = 5;
                if ((board->isOccupied(posn, tempP, owner) != 0) && (board->isAttacked(tempP, !owner))) return false;
            }
            if (board->isAttacked(pos, !owner)) {
                return false;
            } else {
                return true;
            }

    } else {
        return false;
    }
}
                    
/*
int King::move(const Posn posn) {
    if (board->isOccupied(posn, owner) == 1) {
        return 0;
    } else if (isCastling(posn)) {
        moved = true;
        return 2;
    } else if (canReach(posn)) {
        if (board->isExposed(pos, posn, owner)) {
            if (!moved) {
                moved = true;
            }
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
*/

void King::setMoved(const bool hasMoved) {
    moved = hasMoved;
}
