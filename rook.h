#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class ChessBoard;

class Rook: public Piece {
public:
    Rook(ChessBoard*, char, bool);
    int canReach(const Posn); 
    int val();
};

#endif
