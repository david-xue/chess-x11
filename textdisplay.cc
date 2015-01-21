#include "textdisplay.h"
#include "posn.h"
#include "move.h"
#include "piece.h"
using namespace std;

TextDisplay::TextDisplay() {
 for (int n = 0; n < 8; n++)
  for (int m = 0; m < 8; m++) {
   board[n][m] = (n + m) % 2 ? ' ' : '_';
  }
}

void TextDisplay::init() {
 board[0][0] = board[0][7] = 'r';
 board[0][1] = board[0][6] = 'n';
 board[0][2] = board[0][5] = 'b';
 board[0][3] = 'q';
 board[0][4] = 'k';
 board[7][0] = board[7][7] = 'R';
 board[7][1] = board[7][6] = 'N';
 board[7][2] = board[7][5] = 'B';
 board[7][3] = 'Q';
 board[7][4] = 'K';
 for (int n = 0; n < 8; n++) {
  board[1][n] = 'p';
  board[6][n] = 'P';
 }
}

void TextDisplay::init(const char c, const Posn p) {
 board[p.row][p.col] = c;
}

void TextDisplay::init(const Posn p) {
 int n = p.row;
 int m = p.col;
 board[n][m] = (n + m) % 2 ? ' ' : '_';
}

void TextDisplay::notify(const Move m, bool undo) {
 if (!undo) {
  int x = m.orig.row;
  int y = m.orig.col;
  board[x][y] = (x + y) % 2 ? ' ' : '_';
  board[m.dest.row][m.dest.col] = m.mover->getName();
  if (m.castling) {
   if (m.orig.col < m.dest.col) {                                                                                                                              
    board[m.orig.row][5] = m.mover->getOwner() ? 'R' : 'r';
    board[m.orig.row][7] = m.orig.row == 0 ? '_' : ' ';
   }                                                                                                                                                       
   else {
    board[m.orig.row][3] = m.mover->getOwner() ? 'R' : 'r';
    board[m.orig.row][0] = m.orig.row == 0 ? ' ' : '_';
   }   
  }
  if (m.enpassant) {
   int x = m.orig.row;                                                                                                                                    
   int y = m.dest.col;                                                                                                                                    
   board[x][y] = (x + y) % 2 ? ' ' : '_'; 
  } 
 }
 else {
  int x = m.dest.row;
  int y = m.dest.col;
  board[m.orig.row][m.orig.col] = m.mover->getName();
  if (m.captured) board[x][y] = m.captured->getName();
  else board[x][y] = (x + y) % 2 ? ' ' : '_';
  if (m.enpassant) board[m.orig.row][m.dest.col] = m.enpassant->getName();
  if (m.castling) {
   if (m.orig.col < m.dest.col) {
    board[m.orig.row][7] = m.mover->getOwner() ? 'R' : 'r';
    board[m.orig.row][5] = m.orig.row == 0 ? '_' : ' ';
   }                                                                                                                                                     
   else {                                                                                                                                                
    board[m.orig.row][0] = m.mover->getOwner() ? 'R' : 'r';
    board[m.orig.row][3] = m.orig.row == 0 ? '_' : ' ';
   }
  } 
 }
}

ostream& operator<<(ostream& out, TextDisplay& tp) {
 for (int n = 0; n < 8; n++) {
  out << 8 - n << " ";
  for (int m = 0; m < 8; m++) {
   out << tp.board[n][m];
  }
  out << endl;
 }
 out << "  abcdefgh" << endl;
 return out;
}

   
