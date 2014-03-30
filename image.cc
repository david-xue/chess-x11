#include "image.h"
#include "window.h"
#include <X11/Xlib.h>
#include <string>

using namespace std;

Image::Image(int width, int height, int hotspot_x, int hotspot_y, string fileName, Xwindow* xwin) :
    bitmap_width(width), bitmap_height(height), hotspot_x(hotspot_x), hotspot_y(hotspot_y), fileName(fileName) {
    root_win = xwin->getWindow();
    display = xwin->getDisplay();
    gc = xwin->getGC();
    XReadBitmapFile(display, *root_win, fileName.c_str(), &bitmap_width, &bitmap_height, &bitmap, &hotspot_x, &hotspot_y);
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
    XCopyPlane(display, bitmap, *root_win, *gc, 0, 0, bitmap_width, bitmap_height, x, y, 1);
}

Image::~Image () {
    XFreePixmap(display, bitmap);
}
