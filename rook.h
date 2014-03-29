#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class Rook: public Piece {
    bool moved;
    int canReach(const Posn);
public: 
    int val();
    bool hasMoved();
    bool setMoved(const bool);
};

#endif
