#ifndef __OPENING_H__
#define __OPENING_H__
#include <vector>
#include "move.h"

class MoveNode {
 Move move;
 std::vector<MoveNode*> nextMove;
 void addSeq(std::vector<Move>, bool root = false); 

 public:
 Move getMove();
 void init();
 ~MoveNode();
 Move getnextMove(std::vector<Move>);

};

#endif
