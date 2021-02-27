# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
#   -g      - This flag adds deubgging information to the executable file
#   -Wall   - This flag is used to turn on most computer warnings
CFLAGS = -g
LFLAGS = -c

all: mycompiler

mycompiler: main.o lexicalAnalysis.o syntaxAnalysis.o
	$(CC) $(CFLAGS) main.o lexicalAnalysis.o syntaxAnalysis.o -o compiler

main.o: main.cpp
	$(CC) $(LFLAGS) main.cpp

lexicalAnalysis.o: lexicalAnalysis.cpp
	$(CC) $(LFLAGS) lexicalAnalysis.cpp

syntaxAnalysis.o: syntaxAnalysis.cpp
	$(CC) $(LFLAGS) syntaxAnalysis.cpp
clean:
	rm -rf *o compiler