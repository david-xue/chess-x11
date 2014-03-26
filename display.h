#ifndef __DISPLAY_H__
#define __DISPLAY_H__

struct Posn;
struct Move;

class Display {
  char board[8][8];
  
 public:
  void init();
  void init(const char, const Posn);
  void notify(const Move, bool undo = false);

};

#endif
