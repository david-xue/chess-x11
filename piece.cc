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

bool Piece::getThreats() {
 return isThreatened;
}

void Piece::update(const Posn p, bool white, bool black) {
 pos = p;
 isThreatened = owner ? black : white;
 isCovered = owner ? white : black;
}

int Piece::move(const Posn p) {
 if (board->isOccupied(p, owner) == 1) {
//  cout << "Occupied by your own piece." << endl;
  return 0;
 }
 else if (board->isExposed(pos, p, owner)) {
//  cout << "Watch out!" << endl;
  return 0;
 }
 else return canReach(p);
}

Piece::~Piece() {}
