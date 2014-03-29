#include "knight.h"
#include "posn.h"
#include <cstdlib>

int Knight::val() {return 3;}

int Knight::canReach(const Posn posn) {
 int x = abs(pos.col - posn.col);
 int y = abs(pos.row - posn.row);
 if ((x == 1 && y == 2) || (x == 2 && y == 1)) {
  return 1;
 }
 else return 0;
}

