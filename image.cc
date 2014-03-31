#include "image.h"
#include "window.h"
#include <X11/Xlib.h>
#include <string>
#include <cstring>

using namespace std;

Image::Image(int width, int height, int hotspot_x, int hotspot_y, string sfileName, Xwindow* xwin) :
    bitmap(NULL), bitmap_width(width), bitmap_height(height), hotspot_x(hotspot_x), hotspot_y(hotspot_y), xwin(xwin) {
    fileName = new char[sfileName.length() + 1];
    strcpy(fileName,sfileName.c_str());    
//    XReadBitmapFile(display, *root_win, fileName.c_str(), &bitmap_width, &bitmap_height, bitmap, &hotspot_x, &hotspot_y);
    /* check for failure or success. */
    /*
    switch (rc) {
    case BitmapOpenFailed:
        cerr << "XReadBitmapFile - could not open file: " << fileName << endl;
        break;
    case BitmapFileInvalid:
        cerr << "XReadBitmapFile - file " << fileName << " doesn't contain a valid bitmap." << endl;
        break;
    case BitmapNoMemory:
        cerr << "XReadBitmapFile - not enough memory." << endl;
        break;
    case BitmapSuccess:
        // bitmap loaded successfully - do something with it...
        break;
    }
    */
}

void Image::drawImage (int x, int y) {
    Display *display = xwin->getDisplay();
    //Window root_win = DefaultRootWindow(display);
    
    if (bitmap != NULL) {
        XFreePixmap(display, *bitmap);
        bitmap = NULL;
    }
    bitmap = new Pixmap;

//    GC gc = XCreateGC(display, *bitmap, 0,(XGCValues *)0);

    XReadBitmapFile(display, *(xwin->getWindow()), fileName, &bitmap_width, &bitmap_height, bitmap, &hotspot_x, &hotspot_y);

    XCopyPlane(display, *bitmap, *(xwin->getWindow()), *(xwin->getGC()), 0, 0, bitmap_width, bitmap_height, x, y, 1);
}

Image::~Image () {
    Display *display = xwin->getDisplay();
    XFreePixmap(display, *bitmap);
    if (fileName != NULL) delete [] fileName;
}
