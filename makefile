all: main.cpp
	g++-4.8 -std=c++0x filter.cpp scanner.cpp parser.cpp testTree.cpp varStack.cpp -c
	g++-4.8 -std=c++0x filter.o scanner.o parser.o testTree.o varStack.o main.cpp -o comp
clean:
	rm comp filter.o scanner.o parser.o testTree.o varStack.o out.asm
