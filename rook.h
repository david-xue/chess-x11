#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class ChessBoard;

class Rook: public Piece {
    bool moved;
public:
    Rook(ChessBoard*, char, bool);
    int canReach(const Posn); 
    int val();
    bool hasMoved();
    void setMoved( const bool );
};

#endif
