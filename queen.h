#ifndef __QUEEN_H__
#ifndef __QUEEN_H__
#include "queen.h"

class Queen: public Piece {
 public:
  bool canReach(const Posn);
  bool move(const Posn); 
  int val();
};

#endif
