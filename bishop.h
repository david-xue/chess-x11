#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class ChessBoard;
class Bishop: Piece {
    public:
    Bishop(ChessBoard*, char, bool);
	int canReach(const Posn);
    int val();
};

#endif
