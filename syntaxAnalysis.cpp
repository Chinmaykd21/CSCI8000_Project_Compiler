#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
#include "syntaxAnalysis.h"
using namespace std;


// This will check the parameters follow the strict rules which have been set by the professor.
bool checkParameters(std::string parameters){
    vector<string> result;
    stringstream s_stream(parameters);
    while(s_stream.good()){
        string substr;
        getline(s_stream, substr, ',');
        result.push_back(substr);
    }
    /*for(int i=0; i< result.size();i++){
        cout<< result[i]<< endl;
    } */   
    return true;
}

bool checkFunction(std::vector<std::string> tokens){
    bool returnType; // This is to identify the return type of the function
    bool functionName;
    bool flagParameters;
    int count = 0;
    string parameters;
    // cout<<tokens.size()<<endl;
    // This loop will be used to
    for (int i= 0; i < tokens.size(); i++){
        if ((tokens[i] == "int") || (tokens[i] == "float") || (tokens[i] == "char") || (tokens[i] == "double") || (tokens[i] == "void")){
            returnType = true;
        }

        // This condition will check if the value of token[i] is other than int, float, char, double, void and also it will check if the next element is start of the (.
        // If this condition is satisfied then it will check if first character of token[i] is between ascii value 65-90 & 97-122.
        if(i < tokens.size() - 1){
            if ((tokens[i] != "int") && (tokens[i] != "float") && (tokens[i] != "char") && (tokens[i] != "double") && (tokens[i] != "void") && (tokens[i+1] == "(")){
            string checkChar =  tokens[i];
            for (int k=0; k<checkChar.size();k++){
                if (((int(checkChar[k]) >= 65) && (int(checkChar[k]) <= 90)) || ((int(checkChar[k]) >= 97) && (int(checkChar[k] <= 122)))){
                    functionName = true;
                }
                else{
                    functionName = false;
                    }
                }   
            }
        

            //This condition will check if the tokens[i] == "(", then it will store all the elements in single string till ")" came in value for tokens[i]
            if (tokens[i] == "("){
                int j = i + 1;
                while(tokens[j] != ")"){
                    if(tokens[j] != "EndOfLine"){
                        parameters = parameters + " " + tokens[j];
                        j++;
                    }
                }
                //cout << parameters << endl;
                // This function will check all the parameters follow the appropriate declaration format or not. Uncomment it after it is defined
                if (parameters.size() != 0){
                    flagParameters = checkParameters(parameters);
                }else{
                    flagParameters=true;
                }
            }
        }
        //clear out the parameter string at the end
        parameters ="";
        // cout<<"count size:"<<endl;
        // cout<<count<<endl;
        // count++;
    }
    if ((returnType==true) && (functionName == true) && (flagParameters == true)){
        //cout<<"END TRUE"<<endl;
        return true;
    }
    else{
        //cout<<"END FALSE"<<endl;
        return false;
    }
}

bool checksemicolon(std::vector<std::string> tokens)
{
    for (int i = 0; i < tokens.size(); i++)
    {
        //This will be checked for ";"
        if (tokens[i] == "EndOfLine")
        {
            //This condition will check if the element before the word "EndOfLine" does not contains {,},>

            string prevChar = tokens[i - 1];
            if (prevChar == "{" || prevChar == "}" || prevChar == ">")
            {
            }
            else if (prevChar == ")")
            {
                if (tokens[i + 1] == "{")
                {
                }
            }
            else if (prevChar != ";")
            {
                //cout << "i: " << i << " " << tokens[i - 1] << endl;
                return false;
            }
        }
    }
    return true;
}

