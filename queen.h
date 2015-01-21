#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
class Queen: public Piece {
public:
	Queen(ChessBoard *, char, bool);
    int canReach(const Posn);
    
    int val();
};

#endif
