#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
  bool moved;
  Piece* prom;
 
  int isenPassant(const Posn);
 public:
  Pawn(ChessBoard*, char, bool);
  int canReach(const Posn);  
  ~Pawn();
  void update(const Posn, bool, bool);
  int val();
  char getName();
  void promote(Piece*);
  void unpromote();

};

#endif
