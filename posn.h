#ifndef __POSN_H__
#define __POSN_H__

struct Posn {
 int row;
 int col;
 Posn(int row = 0, int col = 0) : row(row), col(col) {};
};

#endif
