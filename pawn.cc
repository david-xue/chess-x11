#include "pawn.h"
#include "posn.h"
#include "move.h"
#include <cstdlib>
#include <vector>
#include "chessboard.h"

Pawn::Pawn(ChessBoard* b, char c, bool player) : Piece(b, c, player){}

Pawn::~Pawn() {
 delete prom;
}

int Pawn::val() {
 return prom ? prom->val() : 1;
}

char Pawn::getName() {
 return prom ? prom->getName() : name;
}

void Pawn::promote(Piece* p) {
 prom = p;
} 
 
int Pawn::canReach(const Posn posn) {
 int o = board->isOccupied(posn, owner);
 if (owner) {
  if (posn.col == pos.col) {
   if (posn.row == pos.row - 2) {
    if (!moved) return o ? 0 : 1;
    else return 0;
   }
   else if (posn.row == pos.row - 1) 
    return o ? 0 : (posn.row == 0 ? 3 : 1);
  }
  if (abs(posn.col - pos.col) == 1) {
   if (posn.row == pos.row - 1) {
    return o ? (posn.row == 0 ? 3 : 1) : isenPassant(posn);
   }
   else return 0;
  }
 }
 else {
  if (posn.col == pos.col) {
   if (posn.row == pos.row + 2) {
    if (!moved) return o ? 0 : (posn.row == 7 ? 3 : 1);
    else return 0;
   }
   else if (posn.row == pos.row + 1) 
    return o ? 0 : (posn.row == 7 ? 3 : 1);
  }
  if (abs(posn.col - pos.col) == 1) {
   if (posn.row == pos.row + 1) {
    return o ? (posn.row == 7 ? 3 : 1) : isenPassant(posn);
   }
   else return 0;
  }
 }
 return 0;
}

int Pawn::isenPassant(const Posn posn) {
 Posn p (pos.row, posn.col);
 if (board->getRecord()->size() == 0) return 0;
 Move m = (board->getRecord())->back();
 Posn o (owner ? 1 : 6, posn.col);
 if (m.orig == o && m.dest == p && m.name == (owner ? 'p' : 'P')) {
  return 4;
 }
 else return 0;
}

void Pawn::unpromote() {
 delete prom;
 prom = 0;
}

