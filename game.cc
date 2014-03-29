#include "game.h"
#include "chessboard.h"
#include "player.h"
//#include "display.h"
#include <sstream>
#include <string>

/*
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
*/

using namespace std;

Game::Game() : board(new ChessBoard()), white(NULL), black(NULL), whitescore(0), blackscore(0) {}

Game::~Game() {
    delete board;
    delete white;
    delete black;
}

void Game::newGame(const bool whitePlayer, const bool blackPlayer) {
}

void Game::setup() {
}

void Game::displayScore() {
    cout << "White Score: " << whitescore << endl;
    cout << "Black Score: " << blackscore << endl;
}

/* what does this do again? */
void Game::saveRecord() {

}

//owner is true if white
void Game::resign (bool owner) {
    if (owner) {
        ++whitescore;
    } else {
        ++blackscore;
    }
    displayScore();
    saveRecord();
    // is this necessary (especially the deletion of players)?
    delete board;
    delete white;
    delete black;
    board = new ChessBoard();
    white = black = NULL;
}



