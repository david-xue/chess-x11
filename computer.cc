#include "player.h"
#include "computer.h"
#include "chessboard.h"
#include "posn.h"

using namespace std;

//I am just writing some stub implementations to get the game working...
//

Computer::Computer (ChessBoard* b, bool isWhite, int lvl) : Player(b, isWhite), AILevel(lvl) {}

int Computer::move() {
    return 0;
}
