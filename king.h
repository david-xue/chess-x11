#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class ChessBoard;
class King: public Piece {
  bool moved;
  bool isCastling(const Posn);

public:
  King (ChessBoard *, char, bool);
  int canReach(const Posn);
  int move(const Posn);
  int val();
  void update(const Posn, bool, bool);
};

#endif
