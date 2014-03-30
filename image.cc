
class Image {
    Pixmap bitmap;
    /* these variables will contain the dimensions of the loaded bitmap. */
    unsigned int bitmap_width, bitmap_height;
    /* these variables will contain the location of the hot-spot of the   */
    /* loaded bitmap.                                                    */
    int hotspot_x, hotspot_y;
    /* this variable will contain the ID of the root window of the screen */
    /* for which we want the pixmap to be created.                        */
    Window root_win; // = DefaultRootWindow(display);
    /* load the bitmap found in the file "icon.bmp", create a pixmap      */
    /* containing its data in the server, and put its ID in the 'bitmap'  */
    /* variable.                                                         */

    GC gc; //graphics context (we'll get this from Window)

    int rc = XReadBitmapFile(display, root_win,"icon.bmp", &bitmap_width, &bitmap_height, &bitmap, &hotspot_x, &hotspot_y);
    /* check for failure or success. */
    switch (rc) {
        case BitmapOpenFailed:
            fprintf(stderr, "XReadBitmapFile - could not open file 'icon.bmp'.\n");
            break;
        case BitmapFileInvalid:
            fprintf(stderr,"XReadBitmapFile - file '%s' doesn't contain a valid bitmap.\n", "icon.bmp");
            break;
        case BitmapNoMemory:
            fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
            break;
        case BitmapSuccess:
            /* bitmap loaded successfully - do something with it... */
            break;
    }

    public:
    Image(Window*, int, int, char*);
    void drawImage(int, int);
    ~Image(); //free's the pixmap

};

Image::Image(Window*
