#include "player.h"
#include "computer.h"
#include "chessboard.h"
#include "posn.h"
#include "move.h"
#include "ai.h"
#include <vector>
#include <cstdlib>
#include "piece.h"
using namespace std;

Computer::Computer (ChessBoard* b, bool isWhite, int lvl) : 
 Player(b, isWhite), AILevel(lvl) {
 b->passPiece(*this, isWhite);
}

void Computer::passPiece(Piece* p[]) {
 for (int n = 0; n < 16; n++) {
  piece[n] = p[n];
 }
}

void Computer::setAILevel(int lvl) {AILevel = lvl;}

int Computer::move() {
  if (AILevel == 1) return random();
  else return 0;
}

int Computer::random() {
 vector<Move> move;
 for (int n = 0; n < 16; n++) {
  vector<Posn>* pos = legalMove(*board, piece[n]->getPosn());
  for (vector<Posn>::iterator i = pos->begin(); i != pos->end(); i++) {
   Move m;
   m.orig = piece[n]->getPosn();
   m.dest = *i;
   move.push_back(m);
  }
  delete pos;
 }
 if (move.size() == 0) return 0;
 else {
  int x = rand() % move.size();
  bool res = board->move(move.at(x).orig, move.at(x).dest);
  if (res == 4) return 0;
  else if (res == 3) return 3;
  else return 1;
 }
}
  

 


