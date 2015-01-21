#include "opening.h"
#include <cstdlib>
#include <iostream>
#include "posn.h"
using namespace std;

void MoveNode::init() {
  Move m1 = {0, 0, Posn(6, 4), Posn(4, 4), false, false, 0, 'P'};//e2 e4
  Move m2 = {0, 0, Posn(1, 4), Posn(3, 4), false, false, 0, 'p'};//e6 e5
  Move m3 = {0, 0, Posn(7, 6), Posn(5, 5), false, false, 0, 'N'};//g1 f3
  Move m4 = {0, 0, Posn(0, 1), Posn(2, 2), false, false, 0, 'n'};//b8 c6
  Move m5 = {0, 0, Posn(7, 5), Posn(3, 1), false, false, 0, 'B'};//f1 b5
  Move m6 = {0, 0, Posn(7, 5), Posn(4, 2), false, false, 0, 'B'};//f1 c4
  Move m7 = {0, 0, Posn(0, 5), Posn(3, 2), false, false, 0, 'b'};//f8 c5
  Move m8 = {0, 0, Posn(1, 2), Posn(3, 2), false, false, 0, 'p'};//c7 c5
  Move m9 = {0, 0, Posn(1, 3), Posn(2, 3), false, false, 0, 'p'};//d7 d6
  Move m10 = {0, 0, Posn(6, 3), Posn(4, 3), false, false, 0, 'P'};//d2 d4
  Move m11 = {0, 0, Posn(3, 2), Posn(4, 3), false, false, 0, 'p'};//c5 d4
  Move m12 = {0, 0, Posn(5, 5), Posn(4, 3), false, false, 0, 'N'};//f3 d4
  Move m13 = {0, 0, Posn(0, 6), Posn(2, 5), false, false, 0, 'n'};//g8 f6
  Move m14 = {0, 0, Posn(7, 1), Posn(5, 2), false, false, 0, 'N'};//b1 c3
  vector<Move> RuyLopez;
  RuyLopez.push_back(m1);
  RuyLopez.push_back(m2); 
  RuyLopez.push_back(m3);
  RuyLopez.push_back(m4);
  RuyLopez.push_back(m5);
  vector<Move> GiuocoPiano;
  GiuocoPiano.push_back(m1);
  GiuocoPiano.push_back(m2);
  GiuocoPiano.push_back(m3);
  GiuocoPiano.push_back(m4);
  GiuocoPiano.push_back(m6);
  GiuocoPiano.push_back(m7);
  vector<Move> SicilianDefense;
  SicilianDefense.push_back(m1);
  SicilianDefense.push_back(m8);
  SicilianDefense.push_back(m3);
  SicilianDefense.push_back(m9);
  SicilianDefense.push_back(m10);
  SicilianDefense.push_back(m11);
  SicilianDefense.push_back(m12);
  SicilianDefense.push_back(m13);
  SicilianDefense.push_back(m14);
  addSeq(RuyLopez, true);
  addSeq(GiuocoPiano, true);
  addSeq(SicilianDefense, true);
  srand(time(NULL));
}

MoveNode::~MoveNode() {
 for (vector<MoveNode*>::iterator i = nextMove.begin(); i != nextMove.end(); i++) {
  delete *i;
 }
}

Move MoveNode::getMove() {
 return move;
}

void MoveNode::addSeq(vector<Move> seq, bool root) {
 if (!root) {
  move = seq.at(0);
  seq.erase(seq.begin());
  if (!seq.empty()) {
   Move nm = seq.at(0);
   for (vector<MoveNode*>::iterator i = nextMove.begin(); i != nextMove.end(); i++) {
    Move m = (*i)->getMove();
    if (nm.orig == m.orig && nm.dest == m.dest) {
     (*i)->addSeq(seq);
     return;
    }
   }
   MoveNode* node = new MoveNode;
   node->addSeq(seq);
   nextMove.push_back(node);
  }
 } else {
   Move nm = seq.at(0);
   for (vector<MoveNode*>::iterator i = nextMove.begin(); i != nextMove.end(); i++) {
    Move m = (*i)->getMove();
    if (nm.orig == m.orig && nm.dest == m.dest) (*i)->addSeq(seq);
    return;
   }
   MoveNode* node = new MoveNode;
   node->addSeq(seq);
   nextMove.push_back(node);
 }
}

Move MoveNode::getnextMove(vector<Move> record) {
 if (record.empty()) {
  if (nextMove.empty()) {
   Move null;
   null.orig = Posn(-1, -1);
   return null;
  } else {
   int n = rand() % nextMove.size();
   return nextMove.at(n)->getMove();
  }
 } else {
  Move r = record.at(0);
  vector<MoveNode*> pm;
  for (vector<MoveNode*>::iterator i = nextMove.begin(); i != nextMove.end() && !nextMove.empty(); i++) {
   Move m = (*i)->getMove();
   if (r.orig == m.orig && r.dest == m.dest) pm.push_back(*i);
  }
  if (pm.empty()) {
   Move null;
   null.orig = Posn(-1, -1);
   return null;
  } else {
   int n = rand() % pm.size();
   record.erase(record.begin());
   return pm.at(n)->getnextMove(record);
  }
 }
}
