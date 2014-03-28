#include "chessboard.h"
using namespace std;

int ChessBoard::move(const Posn orig, const Posn dest) {
  Cell* co = board[orig.row][orig.col];
  Cell* cd = board[dest.row][dest.col];
  Piece* p = co->getPiece();
  if (!p) return 0;
  if (p.getOwner() && blackmove) return 0;
  if (!(p.getOwner()) && !blackmove) return 0;
  int res = p.move();
  if (res == 0) return 0;
  else {
   Move m;
   m.orig = orig;
   m.dest = dest;
   m.name = p->getName();
   Piece* captured = cd.takeoff();
   c.takeoff();
   if (captured) m.captured = captured->getName();
   board[dest.row][dest.col]->putPiece(p);
   if (res == 2) {
    if (orig.row < dest.row) {
     Piece* rook = board[orig.row][7]->takeoff();
     board[orig.row][orig.col + 1]->putPiece(rook);
    }
    else {0
     Piece* rook = board[orig.row][0]->takeoff();
     board[orig.row][orig.col - 1]->putPiece(rook);
    }
    m.castling = true;
   }
   if (res == 3) {
    char c;
    cout << "Enter the piece you want." << endl;
    cin >> c;
    //to be continued..
    m.promotion = c;
   }
   if (res == 4) {
    board[orig.row][dest.col]->takeoff();
    m.enpassant = true;
   }
   update();
   blackmove = !blackmove;
   turn += 1;
   record->push_back(m);
   if (check(blackmove)) {
    if (checkmate(blackmove)) {
     return 3;
    }
    else return 2;
   }
   if (stalemate(blackmove)) return 4;
  }
}
  
   
