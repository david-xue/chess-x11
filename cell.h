#ifndef __CELL_H__
#define __CELL_H__
#include "posn.h"
#include <vector>

class Piece;
class GraphDisplay;

class Cell {
  const Posn pos;
  Piece* p;
  std::vector<Piece*> wcanreach;
  std::vector<Piece*> bcanreach;

  GraphDisplay *gp;

 public:
 
  Cell(Posn, GraphDisplay*);
  Piece* getPiece();
  void putPiece(Piece*, bool updateScreen = true);//will takeoff the occupying piece
  Piece* takeoff(bool updateScreen = true);//the posn of piece taken off is set (-1, -1)
  void update(std::vector<Piece*>, std::vector<Piece*>);
  std::vector<Piece*> getWhiteReach();
  std::vector<Piece*> getBlackReach();

};

#endif
