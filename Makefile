# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
#   -g      - This flag adds deubgging information to the executable file
#   -Wall   - This flag is used to turn on most computer warnings
CFLAGS = -g

all: mycompiler

mycompiler: 
	$(CC) $(CFLAGS) compiler.cpp -o compiler

clean:
	rm -rf *o compiler