#include "posn.h"
#include "king.h"
#include "piece.h"
#include "chessboard.h"
#include "move.h"
#include <vector>
#include <cstdlib>
using namespace std;

// Does King need its own constructor because of moved? (I think this depends on the compiler)
King::King(ChessBoard * board, char c, bool o) : Piece(board, c, o), moved(false) {}

int King::val() {
    // what is it? 4? or some huge value?
    return 10000;
}
 
int King::canReach(const Posn posn) {
    int rowDist = abs(posn.row - pos.row);
    int colDist = abs(posn.col - pos.col);
    if (((colDist == 1) || (colDist == 0)) && ((rowDist == 1) || (rowDist == 0)) && (!((rowDist == 0) && (colDist == 0)))) {
        return 1;
    } else {
        if (isCastling(posn)) {
            return 2;
        } else {
            return 0;
        }
    }
}

bool King::isCastling(const Posn posn) {
    if (posn.row != pos.row || abs(posn.col - pos.col) != 2) return false;
    if (posn.col > pos. col) {
     if (board->isAttacked(Posn(pos.row, 5), !owner)) return false;
     if (board->isOccupied(Posn(pos.row, 6), owner)) return false;
    } else {
     if (board->isAttacked(Posn(pos.row, 3), !owner)) return false;
     if (board->isOccupied(Posn(pos.row, 2), !owner)) return false;
    }
    if (!moved && !isThreatened ) {
           vector<Move>* record = board->getRecord();
            if (record->size() == 0) return true;
            else {
             bool res = true;
             if (posn.col > pos.col) {
              if (board->isOccupied(Posn(pos.row, pos.col + 1), owner)) return false;
              Posn p(pos.row, 7);
              for (vector<Move>::reverse_iterator i = record->rbegin(); i != record->rend(); i++) {
               if (i->orig == p || i->dest == p) res = false;
              }
              cout << res << endl; //What is this?
              return res;
             } else {
              if (board->isOccupied(Posn(pos.row, pos.col - 1), owner)) return false;
              if (board->isOccupied(Posn(pos.row, pos.col - 3), owner)) return false;
              Posn p(pos.row, 0);
              for (vector<Move>::reverse_iterator i = record->rbegin(); i != record->rend(); i++) {
               if (i->orig == p || i->dest == p) res = false;
              }
              return res;
             }
            }
    } else {
        return false;
    }
}
                    
void King::update(const Posn p, bool white, bool black) {
 vector<Move>* record = board->getRecord();
 bool res;
 if (record->size()) {
  for (vector<Move>::reverse_iterator i = record->rbegin(); i != record->rend(); i++) {
   if (i->mover == this) {
    res = true;
    break;
   }
  }
 }    
 moved = res;
 pos = p;
 isThreatened = owner ? black : white;                                                                                              
 isCovered = owner ? white : black;                                                                                                 
}
