#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <X11/Xlib.h>
#include <string>
class Xwindow;

class Image {
    Pixmap* bitmap;
    /* these variables will contain the dimensions of the loaded bitmap. */
    unsigned int bitmap_width, bitmap_height;
    /* these variables will contain the location of the hot-spot of the   */
    /* loaded bitmap.                                                    */
    int hotspot_x, hotspot_y;
    /* file name */
    char* fileName;
    /* this variable will contain the ID of the root window of the screen */
    /* for which we want the pixmap to be created.                        */
    
    Xwindow *xwin;
    //Window* root_win; //DefaultRootWindow(display); I didn't use this, I get from Xwindow
    //Display* display;
    //GC* gc; //graphics context (we'll get this from Window)

    public:
    Image(int, int, int, int, std::string, Xwindow*);
    void drawImage(int, int);
    ~Image(); //free's the pixmap

};

#endif
