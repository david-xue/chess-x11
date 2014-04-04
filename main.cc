// This program satisfies all requirements of the Chess project.

// This is the main program intializing a Game object.
// It handles all inputs between games.

#include "game.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// read the player type and return an appropriate integer
int readPlayerType (const string &str) {
    if (str == "human") {
        return 0;
    }
    if (str.length() == 9) {
        if (str.substr(0, str.length()-1) == "computer") {
            return str[8] - '0';
        }
    }
    return -1;
}

// Main program, initialize Game
int main () {
    Game g;
    string s;
    while (getline(cin,s)) {
        istringstream ss(s);
        if (ss >> s) {
            if (s == "game") {
                string p1, p2;
                if ((ss >> p1) && (ss >> p2)) {
                    int white = readPlayerType(p1);
                    int black = readPlayerType(p2);
                    if ((white >= 0) && (black >= 0)) {
                        g.newGame(white,black);
                    }
                }
            } else if (s == "setup") {
                g.setup();
            } else if (s == "quit") { //not necessary, but it gives a way to quit the game without Ctrl-D/C
                break;
            }
        }
    }
}
