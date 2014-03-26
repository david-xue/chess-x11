#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "display.h"
#include <iostream>
#include <vector>

struct Posn;
struct Move;

class TextDisplay: public Display {
  friend std::ostream& operator<<(std::ostream&, TextDisplay&);
};

#endif
