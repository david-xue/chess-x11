#include <iostream>
#include "cell.h"
#include "piece.h"
#include "graphdisplay.h"
using namespace std;

Cell::Cell(Posn p, GraphDisplay* gp): pos(p), p(NULL),gp(gp) {}

Piece* Cell::getPiece() {
 return p;
}

void Cell::putPiece(Piece* piece, bool updateScreen) {
  takeoff(updateScreen);
  p = piece;
  if (p) {
      p->update(pos, wcanreach, bcanreach);
    if(gp && updateScreen) gp->draw(p->getName(),pos);
  }
}

Piece* Cell::takeoff(bool updateScreen) {
 Piece* temp = p;
 vector<Piece*> v;
 p = 0;
if (gp && updateScreen) gp->undraw(pos);
 Posn n (-1, -1);
 if (temp) temp->update(n, v, v);
 return temp;
}

vector<Piece*> Cell::getWhiteReach() {
 return wcanreach;
}

vector<Piece*> Cell::getBlackReach() {
 return bcanreach;
}

void Cell::update(vector<Piece*> white, vector<Piece*> black) {
 wcanreach = white;
 bcanreach = black;
 if (p) p->update(pos, wcanreach, bcanreach);
}

