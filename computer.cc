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

void Computer::passPiece(Piece* p1[], Piece* p2[]) {
 for (int n = 0; n < 16; n++) {
  if (isWhite) {
   own[n] = p1[n];
   opp[n] = p2[n];
  } else {
   own[n] = p2[n];
   opp[n] = p1[n];
  }
 }
}

void Computer::setAILevel(int lvl) {AILevel = lvl;}

vector<Move>* Computer::alllegalMove() {
 vector<Move>* vec = new vector<Move>;
 for (int n = 0; n < 16; n++) {
  Posn p = own[n]->getPosn();
  if (p.row < 0) continue;
  vector<Posn> v = legalMove(*board, p);
  for (vector<Posn>::iterator i = v.begin(); i != v.end(); i++) {
   Move m;
   m.orig = p;
   m.dest = *i;
   vec->push_back(m);
  }
 }
 return vec;
}

int Computer::move() {
  if (AILevel == 1) return random();
  else return 0;
}

int Computer::random() {
 vector<Move>* move = alllegalMove();
 if (move->size() == 0) return 0;
 else {
  int x = rand() % move->size();
  bool res = board->move(move->at(x).orig, move->at(x).dest);
  if (res == 4) return 0;
  else if (res == 3) return 3;
  else return 1;
 }
}
  

 


