#include "chessboard.h"
#include "move.h"
#include "cell.h"
#include "aitree.h"
#include "piece.h"
#include <vector>
#include <list>
#include <time.h>
#include <cstdlib>


using namespace std;

#define MAX_TREE_DEPTH 4 // depth of tree
unsigned int MAX_DEGREE = 1; //multiplier

// This recursive ctor will create a game tree of depth MAX_TREE_DEPTH
// mp is the current node's move (NULL for root)
// upperval is not and shouldn't be used
// owner is true if white, root node must have !whiteTurn (ie if it's white computer, then whiteTurn for root is false)
MoveTree::MoveTree(ChessBoard* b, int upperval, bool whiteTurn, Move* mp, bool owner, int depth) : depth(depth) {
	// set on degree of tree node multiplier based on how many pieces the AI has left
    if (depth == 0) {
	    int temp = 0;
		Piece ** array;
		if (!owner) {
			array = b->black;
		} else {
			array = b->white;
		}
		for (int i = 0; i < 16; i++) {
			if (array[i]->isOnBoard()) {
				temp++;
			}
		}
		if (temp < 7) {
			if (temp < 4) {
				MAX_DEGREE = 3;
			} else {
				MAX_DEGREE = 2;
			}
		}
	}
	
	tree.clear();
    // check if this is the owner's turn (for root node, this doesn't mean anything)
	ownerTurn = (whiteTurn == owner);
	val = 0;
	int res = 1;
    // First evaluate the current move and store it in node
	if (mp) {
		Move *tempM = new Move;
		m = tempM;
        // make the move on the board (change the current state of board and pass it to its children)
		res = b->move(mp->orig, mp->dest, false, true);
		*m = *mp;
		m->name = ' ';
		if (res == 2) {
			m->name = 'c';
		} else if (res == 3) {
            // stop searching if checkmate
			m->name = 'C';
			depth = MAX_TREE_DEPTH;
		} else if (res == 4) {
			m->name = 'd';
		}
		val += evaluateMove(ownerTurn, m);
	} else {
		m = NULL;
	}

    // recursively create children nodes based moves return in getLegalMoves
    // which will heuristically determine an incomplete list of moves that the current player could make 
	if (depth < MAX_TREE_DEPTH) {
		list<Move>* moves = getLegalMoves(b,whiteTurn);
		if (moves) {
			for (list<Move>::iterator i = moves->begin(); i != moves->end(); ++i) {
				if (m) {
					if (m->name == 'C') {
					break;
					}
				}
				tree.push_back(new MoveTree(b, val, !whiteTurn, &(*i), owner, depth+1));
			}
			delete moves;
		}
	}
	
    // undo the change when done
	if (mp) {
		b->undo(false);
	}
}

// dtor
MoveTree::~MoveTree() {
	unsigned int temp = tree.size();
	for (unsigned int i = 0; i < temp; ++i) {
		delete (tree[i]);
	}
	delete m;
}

// getters
Move* MoveTree::getMove() {
	return m;
}

int MoveTree::getVal() {
	return val;
}

/* This algorithm recursively takes the best move for the current node.
 * This is a minimax algorithm in that it takes the best move of owner and opponent each time
 */
// This returns a pair of int (representing the value of the move), and a vector of move (this vector should be size 1 or 2 at all times)
pair <int, vector < Move* > > MoveTree::getBestMove() {
	srand (time(NULL));
	bool unset = true;
	int maxmin = 0;
	pair <int, vector <Move*> > result, tempResult;
	int tempSize = tree.size();
	if (tempSize == 0) {
		vector<Move*> v;
		result.first = val;
		result.second = v;
		return result;
	} else {
        // search through its children for the move with the best net gain
		for (vector<MoveTree*>::iterator i = tree.begin(); i != tree.end(); ++i) {
			tempResult = (*i)->getBestMove();
			if (unset) {
				maxmin = tempResult.first;
				result = tempResult;
				unset = false;
			} else {
				// If the moves we're checking are of the owner (!ownerTurn because the current node is not owner
				// so the children must be of the owner), then we want the max move
				if ((!ownerTurn) || (depth == 0)) {
					if (tempResult.first > maxmin) {
						maxmin = tempResult.first;
						result = tempResult;
					} else if (tempResult.first == maxmin) {
						int random = rand() % 2;
						if (random == 0) {	
							maxmin = tempResult.first;
							result = tempResult;
						}
					}
				} else {
					//opposite case, if it's the opponents, then we want the worst case possible
					if (tempResult.first < maxmin) {
						maxmin = tempResult.first;
						result = tempResult;
					} else if (tempResult.first == maxmin) {
						int random = rand() % 2;
						if (random == 0) {	
							maxmin = tempResult.first;
							result = tempResult;
						}
					}
				}
			}
		}
		result.first += val;
		result.second.push_back(m);
		return result;
	}

}

