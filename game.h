#ifndef __GAME_H__
#define __GAME_H__
#include <string>
#include "chessboard.h"
#include "player.h"
#include "posn.h"
//#include "display.h"

class Game {
  ChessBoard* board;
  Player* white;
  Player* black;
  int whitescore;
  int blackscore;
  bool selfSetup;
  void displayScore();
  void saveRecord();
  void endGame(int, bool checkmate = false);

  void initializePlayer (bool, const int); 
 
 public:
  Game();
  ~Game();
  void newGame(const int, const int); //0 if human, 1-4 indicate AI level
  void setup();

};

#endif
