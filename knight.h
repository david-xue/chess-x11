#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class ChessBoard;

class Knight: public Piece {
 public:
  Knight(ChessBoard*, char, bool);
  int canReach(const Posn);
  int val();
};

#endif
