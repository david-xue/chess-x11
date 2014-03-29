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
  void endGame(bool);

  void initializePlayer (Player* const, const int); 
  void readLine (const bool);
  Posn convertCoord (std::string); 
 public:
  Game();
  ~Game();
  void newgame(const int, const int); //0 if human, 1-4 indicate AI level
  void setup();

}

#endif
