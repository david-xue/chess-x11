#ifndef __POSN_H__
#define __POSN_H__

struct Posn {
 int row;
 int col;
 // I wanted this constructor so that I could initialize and pass Posns as parameters to functions (saving some code space)
 Posn(int row = 0, int col = 0) : row(row), col(col) {};
};

#endif
