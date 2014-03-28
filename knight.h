#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: Piece {
 public:
  int canMove(const Posn);
  int val();
};

#endif
