CXX = g++
CXXFLAGS = -Wall -MMD -g -lX11 -L/opt/X11/lib
EXEC = chess
OBJECTS = main.o ai.o aitree.o chessboard.o bishop.o cell.o computer.o game.o graphdisplay.o human.o  king.o knight.o move.o pawn.o piece.o player.o posn.o queen.o rook.o textdisplay.o opening.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}


-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
