#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
  bool moved;
  Piece* prom;

 public:
  bool canReach(const Posn);
  bool move(const Posn);
  int val();
  char getName();

};

#endif