bool areParenthesisBalanced(std::vector<std::string> tokens, std::unordered_map<int, int> *imap)
{
    stack<char> t;
    int t1;
    stack<string> s;
    string x;
    unordered_map<int, int> umap;
    vector<string> temp;

    //cout << "Start function areParenthesisBalanced--" << endl;
    // Traversing the Expression
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] == "(" || tokens[i] == "[" || tokens[i] == "{" || tokens[i] == ")" || tokens[i] == "]" || tokens[i] == "}")
        {
            //cout << "i: " << i << " token: " << tokens[i] << endl;
            if (tokens[i] == "(" || tokens[i] == "[" || tokens[i] == "{")
            {
                //cout << tokens[i];
                // Push the element in the stack
                s.push(tokens[i]);
                t.push(i);
                temp.push_back(tokens[i]);
                continue;
            }

            // IF current current character is not opening
            // bracket, then it must be closing. So stack
            // cannot be empty at this point.
            if (s.empty())
                return false;

            if (tokens[i] == ")")
            {
                //cout << tokens[i] << endl;
                t1 = t.top();
                t.pop();
                umap[t1] = i;
                // Store the top element in a
                x = s.top();
                s.pop();
                temp.push_back(tokens[i]);
                if (x == "{" || x == "[")
                    return false;
            }
            else if (tokens[i] == "}")
            {
                // cout << tokens[i] << endl;
                ;
                t1 = t.top();
                t.pop();
                umap[t1] = i;
                // Store the top element in b
                x = s.top();
                s.pop();
                temp.push_back(tokens[i]);
                if (x == "(" || x == "[")
                    return false;
            }
            else if (tokens[i] == "]")
            {
                //cout << tokens[i] << endl;
                ;
                t1 = t.top();
                t.pop();
                umap[t1] = i;
                // Store the top element in b
                x = s.top();
                s.pop();
                temp.push_back(tokens[i]);
                if (x == "(" || x == "{")
                    return false;
            }
        }
    }
    //cout << endl;

    *imap = umap;

    return (s.empty());
}

std::string checkIfElseSyntax(int start, int end, std::vector<std::string> tokens, std::unordered_map<int, int> parenthesisMap)
{
    //cout << endl;
    //cout << "start: " << start << ", end: " << end << endl;
    for (int i = start; i < end; i++)
    {
        if (tokens[i] == "if")
        {
            //cout << "Found If, i: " << i << endl;

            if (i < (end - 2))
            {
                if (tokens[i + 1] == "(")
                {
                    //cout << "I" << endl;
                    int closeBracket = i+5;
                    if(i<(end-1)){
                    auto it = parenthesisMap.find(i + 1);
                    //cout << "I--" << endl;
                    if(it->second){
                        //cout << "I..." << endl;
                        closeBracket = it->second;
                    }
                    }
                    //cout << "I1" << endl;
                    ////////////Insert Code to check the conditional statement////////////////
                    /*bool check = checkIfConditionalStatement(i+2,closeBracket,tokens);
                if(!check){
                    return "Syntax error: Invalid condition in if statement";
                }*/

                    if ((tokens[closeBracket + 1] == "{") && ((closeBracket + 1) < (end - 1)))
                    {
                        //cout << "II" << endl;

                        if((closeBracket+1)<end-1){
                        auto it = parenthesisMap.find(closeBracket + 1);
                        int closeParNum = i+10;//it->second;

                        //cout << "----Recursive call start----" << endl;
                        string op = checkIfElseSyntax(closeBracket + 2, closeParNum, tokens, parenthesisMap);
                        //cout << "----Recursive call end----" << endl;
                        }
                    }
                    else
                        return "Syntax error: Missing {";
                }
                else
                    return "Syntax error: Missing (";
            }
            else 
                return "syntax error";
        }
        else if (tokens[i] == "else")
        {
            if (tokens[i + 1] == "{")
            {
                auto it = parenthesisMap.find(i + 1);
                int closeParNum = it->second;
                //cout << "----Recursive call start----" << endl;
                string op = checkIfElseSyntax(i + 2, closeParNum, tokens, parenthesisMap);
                //cout << "----Recursive call end----" << endl;
            }
            else if (tokens[i + 1] == "if")
            {
            }
            else
                return "Syntax error: invalid else condition";
        }
    }
    return "no error";
}