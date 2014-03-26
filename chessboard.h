#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <iostream>
#include <vector>

struct Posn;
struct Move;
class Piece;
class Cell;
class Display;

class ChessBoard {
  Cell* board[8][8];
  Piece* white[16];
  Piece* black[16];
  Display* tp; //texts display
  Display* gp; //graphics display
  vector<Move> record;//record of moves
  int turn;//number of turns
  bool alert;//alerting mode

  void update();//move calls this to update the cells
  bool check();//move will call this
  bool checkmate();//same as above
  bool stalemate();//same

 public:
  ChessBoard();
  ~ChessBoard();
 
 //basic methods: for boolean values, true = white and false = black 
 //init initialize the chessboard
  void init();
  void init(const char, const Posn);
 //move places the piece from one cell to another; updates the (threats) status of cells
 //     notifies display; add this move to the record of players; determine if there is a check/checkmate/stalemate
 //     returns 0 if illegal; 1 if legal; 2 if check; 3 if checkmate; 4 if stalemate
  int move(const Posn, const Posn);
 //isOccupied returns 0 if the cell is not occupied, 1 if occupied by your own piece, 2 if by opponent's
  int isOccupied(const Posn, bool);
  void undo();
  void setAlert(bool);//set alerting mode; can be set on only when human player vs computer
  vector<Move> getRecord();

 //methods for display and AI:
  friend std::ostream& operator<<(std::ostream&, ChessBoard&);
 //isThreatened returns true if the cell can be reached by opponent's pieces
  bool isThreatened(const Posn, bool);
 //showThreatened displays the threatened pieces
  void showThreatened(const Posn, bool);
 //legalMove returns all legal moves of a piece
  vector<Posn> legalMove(const Posn);
 //showlegalMove displays all legal moves of a piece
  void showlegalMove(const Posn);
 //safeMove returns all legal moves to cells that is not threatened
  vector<Posn> safeMove(const Posn);
 //howtocap returns the next move needed to capture the piece
  vector<Posn> howtocap(const Posn me, const Posn target);

};

#endif
