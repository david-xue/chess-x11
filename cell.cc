#include "cell.h"
#include "piece.h"

Cell::Cell(Posn p): pos(p) {}

Piece* Cell::getPiece() {
 return p;
}

void Cell::putPiece(Piece* piece) {
  p = piece;
  p->update(pos, wcanreach, bcanreach);
}

Piece* Cell::takeoff() {
 Piece* temp = p;
 p = 0;
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
}

