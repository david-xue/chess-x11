#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"
#include <string>

// This class allows the Human Player to input moves
class Human: public Player {
    int readLine(std::string);
    public:
    Human(ChessBoard*, bool);
    int move();
};

#endif