//Evaluate the move based on what happened
int MoveTree::evaluateMove (bool ownerTurn1, Move *mp) {
	int res = 0;
	// check (no value given because it screws the AI's thinking e.g. sacrificing a pawn for a check
	//if (mp->name == 'c') res += 1;
    // Checkmate is crucial
	if (mp->name == 'C') return 1000;
	//if (mp->name == 'd') return 0;
	if (mp->promotion) {
		if (!ownerTurn1) res += 1;
	}
	if (mp->captured) res += mp->captured->val();
	if (mp->enpassant) res += 1; //just for show off
	if (mp->castling) res += 0;
	// if this a white player evaluating a black move for instance
	if (!ownerTurn1) res = res * -1;

	return res;
}

// Get a fix-sized list of moves (otherwise too high degree for node and too slow), which are at the current time, the best moves possible
// It basically checks every single move on the board and evaluate (note that there's always a legal move possible because checkmate hasn't happen)
list<Move>* MoveTree::getLegalMoves(ChessBoard* b, bool whiteTurn) {
	// fix the size of the list (12 * multiplier for first move (AI4), 12 for 1st opponent, then just the best 2 or 1 for deeper moves)
    int nodedeg;
	if (depth == 0) {
		nodedeg = 12 * MAX_DEGREE;
	} else if (depth == 1) {
		nodedeg = 12;
	} else if (depth == 2) {
		nodedeg = 2;
	} else {
		nodedeg = 1;
	}
    // get ptr to the pieces for the current player
	Piece ** array = NULL;
	if (whiteTurn) {
		array = b->black;
	} else {
		array = b->white;
	}
	Piece *p = 0;
	list<Move> *moves = new list<Move>;
	list<Move>::iterator minIter; //keeps track of the worst move in the list so we can replace if necessary
	int min = 0;
	for (int i = 0; i < 16; ++i) {
		p = array[i];
        // first check if the piece is valid (not captured or something)
		if (p != 0 && p->isOnBoard()) {
			Posn pos(0, 0);
			int res, moveVal;
			for (int r = 0; r < 8; r++) {
				for (int c = 0; c < 8; c++) {
					pos.row = r;
					pos.col = c;
					// check if the move is valid
					res = p->move(pos);
					if (res >= 1) {
                        // construct the move backward and evaluate
						Move m;
						m.mover = p;
						m.captured = b->board[r][c]->getPiece();
						m.orig = p->getPosn();
						m.dest = pos;
						m.castling = false;
						m.promotion = false;
						m.enpassant = NULL;
						if (res == 2) {
							m.castling = true;
						} else if (res == 3) {
							m.promotion = true;
						} else if (res == 4) {
							m.enpassant =
									b->board[m.orig.row][m.dest.col]->getPiece();
						}
						m.name = ' ';
						moveVal = evaluateMove(true,&m);
						// if list is empty, get something in there
						if (moves->empty()) {
							min = moveVal;
							moves->push_back(m);
							minIter = moves->begin();
						} else if (moves->size() <= nodedeg) {
                            // if list is not full, fill it
							moves->push_back(m);
							bool unset = true;
							min = 0;
							for (list<Move>::iterator listIter =
									moves->begin();
									listIter != moves->end(); ++listIter) {
								int temp = evaluateMove(true, &(*listIter));
								if ((temp < min) || unset) {
									min = temp;
									minIter = listIter;
									unset = false;
								}
							}
						}  else if (moveVal >= min) {
							// if list is full, then replace the worst move in it if this a better move
							moves->erase(minIter);
							bool unset = true;
							min = 0;
							for (list<Move>::iterator listIter = moves->begin(); listIter != moves->end(); ++listIter) {
								int temp = evaluateMove(true, &(*listIter));
								if ((temp < min) || unset) {
									min = temp;
									minIter = listIter;
									unset = false;
								}
							}
							moves->push_back(m);
						}
					}
				}
			}
		}
	}
	// this shouldn't happen (but it may)
	if (moves->size() == 0) return NULL;
	return moves;
}
