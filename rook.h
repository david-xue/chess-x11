#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class Rook: public Piece {
 public:
  bool canReach(const Posn);
  bool move(const Posn);
  int val();
};

#endif
