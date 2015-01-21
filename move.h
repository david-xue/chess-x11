#ifndef __MOVE_H__
#define __MOVE_H__
#include "posn.h"
class Piece;

struct Move {
 Piece* mover;
 Piece* captured;
 Posn orig;
 Posn dest;
 bool castling;
 bool promotion;
 Piece* enpassant;
 char name;
};

#endif
