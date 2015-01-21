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
#include "aitree.h"
#include "opening.h"
using namespace std;

Computer::Computer (ChessBoard* b, bool isWhite, int lvl) : 
 Player(b, isWhite), AILevel(lvl) {
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

vector<Move> Computer::alllegalMove() {
 vector<Move> vec;
 for (int n = 0; n < 16; n++) {
  vector<Move> v = legalMove(*board, own[n]);
  for (vector<Move>::iterator i = v.begin(); i != v.end(); i++) {
    vec.push_back(*i);
  }
 }
 return vec;
}

Move Computer::random() {
 int x = rand() % legalMoves.size();
 return legalMoves.at(x);
}

Move Computer::random(vector<Move> m) {
 int x = rand() % m.size();
 return m.at(x);
}


int Computer::move() {
  MoveNode opening;
  opening.init();
  Move m = opening.getnextMove(*(board->getRecord()));
  if (m.orig.row < 0) {
  legalMoves = alllegalMove();
  if (legalMoves.size() == 0) return 0;
  if (AILevel == 1) {
   m = random();
  }
  if (AILevel == 2) {
   vector<Move> moves = checkingmove();
   if (moves.size()) m = random(moves);
   else {
    moves = captures();
    if (moves.size()) m = random(moves);
    else {
     moves = capturingmove();
     if (moves.size()) m = random(moves);
     else m = random();
    }
   }
  }
  if (AILevel == 3) {
   vector<Move> moves = safecheckingmove();
   if (moves.size()) {
    m = random(moves);
    cout << "This is a safe checking move." << endl;
   }
   else {
    moves = safecaptures();
    if (moves.size()) {
     m = random(moves);
     cout << "This is a safe capture." << endl;
    }
    else {
     moves = safecapturingmove();
     if (moves.size()) {
      m = random(moves);
      cout << "This is a safe capturing move." << endl;
     }
     else {
      moves = safemove();
      if (!moves.empty()) {
       m = random(moves);
       cout << "This is a safe move." << endl;
      }
      else m = random();
     }
    }
   }
  }
  if (AILevel == 4) {
	  MoveTree tree = MoveTree(board, 0, !isWhite, NULL, isWhite, 0);
	  pair <int,vector <Move*> > bestMove = tree.getBestMove();
	  vector <Move*> * temp = &(bestMove.second);
	  int iter = 0;

	  while (iter < temp->size()) {
		  if (temp->at(iter)) m = *(temp->at(iter));
		  iter++;
	  }
    /*  iter--;
    if (temp->at(iter)){
      while ( (temp->at(iter)->orig.row == -1 ) || ( temp->at(iter)->dest.row == -1)) {
        iter--;
          if (temp->at(iter)) m = *(temp->at(iter));
           }}*/
  }
  if (m.orig.row == -1) {
	cout << "AI4 Checkmate possible" << endl;
	AILevel = 3;
	m = random();
  }
 }
  int res = board->move(m.orig, m.dest, true, true);

  if (res == 4) return 0;
  else if (res == 3) return 3;
  else {
   if (res == 2) cout << (isWhite ? "White checks black." : "Black checks white.") << endl;
   return 1;
  }
}

int min_piece(vector<Piece*>* pieces) {
  int n = pieces->at(0)->val();
  for (vector<Piece*>::iterator i = pieces->begin(); i != pieces->end(); i++) {
   if ((*i)->val() < n) n = (*i)->val();
  }
  return n;
}

int max_piece(vector<Piece*>* pieces) {
  int n = pieces->at(0)->val();
  for (vector<Piece*>::iterator i = pieces->begin(); i != pieces->end(); i++) {
   if ((*i)->val() > n) n = (*i)->val();
  }
  return n;
}

bool Computer::isSafe(Move m) {
 board->move(m.orig, m.dest, false, true);
 for (int n = 0; n < 16; n++) {
  if (own[n]->isThreatened() && !own[n]->isCovered()) {
   board->undo(false);
   return false;
  }
  vector<Piece*> threats = own[n]->getThreats();
  if (!threats.empty() && min_piece(&threats) < own[n]->val()) {
   board->undo(false);
   return false;
  }
 }
 board->undo(false);
 return true;
}


vector<Move> Computer::safemove() {
 vector<Move> m;
 for (vector<Move>::iterator i = legalMoves.begin(); i != legalMoves.end(); i++) {
  if (isSafe(*i) ) m.push_back(*i);
 }
 return m;
}

vector<Move> Computer::captures() {
 vector<Move> m;
 for (vector<Move>::iterator i = legalMoves.begin(); i != legalMoves.end(); i++) {
  int x = gain(*board, isWhite);
  board->move(i->orig, i->dest, false, true);
  int y = gain(*board, isWhite);
  if (y > x) m.push_back(*i);
  board->undo(false);
 }
 return m;
}

vector<Move> Computer::safecaptures() {
 vector<Move> move;
 vector<Move> m = captures();
 for (vector<Move>::iterator i = m.begin(); i != m.end(); i++) {
  if (isSafe(*i)) move.push_back(*i);
 }
 return move;
}

vector<Move> Computer::checkingmove() {
 vector<Move> m;
 vector<Move> checkmate;
  for (vector<Move>::iterator i = legalMoves.begin(); i != legalMoves.end(); i++) {
  int res = board->move(i->orig, i->dest, false, true);
  if (res == 3) {
   checkmate.push_back(*i);
   break;
  }
  else if (res == 2) {
   m.push_back(*i);
  }
  board->undo(false);
 }
 return checkmate.size() ? checkmate : m;
}

vector<Move> Computer::safecheckingmove() {
 vector<Move> m = checkingmove();
 vector<Move> move;
 if (m.empty()) return m;
 if (board->move(m.at(0).orig, m.at(0).dest, false, true) == 3) return m;
 else {
  for (vector<Move>::iterator i = m.begin(); i != m.end(); i++) {
   if (isSafe(*i)) move.push_back(*i); 
  }
 }
 return move;
}


vector<Move> Computer::capturingmove() {
  vector<Move> capturing;
  for (vector<Move>::iterator i = legalMoves.begin(); i != legalMoves.end(); i++) {
  int state = threats(*board, !isWhite);
  board->move(i->orig, i->dest, false, true);
  int res = threats(*board, !isWhite);
  if (res > state) capturing.push_back(*i);
  for (int n = 0; n < 16; n++) {
   Piece* p = i->mover;
   if (opp[n]->getPosn().row < 0) continue;
   if (p->move(opp[n]->getPosn()) && p->val() < opp[n]->val()) 
     capturing.push_back(*i);
  }
  board->undo(false);
 }
 return capturing;
}

vector<Move> Computer::safecapturingmove() {
  vector<Move> m = capturingmove();
  vector<Move> move;
  for (vector<Move>::iterator i = m.begin(); i != m.end(); i++) {
   if (isSafe(*i)) move.push_back(*i);
  }
 return move;
}


