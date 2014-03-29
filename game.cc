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
        int col = s[0] - 'a';
        int row = s[1] - '1';
        if ((col >= 0) && (col <= 7)) {
            if ((row >= 0) && (row <= 7)) {
                return Posn(row,col);
            }
        }
    }
    return NULL;
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
                    Posn pos1 = convertCoords(cmd2);
                    Posn pos2 = convertCoords(cmd3);
                    if ((pos1 != NULL) && (pos2 != NULL)) {
                        // other checking is done in ChessBoard (e.g. piece not empty, piece belongs to right guy, etc)
                        int result = board->move(pos1,pos2);
                        if (result == 0) {
                            cout << "Illegal Move" << endl;
                        } else if (result == 1) {
                            //legal move
                        } else if (result == 2) {
                            if (whiteTurn) {
                                cout << "White checks Black" << endl;
                            } else {
                                cout << "Black checks White" << endl;
                            }
                        } else if (result == 3) {
                            if (whiteTurn) {
                                endGame(1);
                            } else {
                                endGame(2);
                            }
                            return true;
                        } else if (result == 4) {
                            endGame(0);
                        }
                        return false;
                    }
                }
            }
        } else if (cmd == "resign") {
            if (whiteTurn) {
                endGame(2);
            } else {
                endGame(1);
            }
            return true;
        } else {
            cout << "Bad input on command" << endl;
            return false;
        }
    }
    cout << "Bad input on move" << endl;
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



