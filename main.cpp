#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
#include "syntaxAnalysis.h"
#include "lexicalAnalysis.h"
#include "parseTree.h"
using namespace std;

int main(int argc, char **argv)
{

    if (argc <= 1)
    {
        cout << "Usage: ./compiler arg1\n" << endl;
        cout << "arg1: path_to_file/file_name OR file_name" << endl;
        return 0;
    }
    vector<string> tokens;
    tokens = Tokenize(argv[1]); //tokenize the input file

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
    //string ieVal = checkIfElseSyntax(0, tokens.size(), tokens, parenthesisMap);
    //cout << "ieVal: " << ieVal << endl;
    unordered_map<string, string> varTypeMAp;
    parseTree(0, tokens.size(), tokens, parenthesisMap, varTypeMAp, "-");
    }
}
