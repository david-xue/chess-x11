#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <iostream>
#include <vector>

struct Posn;
struct Move;
class Piece;
class Cell;
class TextDisplay;
class GraphDisplay;

class ChessBoard {
  Cell* board[8][8];
  Piece* white[16];
  Piece* black[16];
  TextDisplay* tp;
  GraphDisplay* gp;
  std::vector<Move>* record;//record of moves
  int turn;//number of turns
  bool blackmove;
  bool alert;//alerting mode

  void update();//move calls this to update all cells' status
  bool check(bool);//move will call this to determine if the player is being checked
  bool checkmate(bool);//same as above
  bool stalemate(bool);//same

 public:
  ChessBoard();
  ~ChessBoard();
 
 //basic methods: for boolean values, true = white and false = black 
 //init initialize the chessboard
  void init();
  void init(const char, const Posn);
 //move places the piece from one cell to another(also place the rook to right cell when castling; check for en passant) 
 //     updates the status of cells
 //     notifies display; add this move to the record; determine if there is a check/checkmate/stalemate
 //     returns 0 if illegal; 1 if legal; 2 if check; 3 if checkmate; 4 if stalemate
  int move(const Posn, const Posn);
 //isOccupied returns 0 if not occupied, 1 if occupied by your own piece, 2 if by opponent's
  int isOccupied(const Posn, bool);
  void undo();
  void setAlert(bool);//set alerting mode; can be set on only when human player vs computer
  std::vector<Move>* getRecord();
  bool isExposed(const Posn, const Posn, bool); //pieces will call this to determine if their moves get their king exposed

 //friend functions for display and AI:
  friend std::ostream& operator<<(std::ostream&, ChessBoard&);
 //isThreatened returns true if the cell can be reached by opponent's pieces
  friend bool isThreatened(const Posn, bool);
 //showThreatened displays the threatened pieces
  friend void showThreatened(const Posn, bool);
 //legalMove returns all legal moves of a piece
  friend std::vector<Posn> legalMove(const Posn);
 //showlegalMove displays all legal moves of a piece
  friend void showlegalMove(const Posn);
 //safeMove returns all legal moves to cells that is not threatened
  friend std::vector<Posn> safeMove(const Posn);
 //howtocap returns the next move needed to capture the piece
  friend std::vector<Posn> howtocap(const Posn me, const Posn target);

};

#endif
