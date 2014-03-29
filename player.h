#ifndef __PLAYER_H__
#define __PLAYER_H__

class ChessBoard;

class Player {
  ChessBoard* board;
 public:
  Player(ChessBoard*);
  virtual int move() = 0;//return 0 if draw, 1 if non-game-ending move, 2 if resign, 3 if checkmate

};

#endif
