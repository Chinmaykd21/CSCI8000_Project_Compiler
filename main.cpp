#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
#include "lexicalAnalysis.h"
#include "syntaxAnalysis.h"
using namespace std;

int main(int argc, char **argv)
{

    if (argc <= 1)
    {
        cout << "Input file missing!" << endl;
        return 0;
    }

    fstream newfile;
    vector<string> tokens;

    int input_size = sizeof(argv[1]) / sizeof(char);
    string input = convertToString(argv[1], input_size);

    tokens = Tokenize(input); //tokenize the input file

    unordered_map<int, int> imap;
    bool opParenthesis = areParenthesisBalanced(tokens, &imap); // check Parenthesis
    bool opFunction = checkFunction(tokens); // check function
    bool opColons = checksemicolon(tokens); //check Semicolon

    if (opParenthesis == false)
        cout << "Syntax error: Parenthesis Not Balanced" << endl;
    else if (opColons == false)
        cout << "Syntax error: Missing semi-colon in a statement." << endl;
    else if (opFunction == false) 
            cout << "Please check the function definition properly." << endl;
}