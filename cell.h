#ifndef __CELL_H__
#define __CELL_H__

class Piece;
struct Posn;

class Cell {
  const Posn pos;
  Piece* p;
  bool wcanreach;
  bool bcanreach;

 public:
 

  Piece* getPiece();
  void putPiece(Piece*);
  Piece* takeoff();
  void update(bool, bool);
  bool getWhiteReach();
  bool getBlackReach();

};

#endif
