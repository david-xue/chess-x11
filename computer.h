#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include <vector>

struct Move;
class Piece;

class Computer: public Player {
    int AILevel;
    int random();
    Piece* own[16];
    Piece* opp[16];
    std::vector<Move>* alllegalMove();
    public:
    Computer(ChessBoard*,bool, int);
    void passPiece(Piece*[], Piece*[]);
    int move();
    void setAILevel(int); //this is needed because there are 4 levels of AI to choose from (Alternative: a Computer-specific constructor)
};

#endif
