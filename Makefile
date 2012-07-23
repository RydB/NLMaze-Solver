CC=g++
CFLAGS=-c -O3 -Wall
GFLAGS=-g -Wall

all: zoolander

zoolander: main.o MazeNode.o MazeGraph.o MazeError.o Maze.o
	$(CC) -o zoolander main.o MazeNode.o MazeGraph.o MazeError.o Maze.o

debug: main.o
	$(CC) $(GFLAGS) -o zbug main.cpp MazeNode.cpp MazeGraph.cpp MazeError.cpp Maze.cpp
	
main.o: main.cpp Maze.h
	$(CC) $(CFLAGS) main.cpp

MazeNode.o: MazeNode.cpp MazeNode.h
	$(CC) $(CFLAGS) MazeNode.cpp

MazeGraph.o: MazeGraph.cpp MazeGraph.h
	$(CC) $(CFLAGS) MazeGraph.cpp

MazeError.o: MazeError.cpp MazeError.h
	$(CC) $(CFLAGS) MazeError.cpp

Maze.o: Maze.cpp Maze.h
	$(CC) $(CFLAGS) Maze.cpp

clean:
	rm -rf *.o zoolander *~
