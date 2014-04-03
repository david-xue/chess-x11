#include "ai.h"
#include "chessboard.h"
#include "posn.h"
#include "cell.h"
#include "piece.h"
#include "move.h"
using namespace std;

vector<Move> legalMove(ChessBoard& b, Piece* p) {
 vector<Move> vec;
 Posn posn = p->getPosn();
 if (posn == Posn(-1, -1)) return vec;
 for (int r = 0; r < 8; r++) {
  for (int c = 0; c < 8; c++) {
   Posn pos(r, c);
   if (p->move(pos)) {
    Move m;
    m.mover = p;
    m.orig = posn;
    m.dest = pos;
    vec.push_back(m);
   }
  }
 }
 return vec;
}

//vector<Posn> howtocap(ChessBoard& b, const Posn me, const Posn target) {

int gain(ChessBoard& b, bool player) {
 int x = 0;
 int y = 0;
 for (int n = 1; n < 16; n++) {
  if (b.white[n]->getPosn().row >= 0) x += b.white[n]->val();
  if (b.black[n]->getPosn().row >= 0) y += b.black[n]->val();
 }
 return player ? x - y : y - x;
}

int threats(ChessBoard& b, bool player) {
 int res = 0;
 if (player) {
  for (int n = 1; n < 16; n++) {
   if (b.white[n]->isThreatened() && !b.white[n]->isCovered()) 
    res += b.white[n]->val();
  }
 } else {
  for (int n = 1; n < 16; n++) {
   if (b.black[n]->isThreatened() && !b.black[n]->isCovered()) 
    res += b.black[n]->val();
  }
 }
 return res;
}

