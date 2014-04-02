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
  Posn p = own[n]->getPosn();
  if (p.row < 0) continue;
  vector<Posn> v = legalMove(*board, p);
  for (vector<Posn>::iterator i = v.begin(); i != v.end(); i++) {
   Move m;
   m.orig = p;
   m.dest = *i;
   vec.push_back(m);
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
  legalMoves = alllegalMove();
  if (legalMoves.size() == 0) return 0;
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
    else {
     moves = capturingmove();
     if (moves.size()) m = random(moves);
     else m = random();
    }
   }
  }
  if (AILevel == 3) {
   vector<Move> moves = safecheckingmove();
   if (moves.size()) m = random(moves);
   else {
    moves = safecaptures();
    if (moves.size()) m = random(moves);
    else {
     moves = safecapturingmove();
     if (moves.size()) m = random(moves);
     else m = random(safemove());
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
      iter--;
    if (temp->at(iter)){
      while ( (temp->at(iter)->orig.row == -1 ) || ( temp->at(iter)->dest.row == -1)) {
        iter--;
          if (temp->at(iter)) m = *(temp->at(iter));
           }}
  }
  if (m.orig == Posn(-1,-1))  m = random();
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

vector<Move> Computer::safemove() {
 vector<Move> m;
 for (vector<Move>::iterator i = legalMoves.begin(); i != legalMoves.end(); i++) {
  board->move(i->orig, i->dest, false, true);
  bool exposed = false;
  for (int n = 0; n < 16; n++) {
   vector<Piece*> threats = own[n]->getThreats();
   if (threats.size() && own[n]->getCovers().size() == 0) {
    exposed = true;
    break;
   }
   if (threats.size() && min_piece(&threats) <= own[n]->val()) {
    exposed = true;
    break;
   }
   if (!exposed) m.push_back(*i);
  }
  board->undo(false);
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
  board->move(i->orig, i->dest, false, true);
  bool exposed = false;
  for (int n = 1; n < 16; n++) {
   vector<Piece*> threats = own[n]->getThreats();
   if (threats.size() && own[n]->getCovers().size() == 0) {
    exposed = true;
    break;
   }
   if (threats.size() && min_piece(&threats) <= own[n]->val()) {
    exposed = true;
    break;
   }
  }
  if (!exposed) move.push_back(*i);
  board->undo(false);
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
  for (vector<Move>::iterator i = m.begin(); i != m.end(); i++) {
   int res = board->move(i->orig, i->dest, false, true);
   if (res == 3) {
    board->undo(false);
    return m;
   }
   else {
   bool exposed = false;
   Piece* checking = 0;
   for (int n = 1; n < 16; n++) {
    if (own[n]->getPosn() == i->dest) checking = own[n];
    else continue;
   }
   if (checking) {
   vector<Piece*> threats = checking->getThreats();
   if (threats.size() && checking->getCovers().size() == 0)
     exposed = true;
   if (threats.size() && min_piece(&threats) < checking->val())
     exposed = true;
   if (!exposed) move.push_back(*i);
   }
   board->undo(false);
   }
  }
 return move;
}


vector<Move> Computer::capturingmove() {
  vector<Move> capturing;
  vector<Move> fork;
  for (vector<Move>::iterator i = legalMoves.begin(); i != legalMoves.end(); i++) {
  int state = threats(*board, !isWhite);
  board->move(i->orig, i->dest, false, true);
  int res = threats(*board, !isWhite);
  if (res - state >= 2) fork.push_back(*i);
  if (res - state == 1) capturing.push_back(*i);
  board->undo(false);
 }
 return fork.size() ? fork : capturing;
}

vector<Move> Computer::safecapturingmove() {
  vector<Move> m = capturingmove();
  vector<Move> move;
  for (vector<Move>::iterator i = m.begin(); i != m.end(); i++) {
   board->move(i->orig, i->dest, false, true);
   bool exposed = false;
   for (int n = 1; n < 16; n++) {
    vector<Piece*> threats = own[n]->getThreats();
    if (threats.size() && own[n]->getCovers().size() == 0) {
     exposed = true;
     break;
    }
    if (threats.size() && min_piece(&threats) <= own[n]->val()) {
     exposed = true;
     break;
    }
   }
   if (!exposed) move.push_back(*i);
   board->undo(false);
  }
 return move;
}


