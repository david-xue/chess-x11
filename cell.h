#ifndef __CELL_H__
#define __CELL_H__

class Piece;

class Cell {
  Piece* p;
  bool WhiteThreats;
  bool BlackThreats;

 public:
  Piece* getPiece();
  void putPiece(Piece*);
  void takeoff();
  void updateThreats(bool, bool);

};

#endif
