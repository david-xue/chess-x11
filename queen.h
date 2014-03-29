#ifndef __QUEEN_H__
#ifndef __QUEEN_H__
#include "queen.h"

class Queen: public Piece {
    int canReach(const Posn);
    public:
    int val();
};

#endif
