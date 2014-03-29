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
  Game();
  ~Game();
  void newgame(const bool, const bool); //bool is true is Human
  void setup();

}

#endif
