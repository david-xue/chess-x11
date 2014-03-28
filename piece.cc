#include "piece.h"

Piece::Piece(ChessBoard* b, char c, bool o): 
 board(b), name(c), owner(o) {
 pos.row = pos.col = -1;
}

char Piece::getName() {
 return name;
}

bool Piece::getOwner() {
 return owner;
}

Posn Piece::getPosn() {
 return pos;
}

void Piece::update(const Posn p, bool white, bool black) {
 pos = p;
 isThreatened = owner ? black : white;
 isCovered = owner ? white : black;
}

Piece::~Piece() {}
