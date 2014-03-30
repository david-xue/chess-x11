#ifndef __PIECE_H__
#define __PIECE_H__
#include "posn.h"
#include "chessboard.h"

class Piece {
 protected:
  const char name;
  const bool owner;
  ChessBoard* const board;
  Posn pos;
  bool isThreatened;
  bool isCovered;

 public:
  Piece(ChessBoard*, char, bool);
  virtual ~Piece();
  virtual int val() = 0;//return the standard relative value of piece
  virtual int canReach(const Posn) = 0;
  int move(const Posn);//return 0 if illegal; 1 if legal; 2 if castling; 3 if can be promoted; 4 if en passant
  virtual char getName();
  bool getOwner();
  Posn getPosn();
 //update the status; the second arg is the new threat status and the last is cover status
  virtual void update(const Posn, bool, bool);
};

#endif
