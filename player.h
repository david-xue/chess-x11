#ifndef __PLAYER_H__
#define __PLAYER_H__

class ChessBoard;

class Player {
  ChessBoard* board;

 public:
  Player(ChessBoard*);
  virtual bool move() = 0;//return false if the end of game has been reached

};

#endif
