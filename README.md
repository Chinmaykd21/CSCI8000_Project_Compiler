# Project_1
Write a simple compiler in C/C++. 

## Objective
Compiler is one of the core software in our system software stack. A vulnerable compiler can instrument malicious instruction in a binary. A compiler has two phases: front-end and back-end. In this project, we will write a simple compiler that will
- read a code using stdin
- tokenize the source (lexical analysis)
- check correctness of code (syntax analysis)
- generate a parse tree

# Programming Language used
C++

# How to run
###### run the following command to compile the compiler.cpp file
> make

###### once the compilation is successful, run the following command
> ./compiler file.cpp

file.cpp is the file which is to be compiled by our compiler.