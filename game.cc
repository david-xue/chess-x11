#include "game.h"
#include "chessboard.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "posn.h"
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

Posn Game::convertCoords(string s) {
    if (s.length() == 2) {
        int col;
    } else {
        return NULL;
    }
}

// true if the game ends (resign or win or draw)
bool Game::readLine(const bool whiteTurn) {
    string s;
    getline(cin,s);
    istringstream ss(s);
    string cmd1, cmd2, cmd3;
    if (ss >> cmd) {
        if (cmd == "move") {
            if (ss >> cmd2) {
                if (ss >> cmd3) {
                    Posn pos1 = 
        } else if (cmd == "resign") {
            endGame(whiteTurn);
            return true;
        } else {
            cout << "Bad input" << endl;
        }
    }
    return false;
}

void Game::newGame(const int whitePlayer, const int blackPlayer) {
    initializePlayer(white, whitePlayer);
    initializePlayer(black, blackPlayer);
    if (!selfSetup) board->init();
    bool whiteTurn = board->isWhiteMove();
    while (true) {
        if (readLine(whiteTurn)) break;
        whiteTurn = !whiteTurn;
    }
            
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



