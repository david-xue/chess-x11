#ifndef __PIECE_H__
#define __PIECE_H__

struct Posn;
class ChessBoard;

class Piece {
  const char name;
  const bool owner;
  ChessBoard* board;
  Posn pos;
  bool isThreatened;
  bool isCovered;
  
public:
  Piece(ChessBoard*);
  virtual int val() = 0;//return the standard relative value of piece
  virtual bool canReach(const Posn) = 0;
  virtual bool move(const Posn) = 0;
  virtual char getName();
  bool getowner();
  Posn getPosn();
  void update(const Posn, bool, bool);//update the status

};

#endif
