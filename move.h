#ifndef __MOVE_H__
#define __MOVE_H__

struct Move {
 const char name;
 const char captured;
 const Posn orig;
 const Posn dest;
 const bool castling;
 const char promotion;
 const bool enpassant;
};

#endif
