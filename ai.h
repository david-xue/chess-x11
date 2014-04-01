#ifndef __AI_H__
#define __AI_H__
#include <vector>

struct Move;
class Posn;
class ChessBoard;
/*
Move bestMove(bool, const ChessBoard&);

int assess(bool, const ChessBoard&);
*/

std::vector<Posn> legalMove(ChessBoard&, const Posn);

int gain(ChessBoard&, bool);
//std::vector<Posn> howtocap(ChessBoard&, const Posn me, const Posn target);
#endif 
