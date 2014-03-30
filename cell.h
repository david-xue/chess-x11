#ifndef __CELL_H__
#define __CELL_H__
#include "posn.h"

class Piece;
class GraphDisplay;

class Cell {
  const Posn pos;
  Piece* p;
  bool wcanreach;
  bool bcanreach;

  GraphDisplay *gp;

 public:
 
  Cell(Posn, GraphDisplay*);
  Piece* getPiece();
  void putPiece(Piece*);//will takeoff the occupying piece
  Piece* takeoff();//the posn of piece taken off is set (-1, -1)
  void update(bool, bool);
  bool getWhiteReach();
  bool getBlackReach();

};

#endif
