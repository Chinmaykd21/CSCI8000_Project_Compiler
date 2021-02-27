#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
#include "syntaxAnalysis.h"
#include "lexicalAnalysis.h"
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

    unordered_map<int, int> parenthesisMap;
    bool opParenthesis = areParenthesisBalanced(tokens, &parenthesisMap); // check Parenthesis
    bool opFunction = checkFunction(tokens); // check function
    bool opColons = checksemicolon(tokens); //check Semicolon

    if (opParenthesis == false)
        cout << "Syntax error: Parenthesis Not Balanced" << endl;
    else if (opColons == false)
        cout << "Syntax error: Missing semi-colon in a statement." << endl;
    else if (opFunction == false) 
            cout << "Please check the function definition properly." << endl;
    else{
    string ieVal = checkIfElseSyntax(0, tokens.size(), tokens, parenthesisMap);
    cout << "ieVal: " << ieVal << endl;
    }
}