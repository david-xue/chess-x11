#include "piece.h"
#include "chessboard.h"
#include "posn.h"
using namespace std;

Piece::Piece(ChessBoard* b, char c, bool o): 
 name(c), owner(o), board(b), pos(Posn(-1, -1)) {
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

int Piece::move(const Posn p) {
 if (board->isOccupied(p, owner) == 1) {
  return 0;
 }
 else if (board->isExposed(pos, p, owner)) {
  return 0;
 }
 else return canReach(p);
}

Piece::~Piece() {}
