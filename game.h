#ifndef __GAME_H__
#define __GAME_H__
#include <string>
#include "chessboard.h"
#include "player.h"
#include "posn.h"

// This class handles players and their moves and keep track of score and other statistics for the program.
// See game.cc for comments on each method

class Game {
  ChessBoard* board;
  Player* white;
  Player* black;
  int whitescore;
  int blackscore;
  bool selfSetup;
  void displayScore();
  void saveRecord();
  void endGame(int);

  void initializePlayer (bool, const int); 
 
 public:
  Game();
  ~Game();
  void newGame(const int, const int); //0 if human, 1-4 indicate AI level
  void setup();

};

#endif
