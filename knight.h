#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: public Piece {
  int canReach(const Posn);
 public:
  int val();
};

#endif
