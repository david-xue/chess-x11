#include "ai.h"
#include "chessboard.h"
#include "posn.h"
#include "cell.h"
#include "piece.h"
using namespace std;

vector<Posn> legalMove(ChessBoard& b, const Posn p) {
 vector<Posn> vec;
 Piece* m = b.board[p.row][p.col]->getPiece();
 if (m == 0) return vec;
 for (int r = 0; r < 8; r++) {
  for (int c = 0; c < 8; c++) {
   Posn pos(r, c);
   if (m->move(pos)) vec.push_back(pos);
  }
 }
 return vec;
}

//vector<Posn> howtocap(ChessBoard& b, const Posn me, const Posn target) {

int gain(ChessBoard& b, bool player) {
 int x,y;
 for (int n = 0; n < 16; n++) {
  if (b.white[n]->getPosn().row >= 0) x += b.white[n]->val();
  if (b.black[n]->getPosn().row >= 0) y += b.black[n]->val();
 }
 return player ? x - y : y - x;
}

int threats(ChessBoard& b, bool player) {
 int res;
 if (player) {
  for (int n = 1; n < 16; n++) {
   if (b.white[n]->getThreats().size() && b.white[n]->getCovers().size() == 0) res += 1;
  }
 } else {
  for (int n = 1; n < 16; n++) {
   if (b.black[n]->getThreats().size() && b.black[n]->getCovers().size() == 0) res += 1;
  }
 }
 return res;
}

