#ifndef __DISPLAY_H__
#define __DISPLAY_H__

struct Posn;
struct Move;

class Display {
  
 public:
  void init() = 0;
  void init(const char, const Posn) = 0;
  void notify(const Move, bool undo = false) = 0;

};

#endif
