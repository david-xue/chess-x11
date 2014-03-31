#include "ai.h"
#include "chessboard.h"
#include "posn.h"
#include "cell.h"
#include "piece.h"
using namespace std;

vector<Posn>* legalMove(ChessBoard& b, const Posn p) {
 vector<Posn>* vec = new vector<Posn>;
 Piece* m = b.board[p.row][p.col]->getPiece();
 if (m == 0) return vec;
 for (int r = 0; r < 8; r++) {
  for (int c = 0; c < 8; c++) {
   Posn pos(r, c);
   if (m->move(pos)) vec->push_back(pos);
  }
 }
 return vec;
}
