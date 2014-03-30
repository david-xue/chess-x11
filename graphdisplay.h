#ifndef __GRAPHDISPLAY_H__
#define __GRAPHDISPLAY_H__
#include <X11/Xlib.h>
#include <map>

class Posn;
class Xwindow;
class Image;

class GraphDisplay {

    Xwindow* xwindow;
    std::map<char,Image*> imageMap; //pointers to loaded images (mapped by char, eg K,k,Q)
    
    public:
    
    GraphDisplay();
    ~GraphDisplay();

    void draw(char, Posn);
    void undraw(Posn);

};

#endif
