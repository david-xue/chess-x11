CXX = g++
CXXFLAGS = -Wall -MMD -lX11
EXEC = chess
OBJECTS = main.o ai.o chessboard.o bishop.o cell.o computer.o game.o graphdisplay.o human.o king.o knight.o move.o  piece.o posn.o queen.o rook.o textdisplay.o window.o pawn.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}


-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
