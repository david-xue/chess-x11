#include "chessboard.h"
#include "posn.h"
#include "move.h"
#include "cell.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
using namespace std;

void ChessBoard::update() {
 Posn p;
 for (int n = 0; n < 8; n++) {
  for (int m = 0; m < 8; m++) {
   p.row = n;
   p.col = m;
   bool w, b;
   for (int l = 0; l < 16; l++) {
    if (white[l]->canReach(p)) w = true;
    if (black[l]->canReach(p)) b = true;
   }
   board[n][m]->update(w, b);
  }
 }
}

int ChessBoard::move(const Posn orig, const Posn dest) {
  Cell* co = board[orig.row][orig.col];
  Cell* cd = board[dest.row][dest.col];
  Piece* p = co->getPiece();
  if (!p) return 0;
  if (p->getOwner() && blackmove) return 0;
  if (!(p->getOwner()) && !blackmove) return 0;
  int res = p->move(dest);
  if (res == 0) return 0;
  else {
    Move m = {p, cd->takeoff(), orig, dest, false, false, 0};
   co->takeoff();
   cd->putPiece(p);
  if (res == 2) {
        // for castling, King would've checked all conditions except for rook's part  
        Piece * rook;
        // I'll clean up these ridiculous conditions later...
      if (orig.col < dest.col) {
          rook = board[orig.row][7]->getPiece();
          if ((isExposed(Posn(orig.row, 7), Posn(orig.row, 5), rook->getOwner())) || rook->hasMoved() || (rook->getOwner() != p->getOwner())) {
                cd->takeoff();
                co->putPiece(p);
                p->setMoved(false);
                return 0;
            } 
            rook = board[orig.row][7]->takeoff();
            board[orig.row][5]->putPiece(rook);
        } else { 
            rook = board[orig.row][0]->getPiece();
          if ((isExposed(Posn(orig.row, 0), Posn(orig.row, 3), rook->getOwner())) || rook->hasMoved() || (rook->getOwner() != p->getOwner())) {
                cd->takeoff();
                co->putPiece(p);
                p->setMoved(false);
                return 0;
            } 
            rook = board[orig.row][0]->takeoff();
            board[orig.row][3]->putPiece(rook);
        }
        m.castling = true;
        rook->setMoved(true);
    }
   if (res == 3) {
    char c;
    cout << "Enter the piece you want." << endl;
    cin >> c;
    //to be continued..
    m.promotion = true;
   }
   if (res == 4) {
    m.enpassant = board[orig.row][dest.col]->takeoff();
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

void ChessBoard::undo() {
 Move m = record->back();
 Cell* co = board[m.orig.row][m.orig.col];
 Cell* cd = board[m.dest.row][m.orig.col];
 cd->putPiece(m.captured);
 co->putPiece(m.mover);
 if (m.promotion) {
  Pawn* pawn = static_cast<Pawn*>(m.mover);
  pawn->unpromote();
 }
 if (m.castling) {
  if (m.orig.col < m.dest.col) {
    Piece* rook = board[m.orig.row][5]->takeoff();
    board[m.orig.row][7]->putPiece(rook);
  }
  else {
   Piece* rook = board[m.orig.row][3]->takeoff();
   board[m.orig.row][0]->putPiece(rook);
  }
 }
 if (m.enpassant) {
  board[m.orig.row][m.dest.col]->putPiece(m.enpassant);
 }
 update();
 record->pop_back();
 blackmove = !blackmove;
 turn -= 1;
}
  
bool ChessBoard::isExposed(const Posn orig, const Posn dest, bool player) {
 Cell* co = board[orig.row][orig.col];
 Cell* cd = board[dest.row][dest.col];
 Piece* p1 = co->takeoff();
 Piece* p2 = cd->takeoff();
 cd->putPiece(p1);
 bool res = false;
 if (player) {
  for (int n = 0; n < 16; n++) {
   if ((black[n]->getPosn()).row != -1) {
    if (black[n]->canReach(white[0]->getPosn()))
     res = true;
   }
  }
 }
 else {
  for (int n = 0; n < 16; n++) {
   if ((white[n]->getPosn()).row != -1) {
    if (white[n]->canReach(black[0]->getPosn()))
     return true;
   }
  }
 }
 cd->putPiece(p2);
 co->putPiece(p1);
 return res;
} 

int ChessBoard::isOccupied(const Posn posn, bool player) {
 Piece* p = board[posn.row][posn.col]->getPiece();
 if (!p) return 0;
 else if (p->getOwner() == player) return 1;
 else return 2;
}


bool ChessBoard::isAttacked(const Posn posn, bool opponent) {
    if (opponent) {
        return board[posn.row][posn.col]->getWhiteReach();
    } else {
        return board[posn.row][posn.col]->getBlackReach();
    }
}

bool ChessBoard::isWhiteMove() {
    return !blackMove;
}
