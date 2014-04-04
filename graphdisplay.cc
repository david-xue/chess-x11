#include "graphdisplay.h"
#include "posn.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <map>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

/* This class is a re-implementation of the Xwindow class.
 * Xwindow did not support image loading and when I tried to add additional
 * methods, the Pixmap couldn't load properly.
 * 
 * So, after reading a manual online about loading images in X11, I wrote
 * this class for image loading (the helpers are taking from web)
 *
 * Kudos to : http://neuron-ai.tuke.sk/hudecm/Tutorials/C/special/xlib-programming/xlib-programming-2.html
 */

// helper for creating a simple window
Window create_simple_window(Display* display, int width, int height, int x,
		int y) {
	int screen_num = DefaultScreen(display);
	int win_border_width = 2;
	Window win;

	/* create a simple window, as a direct child of the screen's */
	/* root window. Use the screen's black and white colors as   */
	/* the foreground and background colors of the window,       */
	/* respectively. Place the new window's top-left corner at   */
	/* the given 'x,y' coordinates.                              */
	win = XCreateSimpleWindow(display, RootWindow(display, screen_num), x, y,
			width, height, win_border_width, BlackPixel(display, screen_num),
			WhitePixel(display, screen_num));

	/* make the window actually appear on the screen. */
	XMapWindow(display, win);

	/* flush all pending requests to the X server. */
	XFlush(display);

	return win;
}

// helper for creating GC
GC create_gc(Display* display, Window win, int reverse_video) {
	GC gc; /* handle of newly created GC.  */
	unsigned long valuemask = 0; /* which values in 'values' to  */
	/* check when creating the GC.  */
	XGCValues values; /* initial values for the GC.   */
	unsigned int line_width = 2; /* line width for the GC.       */
	int line_style = LineSolid; /* style for lines drawing and  */
	int cap_style = CapButt; /* style of the line's edje and */
	int join_style = JoinBevel; /*  joined lines.		*/
	int screen_num = DefaultScreen(display);

	gc = XCreateGC(display, win, valuemask, &values);
	if (gc < 0) {
		cerr << "XCreateGC:" << endl;
	}

	/* allocate foreground and background colors for this GC. */
	if (reverse_video) {
		XSetForeground(display, gc, WhitePixel(display, screen_num));
		XSetBackground(display, gc, BlackPixel(display, screen_num));
	} else {
		XSetForeground(display, gc, BlackPixel(display, screen_num));
		XSetBackground(display, gc, WhitePixel(display, screen_num));
	}

	/* define the style of lines that will be drawn using this GC. */
	XSetLineAttributes(display, gc, line_width, line_style, cap_style,
			join_style);

	/* define the fill style for the GC. to be 'solid filling'. */
	XSetFillStyle(display, gc, FillSolid);

	return gc;
}


