#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King: public Piece {
  bool moved;
 public:
  bool canReach(const Posn);
  bool move(const Posn);
  int val(); 
};

#endif
