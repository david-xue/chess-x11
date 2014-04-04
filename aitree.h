#ifndef __AI_TREE_H__
#define __AI_TREE_H__

#include <map>
#include <string>
#include <vector>
#include <list>
class Move;
class ChessBoard;
/* This class is used for AI level 4. It is representative of a 
 * game tree and uses a minimax algorithm to determine the best move to make.
 * It searches 4 plies deep, but only for a select number of best moves for 
 * optimization reasons. */
class MoveTree {
	unsigned int depth;
    Move* m;
    int val;
    bool ownerTurn;
    int evaluateMove(bool, Move*);
    std::vector<MoveTree*> tree;
    public:
    MoveTree(ChessBoard*, int, bool, Move*, bool, int);
    ~MoveTree();
    Move* getMove();
    int getVal();
    std::pair <int, std::vector <Move*> > getBestMove();
    std::list<Move>* getLegalMoves(ChessBoard* , bool);
};

#endif
