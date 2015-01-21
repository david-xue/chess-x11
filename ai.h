#ifndef __AI_H__
#define __AI_H__
#include <vector>

struct Move;
class Posn;
class Piece;
class ChessBoard;
/*
Move bestMove(bool, const ChessBoard&);

int assess(bool, const ChessBoard&);
*/

std::vector<Move> legalMove(ChessBoard&, Piece*);

int gain(ChessBoard&, bool);
int threats(ChessBoard&, bool);
//std::vector<Posn> howtocap(ChessBoard&, const Posn me, const Posn target);
#endif 
