#include "player.h"
#include "computer.h"
#include "chessboard.h"
#include "posn.h"
#include "move.h"
#include "ai.h"
#include <vector>
#include <cstdlib>
#include "piece.h"
#include <time.h>
#include "cell.h"
using namespace std;

Computer::Computer (ChessBoard* b, bool isWhite, int lvl) : 
 Player(b, isWhite), AILevel(lvl), legalMoves(new vector<Move>) {
 b->giveaway(*this);
 srand(time(NULL));
}

void Computer::receive(Piece* p1[], Piece* p2[]) {
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

Move Computer::random() {
 int x = rand() % legalMoves->size();
 return legalMoves->at(x);
}

Move Computer::random(vector<Move> m) {
 int x = rand() % m.size();
 return m.at(x);
}


int Computer::move() {
  delete legalMoves;
  legalMoves = alllegalMove();
  if (legalMoves->size() == 0) return 0;
  Move m;
  if (AILevel == 1) {
   m = random();
  }
  if (AILevel == 2) {
   vector<Move> moves = checkingmove();
   if (moves.size()) m = random(moves);
   else {
    moves = captures();
    if (moves.size()) m = random(moves);
    else m = random();
   }
  }
  int res = board->move(m.orig, m.dest, true, true);
  if (res == 4) return 0;
  else if (res == 3) return 3;
  else return 1;
}

vector<Move> Computer::captures() {
 vector<Move> m;
 for (vector<Move>::iterator i = legalMoves->begin(); i != legalMoves->end(); i++) {
  int x = gain(*board, isWhite);
  board->move(i->orig, i->dest, false, true);
  int y = gain(*board, isWhite);
  if (y > x) m.push_back(*i);
  board->undo(false);
 }
 return m;
}

vector<Move> Computer::checkingmove() {
 vector<Move> m;
  for (vector<Move>::iterator i = legalMoves->begin(); i != legalMoves->end(); i++) {
  int res = board->move(i->orig, i->dest, false, true);
  if (res == 3) {
   board->undo(false);
   vector<Move> checkmate;
   checkmate.push_back(*i);
   return checkmate;
  }
  else {
   m.push_back(*i);
   board->undo(false);
  }
 }
 return m;
}

vector<Move> Computer::capturingmove() {
  vector<Move> capturing;
  vector<Move> fork;
  for (vector<Move>::iterator i = legalMoves->begin(); i != legalMoves->end(); i++) {
  int state = threats(*board, !isWhite);
  board->move(i->orig, i->dest, false, true);
  int res = threats(*board, !isWhite);
  if (res - state >= 2) fork.push_back(*i);
  if (res - state == 1) capturing.push_back(*i);
  board->undo(false);
 }
 return fork.size() ? fork : capturing;
}

