#include "pawn.h"
#include "posn.h"
#include <cstdlib>

Pawn::~Pawn() {
 delete prom;
}

int Pawn::val() {
 return prom ? prom.val() : 1;
}

char Pawn::getName() {
 return prom ? prom.getName() : name;
}

void Pawn::promote(Piece* p) {
 prom = p;
} 

int Pawn::canMove(const Posn posn) {
 Piece* p = board->getPiece(posn);
 if (owner) {
  if (posn.col == pos.col) {
   if (posn.row == pos.row + 2) {
    if (!moved) return p ? 0 : 1;
    else return 0;
   }
   else if (posn.row == pos.row + 1) 
    return p ? 0 : 1;
  }
  if (abs(posn.col - pos.col) == 1) {
   if (posn.row == pos.row + 1)
    return p ? 1 : 4;
   else return 0;
  }
 }
 else {
  if (posn.col == pos.col) {
   if (posn.row == pos.row - 2) {
    if (!moved) return p ? 0 : 1;
    else return 0;
   }
   else if (posn.row == pos.row - 1) 
    return p ? 0 : 1;
  }
  if (abs(posn.col - pos.col) == 1) {
   if (posn.row == pos.row - 1)
    return p ? 1 : 4;
   else return 0;
  }
 }
}
