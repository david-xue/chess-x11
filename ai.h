#ifndef __AI_H__
#define __AI_H__

struct Move;
class ChessBoard;

Move bestMove(bool, const ChessBoard&);

int assess(bool, const ChessBoard&);

#endif 