//ctor (will load the images and display the initial screen)
GraphDisplay::GraphDisplay() {

	int screen_num; /* number of screen to place the window on.  */
    char *display_name = getenv("DISPLAY"); /* address of the X display.      */

	/* open connection with the X server. */
	display = XOpenDisplay(display_name);
	if (display == NULL) {
		cerr << "cannot connect to X server display_name" << endl;
		exit(1);
	}

	/* get the geometry of the default screen for our display. */
	screen_num = DefaultScreen(display);
	
    // make the new window 710x710
    width = 710;
    height = 710;

	/* create a simple window, as a direct child of the screen's   */
	/* root window. Use the screen's white color as the background */
	/* color of the window. Place the new window's top-left corner */
	/* at the given 'x,y' coordinates.                             */
	win = create_simple_window(display, width, height, 0, 0);

	/* allocate a new GC (graphics context) for drawing in the window. */
	gc = create_gc(display, win, 0);
	XSync(display, False);


    char tempArray [16] = {'K','Q','R','B','N','P','k','q','r','b','n','p', ' ', 'x', 'y','g'};
	string extension = ".xbm";
    string fileName;

    bitmap_width = bitmap_height = 80;
    axis_width = 640;
    axis_height = 30;
	for (int i = 0; i < 16; ++i) {
        if (tempArray[i] == ' ') {
            fileName = "blank.xbm";
        } else if (tempArray[i] == 'x') {
            fileName = "xaxis.xbm";
        } else if (tempArray[i] == 'y') {
            fileName = "yaxis.xbm";
        } else if (tempArray[i] == 'g') {
            fileName = "background.xbm";
        } else if (tempArray[i] != toupper(tempArray[i])) {
			fileName = tempArray[i];
            fileName += "black" + extension;
	    } else {
			fileName = tempArray[i];
            fileName += "white" + extension;
		}

		/* this variable will contain the ID of the newly created pixmap.    */
		Pixmap* bitmap = new Pixmap;

		/* these variables will contain the location of the hotspot of the   */
		/* loaded bitmap.                                                    */
		int hotspot_x, hotspot_y;
		hotspot_x = hotspot_y = 0;

		/* load the bitmap found in the file "icon.bmp", create a pixmap     */
		/* containing its data in the server, and put its ID in the 'bitmap' */
		/* variable.                                                         */
        int rc;

        // This section load all images (there are 16 of them, 12 for chess pieces, 1 for blank square, 2 for axis, 1 for background)
        if ((fileName != "xaxis.xbm") && (fileName != "yaxis.xbm") && (fileName != "background.xbm")) {
		    rc = XReadBitmapFile(display, win, fileName.c_str(),
				&bitmap_width, &bitmap_height, bitmap, &hotspot_x, &hotspot_y);
            imageMap[tempArray[i]] = bitmap;
        } else if (fileName == "xaxis.xbm") {
            xaxis = bitmap;
            rc = XReadBitmapFile(display, win, fileName.c_str(),
                    &axis_width, &axis_height, bitmap, &hotspot_x, &hotspot_y);
        } else if (fileName == "yaxis.xbm") {
            yaxis = bitmap;
            rc = XReadBitmapFile(display, win, fileName.c_str(),
                    &axis_height, &axis_width, bitmap, &hotspot_x, &hotspot_y);
        } else if (fileName == "background.xbm") {
            bg = bitmap;
            rc = XReadBitmapFile(display, win, fileName.c_str(),
                    &width, &height, bitmap, &hotspot_x, &hotspot_y);
        }
        // error checking for image loading
		switch (rc) {
		case BitmapOpenFailed:
			cerr << "XReadBitmapFile - could not open file: " << fileName << endl;
			exit(1);
			break;
		case BitmapFileInvalid:
			cerr << "XReadBitmapFile - file " << fileName << " doesn't contain a valid bitmap.\n";
			exit(1);
			break;
		case BitmapNoMemory:
			cerr << "XReadBitmapFile - not enough memory.\n";
			exit(1);
			break;
		}

        XSync(display,false);
        
	}
    // draws the background
     XCopyPlane(display, *bg, win, gc, 0, 0, width,
                height, 0, 0, 1);
    XSync(display, False);

    // draws the axes
    XCopyPlane(display, *xaxis, win, gc, 0, 0, axis_width,
				axis_height, 60, 0, 1);
	XSync(display, False);
    XCopyPlane(display, *yaxis, win, gc, 0, 0, axis_height,
                axis_width, 0, 60, 1);
    XSync(display, False);
    // draws a blank chess board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            undraw(Posn(i,j));
        }
    }
}

GraphDisplay::~GraphDisplay() {
	/* flush all pending requests to the X server. */
	XFlush(display);

	/* make a delay for a short period. */
	//sleep(4);

	/* close the connection to the X server. */

    /* Frees all the images loaded in to the program to prevent memory leaks */
    map<char,Pixmap*>::iterator iter;
    for (iter = imageMap.begin(); iter != imageMap.end(); ++iter) {
        XFreePixmap(display,*(iter->second));
        delete iter->second;
    }
    XFreePixmap(display,*xaxis);
    XFreePixmap(display,*yaxis);
    XFreePixmap(display,*bg);
    delete xaxis;
    delete yaxis;
    delete bg;
    XFreeGC(display,gc);
    XCloseDisplay(display);
}

/* Draws the appropriate piece image at the position specified by pos */
void GraphDisplay::draw (char piece, Posn pos) { 
	int y = pos.row * (bitmap_height+5) + 40;
	int x = pos.col * (bitmap_width+5) + 40;
	try {
		XCopyPlane(display, *(imageMap.at(piece)), win, gc, 0, 0, bitmap_width,
				bitmap_height, x, y, 1);
		XSync(display, false);
	} catch (const out_of_range& except) {
		cerr << "out of range error: " << except.what() << endl;
	}
}

/* Draws a blank square at Posn pos */
void GraphDisplay::undraw(Posn pos) {
    int y = pos.row * (bitmap_height+5) + 40;
	int x = pos.col * (bitmap_width+5) + 40;
	char blank = ' ';
    try {
	    XCopyPlane(display, *(imageMap.at(blank)), win, gc, 0, 0, bitmap_width,
				bitmap_height, x, y, 1);
		XSync(display, False);
	} catch (const out_of_range& except) {
		cerr << "out of range error: " << except.what() << endl;
	} 
}
