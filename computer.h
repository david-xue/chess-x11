#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"
#include <vector>

struct Move;

class Computer: public Player {
 public:
  bool move();
};

#endif
