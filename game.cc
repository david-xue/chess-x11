// See game.h for class declaration
#include "game.h"
#include "chessboard.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "posn.h"

#include <sstream>
#include <string>
#include <iostream>

using namespace std;
//ctor for game, this will initialize a new chess board
//This game object will remain for the rest of the program
Game::Game() : board(new ChessBoard()), white(NULL), black(NULL), whitescore(0), blackscore(0), selfSetup(false) {}

//dtor
Game::~Game() {
    delete board;
    delete white;
    delete black;
}

//initialize the appropriate players (polymorphic pointers)
void Game::initializePlayer (bool isWhite, const int humanAI) {
    if (humanAI == 0) {
        if (isWhite) {
            white = new Human(board, isWhite);
        } else {
            black = new Human(board, isWhite);
        }
    } else {
        if (isWhite) {
            white = new Computer(board, isWhite, humanAI);
        } else {
            black = new Computer(board, isWhite, humanAI);
        }
    }
}

//Start a new game and handle the alternating moves
void Game::newGame(const int whitePlayer, const int blackPlayer) {
    initializePlayer(true, whitePlayer);
    initializePlayer(false, blackPlayer);
    // output the board after setup mode (necessary for text, not for graphic)
    if (!selfSetup) {
        board->game();
    } else {
        cout << *board;
    }
    // check for if it's white move
    bool whiteTurn = board->isWhiteMove();
    Player* currentPlayer;
    while (true) {
        // switch turns
        if (whiteTurn) {
            currentPlayer = white;
        } else {
            currentPlayer = black;
        }
        int result;
        // the human player will throw an exception if there's no more moves in stdin
        // this allows the scoreboard to displayed in endGame() regardless of exit (normal or Ctrl-D)
        try {
            result = currentPlayer->move();
        } catch (string &s) {
            // out of moves
            cerr << s << endl;
            endGame(0);
            break;
        }
        if (result == 0) {
            //draw
            endGame(0);
            break;
        } else if (result == 1) {
            //legal, non-game-ending move
            whiteTurn = !whiteTurn;
        } else if (result == 2) {
            //resign
            if (whiteTurn) {
                endGame(2);
            } else{
                endGame(1);
            }
            break;
        } else if (result == 3) {
            // win by checkmate
            if (whiteTurn) {
                endGame(1);
            } else {
                endGame(2);
            }
            break;
        }
    }    
}

// setup mode
void Game::setup() {
    board->setup();
    selfSetup = true;
}

// display score
void Game::displayScore() {
    cout << "White Score: " << whitescore << endl;
    cout << "Black Score: " << blackscore << endl;
}

/* Save feature not implemented, could add this */
void Game::saveRecord() {
}

//win is 1 if white wins, 2 if black wins, 0 if draw
void Game::endGame (int win) {
    // this is what happens when the game end
    if (win == 1) {
        cout << "White wins" << endl;
        ++whitescore;
    } else if (win == 2) {
        cout << "Black wins" << endl;
        ++blackscore;
    } else {
        cout << "Draw" << endl;
    }
    displayScore();
    saveRecord();
    delete board;
    delete white;
    delete black;
    board = new ChessBoard();
    white = black = NULL;
    selfSetup = false;
}

