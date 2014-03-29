#include "posn.h"
#include <string>
using namespace std;

Posn::Posn(int row, int col) : row(row), col(col) {};

Posn convertCoords(string s) {
    if (s.length() == 2) {
        int col = s[0] - 'a';
        int row = s[1] - '1';
        if ((col >= 0) && (col <= 7)) {
            if ((row >= 0) && (row <= 7)) {
                return Posn(row,col);
            }
        }
    }
    return Posn(-1,-1);
}

