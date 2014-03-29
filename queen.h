#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
class Queen: public Piece {
    int canReach(const Posn);
    public:
    int val();
};

#endif
