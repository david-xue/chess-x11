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

void update(const Pons p, bool white, bool black) {
 pos = p;
 isThreatened = owner ? black : white;
 isCovered = owner ? white : black;
}

Piece::~Piece() {}
