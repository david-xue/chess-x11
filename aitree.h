#ifndef __AI_TREE_H__
#define __AI_TREE_H__

#include <map>
#include <string>
#include <vector>

class Move;
class ChessBoard;

class MoveTree {

    Move* m;
    int val;
    bool ownerTurn;
    int evaluateMove(bool, bool);
    public:
    std::vector<MoveTree*> tree;
    MoveTree(ChessBoard*, int, bool, Move*, bool, int);
    ~MoveTree();
    Move* getMove();
    int getVal();
    std::pair <int, std::vector <Move*> > getBestMove();
    std::vector<Move>* getLegalMoves(ChessBoard* , bool);
};

#endif
