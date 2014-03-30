#ifndef __POSN_H__
#define __POSN_H__
#include <string>

struct Posn {
 int row;
 int col;
 // I wanted this constructor so that I could initialize and pass Posns as parameters to functions (saving some code space)
 Posn(int, int);
 bool operator==(Posn);
};

Posn convertCoords (std::string);
#endif
