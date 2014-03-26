#ifndef __GAME_H__
#define __GAME_H__
#include "chessboard.h"
#include "player.h"
#include "display.h"

class Game {
  ChessBoard* board;
  Player* white;
  Player* black;
  int whitescore;
  int blackscore;

  void displayScore();
  void saveRecord();
  void resign(bool);

 public:
  Game(bool, bool) //bool = true if player is human; false if computer
  ~Game();
  void newgame();
  void setup();

}

#endif
