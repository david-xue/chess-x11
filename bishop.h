#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop: Piece {
 public:
  bool canReach(const Posn);
  bool move(const Posn);
  int val();
};

#endif
