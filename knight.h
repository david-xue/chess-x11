#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: Piece {
 public:
  bool canReach(const Posn);
  bool move(const Posn);
  int val();
};

#endif
