#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop: Piece {
    bool canReach(const Posn);
    public:
    int val();
};

#endif
