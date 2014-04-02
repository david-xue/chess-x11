#include "chessboard.h"
#include "move.h"
#include "cell.h"
#include "aitree.h"
#include "piece.h"
#include <vector>
#include <list>
#include <cstdlib>

#define MAX_TREE_DEPTH 5
#define MAX_DEGREE 3
using namespace std;

// owner is true if white, root node must have !whiteTurn (ie if it's white computer, then whiteTurn for root is false)
MoveTree::MoveTree(ChessBoard* b, int upperval, bool whiteTurn, Move* mp, bool owner, int depth) : depth(depth) {
	tree = {};
	ownerTurn = (whiteTurn == owner);
	val = 0;
	int res = 1;

	if (mp) {
		Move *tempM = new Move;
		m = tempM;
		res = b->move(mp->orig, mp->dest, false, true);
		*m = *mp;
		if (res == 2) {
			m->name = 'c';
		} else if (res == 3) {
			m->name = 'C';
		} else if (res == 4) {
			m->name = 'd';
		}
		val += evaluateMove(ownerTurn, m);
	} else {
		m = NULL;
	}
	if (depth < MAX_TREE_DEPTH) {
		list<Move>* moves = getLegalMoves(b,whiteTurn);
		if (moves) {
			int temp = moves->size();
			for (list<Move>::iterator i = moves->begin(); i != moves->end(); ++i) {
				tree.push_back(new MoveTree(b, val, !whiteTurn, &(*i), owner, depth+1));
			}
			delete moves;
		}
	}
	if (mp) {
		b->undo(false);
	}
}

MoveTree::~MoveTree() {
	unsigned int temp = tree.size();
	//cout << "size of tree " << temp << endl;
	for (unsigned int i = 0; i < temp; ++i) {
		delete (tree[i]);
	}
	delete m;
}

Move* MoveTree::getMove() {
	return m;
}

int MoveTree::getVal() {
	return val;
}

/* This algorithm recursively takes the best move for the player.
 * The minimax structure of the tree allows for always max checking.
 */
pair <int, vector < Move* > > MoveTree::getBestMove() {

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
					}
				} else {
					//opposite case, if it's the opponents, then we want the worst case possible
					if (tempResult.first < maxmin) {
						maxmin = tempResult.first;
						result = tempResult;
					}
				}
			}
		}
		result.first += val;
		result.second.push_back(m);
		return result;
	}

}

int MoveTree::evaluateMove (bool ownerTurn1, Move *mp) {
	int res = 0;
	// check
	//if (mp->name == 'c') res += 4;
	if (mp->name == 'C') return 10000;
	//if (mp->name == 'd') return 0;

	if (mp->promotion) res += 9;
	if (mp->captured) res += mp->captured->val();
	if (mp->enpassant) res += 2; //just for show off lol...
	if (mp->castling) res += 1; //again, just for show off...
	// if this a white player evaluating a black move for instance
	if (!ownerTurn1) res = res * -1;

	return res;
}

list<Move>* MoveTree::getLegalMoves(ChessBoard* b, bool whiteTurn) {
	Piece ** array = NULL;
	if (whiteTurn) {
		array = b->black;
	} else {
		array = b->white;
	}
	Piece *p = 0;
	//cerr << "one" << endl;
	list<Move> *moves = new list<Move>;
	list<Move>::iterator minIter;
	int min = 0;
	for (int i = 0; i < 16; ++i) {
		p = array[i];
		if (p != 0 && p->isOnBoard()) {
			Posn pos(0, 0);
			int res, moveVal;
			for (int r = 0; r < 8; r++) {
				for (int c = 0; c < 8; c++) {
					pos.row = r;
					pos.col = c;
					//if (p->canReach(pos)) {

					res = p->move(pos);
					if (res >= 1) {
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
						//cerr << "two" << endl;
						if (moves->empty()) {
							//cerr <<"A" << endl;
							min = moveVal;
							moves->push_back(m);
							minIter = moves->begin();
						} else if (moves->size() <= MAX_DEGREE) {
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
						}  else if (moveVal > min) {
							//cerr << "B" << endl;
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
					//}
				}
			}
		}
	}
	//cerr << "three" << endl;
	//cout << "size " << moves.size() << endl;
	if (moves->size() == 0) return NULL;
	return moves;
}





