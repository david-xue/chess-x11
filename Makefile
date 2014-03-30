CXX = g++
CXXFLAGS = -Wall -MMD -g -lX11
EXEC = chess
OBJECTS = main.o ai.o chessboard.o bishop.o cell.o computer.o game.o graphdisplay.o human.o image.o king.o knight.o move.o pawn.o piece.o player.o posn.o queen.o rook.o textdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}


-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
