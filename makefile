all: Lab1

CXX = g++

LINKFLAGS = -Wall -fomit-frame-pointer -funroll-all-loops -O0 -g

Lab1: main.o parser.o block.o box.o
	$(CXX) $(LINKFLAGS) main.o -o Lab1

main.o: main.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" main.cpp -c

parser.o: ./src/parser.cpp ./src/parser.h
	$(CXX) $(LINKFLAGS) ./src/parser.cpp -c

block.o: ./src/block.cpp ./src/block.h
	$(CXX) $(LINKFLAGS) ./src/block.cpp -c

box.o: ./src/box.cpp ./src/box.h
	$(CXX) $(LINKFLAGS) ./src/box.cpp -c
clean:
	rm -rf *.o *.gch Lab1






