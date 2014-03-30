#include "game.h"
#include "chessboard.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "posn.h"
//#include "display.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

Game::Game() : board(new ChessBoard()), white(NULL), black(NULL), whitescore(0), blackscore(0), selfSetup(false) {}

Game::~Game() {
    delete board;
    delete white;
    delete black;
}

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

void Game::newGame(const int whitePlayer, const int blackPlayer) {
    initializePlayer(true, whitePlayer);
    initializePlayer(false, blackPlayer);
    if (!selfSetup) {
        board->game();
    } else {
        cout << *board;
    }
    bool whiteTurn = board->isWhiteMove();
    Player* currentPlayer;
    while (true) {
        if (whiteTurn) {
            currentPlayer = white;
        } else {
            currentPlayer = black;
        }
        int result;
        try {
            if (currentPlayer == NULL) cout << "WTF" << endl;
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

void Game::setup() {
    board->setup();
    selfSetup = true;
}


void Game::displayScore() {
    cout << "White Score: " << whitescore << endl;
    cout << "Black Score: " << blackscore << endl;
}

/* what does this do again? */
void Game::saveRecord() {

}

//win is 1 if white wins, 2 if black wins, 0 if draw
void Game::endGame (int win) {
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
    // is this necessary (especially the deletion of players)?
    delete board;
    delete white;
    delete black;
    board = new ChessBoard();
    white = black = NULL;
    selfSetup = false;
}



