#ifndef __PIECE_H__
#define __PIECE_H__
#include "posn.h"

class ChessBoard;

class Piece {
  const char name;
  const bool owner;
  ChessBoard* const board;
  Posn pos;
  bool isThreatened;
  bool isCovered;
  
public:
  Piece(ChessBoard*, char, bool);
  virtual ~Piece();
  Piece(ChessBoard*);
  virtual int val() = 0;//return the standard relative value of piece
  virtual int move(const Posn) = 0;//return 0 if illegal; 1 if legal; 2 if castling; 3 if can be promoted; 4 if en passant
  virtual char getName();
  bool getOwner();
  Posn getPosn();
 //update the status; the second arg is the new threat status and the last is cover status
  void update(const Posn, bool, bool);

};

#endif
