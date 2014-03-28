#ifndef __CELL_H__
#define __CELL_H__
#include "posn.h"

class Piece;

class Cell {
  const Posn pos;
  Piece* p;
  bool wcanreach;
  bool bcanreach;

 public:
 
  Cell(Posn);
  Piece* getPiece();
  void putPiece(Piece*);
  Piece* takeoff();
  void update(bool, bool);
  bool getWhiteReach();
  bool getBlackReach();

};

#endif
