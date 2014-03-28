#include "textdisplay.h"
#include "posn.h"
#include "move.h"
using namespace std;

void TextDisplay::init() {
 board[0][0] = board[0][7] = 'r';
 board[0][1] = board[0][6] = 'n';
 board[0][2] = board[0][5] = 'b';
 board[0][3] = 'q';
 board[0][4] = 'k';
 board[0][0] = board[0][7] = 'R';
 board[0][1] = board[0][6] = 'N';
 board[0][2] = board[0][5] = 'B';
 board[0][3] = 'Q';
 board[0][4] = 'K';
 for (int n = 0; n < 8; n++) {
  board[1][n] = 'p';
  board[6][n] = 'P';
 }
 for (int n = 2; n < 6; n++) 
  for (int m = 0; m < 8; m++) {
   board[n][m] = (n + m) % 2 ? ' ' : '_';
  }
}

void TextDisplay::init(const char c, const Posn p) {
 board[p.row][p.col] = c;
}

void TextDisplay::notify(const Move m, bool undo) {
 if (!undo) {
  int x = m.orig.row;
  int y = m.orig.col;
  board[x][y] = (x + y) % 2 ? ' ' : '_';
  board[m.dest.row][m.dest.col] = m.name;
 }
 else {
  int x = m.dest.row;
  int y = m.dest.col;
  if (m.promotion) board[x][y] = m.name;
  else {
   board[m.orig.row][m.orig.col] = m.name;
   if (m.captured) board[x][y] = m.captured;
   else board[x][y] = (x + y) % 2 ? ' ' : '_';
   if (m.enpassant) board[m.orig.row][m.dest.col] = m.name == 'p' ? 'P' : 'p';
  }
 }
}

ostream& operator<<(ostream& out, TextDisplay& tp) {
 for (int n = 0; n < 8; n++) {
  out << 8 - n << " " << tp.board[n] << endl;
 }
 out << "  abcdefgh" << endl;
 return out;
}

   
