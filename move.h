#ifndef __MOVE_H__
#define __MOVE_H__

struct Move {
 const Posn orig;
 const Posn dest;
 Piece* const Captured;
};

#endif
