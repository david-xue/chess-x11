#ifndef __PLAYER_H__
#define __PLAYER_H__

class ChessBoard;

class Player {
protected:
  ChessBoard* board;
  bool isWhite;
 public:
  Player(ChessBoard*, bool);
  virtual int move() = 0;//return 0 if draw, 1 if non-game-ending move, 2 if resign, 3 if checkmate
  virtual ~Player();
};

#endif
