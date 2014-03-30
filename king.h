#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King: public Piece {
  bool moved;
  bool isCastling(const Posn);

public:
  King (ChessBoard *, char, bool);
  int canReach(const Posn);
  int move(const Posn);
  int val();
  void setMoved(const bool);
};

#endif
