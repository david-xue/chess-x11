#include <iostream>
#include "cell.h"
#include "piece.h"
#include "graphdisplay.h"
Cell::Cell(Posn p, GraphDisplay* gp): pos(p), gp(gp) {}

Piece* Cell::getPiece() {
 return p;
}

void Cell::putPiece(Piece* piece) {
  takeoff();
  p = piece;
  if (p) {
      p->update(pos, wcanreach, bcanreach);
      //gp->draw(p->getName(),pos);
  }
}

Piece* Cell::takeoff() {
 Piece* temp = p;
 p = 0;
// gp->undraw(pos);
 Posn n (-1, -1);
 if (temp) temp->update(n, false, false);
 return temp;
}

bool Cell::getWhiteReach() {
 return wcanreach;
}

bool Cell::getBlackReach() {
 return bcanreach;
}

void Cell::update(bool white, bool black) {
 wcanreach = white;
 bcanreach = black;
 if (p) p->update(pos, wcanreach, bcanreach);
}

