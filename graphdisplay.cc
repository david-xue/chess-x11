#include "graphdisplay.h"
#include "image.h"
#include "window.h"
#include "posn.h"

#include <X11/Xlib.h>
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

GraphDisplay::GraphDisplay() {
    xwindow = new Xwindow();
    char tempArray [12] = {'K','Q','R','B','K','P','k','q','r','b','k','p'};
    string extension = ".bmp";
    string fileName;
    for (int i=0; i<12; ++i) {
        if (tempArray[i] != toupper(tempArray[i])) {
            //fileName = tempArray[i] + "black" + extension;
            fileName = "testingblack.bmp";
        } else {
            //fileName = tempArray[i] + "white" + extension;
            fileName = "testingwhite.bmp";
        }
        // the params are width, height, hotspot_x, hotspot_y, fileName, xwindow
        imageMap[tempArray[i]] = new Image(40,40,0,0,fileName,xwindow);
    }
}

GraphDisplay::~GraphDisplay() {
    map<char,Image*>::iterator iter;
    for (iter = imageMap.begin(); iter != imageMap.end(); ++iter) {
        delete iter->second;
    }
    delete xwindow;
}

void GraphDisplay::draw (char piece, Posn pos) { 
    int y = pos.row * 40;
    int x = pos.col * 40;
    try {
        imageMap.at(piece)->drawImage(x,y);
    } catch (const out_of_range& except) {
        cerr << "out of range error: " << except.what() << endl;
    }
}

void GraphDisplay::undraw(Posn pos) {
    int y = pos.row * 40;
    int x = pos.col * 40;
    xwindow->fillRectangle(x, y, 40, 40, Xwindow::White); //draw a white rectangle in place
}
