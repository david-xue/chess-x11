#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include <vector>

struct Move;

class Computer: public Player {
    int AILevel;
    public:
    Computer(ChessBoard*,bool, int);
    int move();
    //void setAILevel(int); //this is needed because there are 4 levels of AI to choose from (Alternative: a Computer-specific constructor)
};

#endif
