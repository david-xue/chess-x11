#include "chessboard.h"
#include "move.h"
#include "cell.h"
#include "aitree.h"
#include "piece.h"
#include <vector>
#include <cstdlib>

#define MAX_TREE_DEPTH 3
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
		val += evaluateMove(whiteTurn, owner);
	} else {
		m = NULL;
	}
	if (depth < MAX_TREE_DEPTH) {
		vector<Move>* moves = getLegalMoves(b,whiteTurn);
		int temp = moves->size();
		for (int i = 0; i < temp; ++i) {
			tree.push_back(new MoveTree(b, val, !whiteTurn, &(moves->at(i)), owner, depth+1));
		}
		delete moves;
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

int MoveTree::evaluateMove (bool whiteTurn, bool owner) {
	int res = 0;
	// check
	if (m->name == 'c') res += 4;
	if (m->name == 'C') return 100000;
	if (m->name == 'd') return 0;

	if (m->promotion) res += 9;
	if (m->captured) res += m->captured->val();
	if (m->enpassant) res += 2; //just for show off lol...
	if (m->castling) res += 1; //again, just for show off...
	// if this a white player evaluating a black move for instance
	if (!ownerTurn) res = res * -1;

	return res;
}

vector<Move>* MoveTree::getLegalMoves(ChessBoard* b, bool whiteTurn) {
	Piece ** array = NULL;
	if (whiteTurn) {
		array = b->black;
	} else {
		array = b->white;
	}
	Piece *p = 0;
	vector<Move> *moves = new vector<Move>;
	for (int i = 0; i < 16; ++i) {
		p = array[i];
		if (p != 0 && p->isOnBoard()) {
			Posn pos(0, 0);
			int res;
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
								m.enpassant =b->board[m.orig.row][m.dest.col]->getPiece();
							}
							m.name = ' ';
							moves->push_back(m);
						}
					//}
				}
			}
		}
	}
	//cout << "size " << moves.size() << endl;
	return moves;
}





