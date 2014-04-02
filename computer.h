#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include <vector>

struct Move;
class Piece;
class Cell;
class Computer: public Player {
    int AILevel;
    Piece* own[16];
    Piece* opp[16];
    std::vector<Move>* legalMoves;

    Move random();
    Move random(std::vector<Move>);
    std::vector<Move>* alllegalMove();
    std::vector<Move> captures();
    std::vector<Move> checkingmove();
    std::vector<Move> capturingmove();
    public:
    Computer(ChessBoard*,bool, int);
    ~Computer();
    void receive(Piece*[], Piece*[]);
    int move();
    void setAILevel(int); //this is needed because there are 4 levels of AI to choose from (Alternative: a Computer-specific constructor)
};

#endif
