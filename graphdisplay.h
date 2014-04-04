#ifndef __GRAPHDISPLAY_H__
#define __GRAPHDISPLAY_H__
#include <X11/Xlib.h>
#include <map>

/* This class is a new version of the Xwindow class with support for loaded images.
 * The original window.cc does not appear to work when I added image loading mechanisms,
 * so I rewrote it. */

// See graphdisplay.cc for implementation

class Posn;

class GraphDisplay {

	Display *display;
	Window win;

	GC gc; /* GC (graphics context) used for drawing    */

	unsigned int width, height; /* height and width for the new window.      */
	/* these variables will contain the dimensions of the loaded bitmap. */

	unsigned int bitmap_width, bitmap_height;
    
	std::map<char, Pixmap*> imageMap; //pointers to loaded images (mapped by char, eg K,k,Q)
    Pixmap* xaxis;
    Pixmap* yaxis;
    Pixmap* bg;
    unsigned int axis_width, axis_height;
public:

	GraphDisplay();
	~GraphDisplay();

	void draw(char, Posn);
	void undraw(Posn);

};

Window create_simple_window(Display*, int, int, int, int);
GC create_gc(Display*, Window, int);

#endif
