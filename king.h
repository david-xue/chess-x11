#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King: public Piece {
  bool moved;
  bool isCastling(const Posn);
 public:
  King(ChessBoard*, char, bool);
  bool canReach(const Posn);
  int move(const Posn);
  int val(); 
};

#endif
