#ifndef __MOVE_H__
#define __MOVE_H__

class Piece;

struct Move {
 Piece* mover;
 Piece* captured;
 Posn orig;
 Posn dest;
 bool castling;
 bool promotion;
 bool enpassant;
};

#endif
