#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"
#include <vector>

struct Move;

class Computer: public Player {
 public:
  bool move();
  bool setAILevel(int); //this is needed because there are 4 levels of AI to choose from (Alternative: a Computer-specific constructor)
};

#endif
