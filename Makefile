CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = chess
OBJECTS = main.o ai.o chessboard.o bishop.o cell.o computer.o game.o graphdisplay.o human.o king.o knight.o move.o pawn.o piece.o posn.o queen.o rook.o textdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
