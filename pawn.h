#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
  bool moved;
  Piece* prom;
 
  int isenPassant(const Posn);
  int canReach(const Posn);

 public:
  ~Pawn();
  int val();
  char getName();
  void promote(Piece*);
  void unpromote();

};

#endif
