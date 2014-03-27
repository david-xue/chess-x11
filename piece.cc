#include "piece.h"

Piece::Piece(ChessBoard* b): board(b) {}

char Piece::getName() {
 return name;
}

bool Piece::getOwner() {
 return owner;
}

Posn getPosn() {
 return pos;
}

void update(const Pons p, bool t, bool c) {
 pos = p;
 isThreatened = t;
 isCovered = c;
}
