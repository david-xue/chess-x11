#include "game.h"
#include "chessboard.h"
#include "player.h"
#include "human.h"
#include "computer.h"
//#include "display.h"
#include <sstream>
#include <string>

using namespace std;

Game::Game() : board(new ChessBoard()), white(NULL), black(NULL), whitescore(0), blackscore(0), selfSetup(false) {}

Game::~Game() {
    delete board;
    delete white;
    delete black;
}

void initializePlayer (Player * const player. const int humanAI) {
    if (player != NULL) delete player;
    if (humanAI == 0) {
        player = new Human();
    } else {
        player = new Computer();
        player->setAILevel(humanAI);
    }
}

void Game::newGame(const int whitePlayer, const int blackPlayer) {
    initializePlayer(white, whitePlayer);
    initializePlayer(black, blackPlayer);
    if (!selfSetup) board->init();
    while ( 
}

void Game::setup() {

    selfSetup = true;
}


void Game::displayScore() {
    cout << "White Score: " << whitescore << endl;
    cout << "Black Score: " << blackscore << endl;
}

/* what does this do again? */
void Game::saveRecord() {

}

//owner is true if white
void Game::endGame (bool owner) {
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
    selfSetup = false;
}



