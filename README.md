# chess-x11

A chess game written in C++ with the X11 (XWindows) graphics library. It features the full set of rules for chess and 4 levels of computer AI, the highest of which is a minimax Chess AI.

See https://www.youtube.com/watch?v=BG_RJtxqxaQ for a demo of AI vs AI

## Instructions to run

1. Clone git repo
2. make
3. run chess binary

## Special instructions for different platforms

1. Mac
You will need to install XQuartz. After installing XQuartz, launch the xterm application. Run make and the binary in the xterm.

For Mac (and perhaps Linux), you may also need to change the -L in CXXFLAG in the Makefile to point at the correct location of the X11 library. The x11 library location can be found using the 
locate command, ie "locate libX11.dylib".



## Commands for game

Initial command to start a game:
game human computerX
where X is 1, 2, 3, or 4 (highest difficulty)

or game computerX computerX, or game human human

Example of command during game:
move e5 e7





