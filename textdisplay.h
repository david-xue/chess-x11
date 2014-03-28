#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>

struct Posn;
struct Move;

class TextDisplay {
  char board[8][8];

 public:
  void init();
  void init (const char, const Posn);
  void notify(const Move, bool undo = false);
  friend std::ostream& operator<<(std::ostream&, TextDisplay&);
};

#endif
