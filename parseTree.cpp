#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
#include "parseTree.h"
using namespace std;

bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

void parseTree(int start, int end, vector<string> tokens, unordered_map<int, int> parenthesisMap, unordered_map<string, string> varTypeMap, string indent)
{
    unordered_set<string> specialCharSet;
    specialCharSet.insert("main");
    specialCharSet.insert("int");
    specialCharSet.insert("char");
    specialCharSet.insert("string");
    specialCharSet.insert("float");
    specialCharSet.insert("return");
    specialCharSet.insert("void");
    specialCharSet.insert("if");
    specialCharSet.insert("else");
    specialCharSet.insert(",");
    specialCharSet.insert("\"");
    specialCharSet.insert(";");
    specialCharSet.insert("{");
    specialCharSet.insert("}");
    specialCharSet.insert("(");
    specialCharSet.insert(")");
    specialCharSet.insert("[");
    specialCharSet.insert("]");
    specialCharSet.insert("=");
    specialCharSet.insert("+");
    specialCharSet.insert("-");
    specialCharSet.insert("/");
    specialCharSet.insert("EndOfLine");

    unordered_map<string, string> newVarTypeMap;
    newVarTypeMap = varTypeMap;
    for (int i = start; i < end; i++)
    {
        //cout << "i: " << i << " tokens[i]: " << tokens[i] << endl;

        if ((tokens[i] == "int") || (tokens[i] == "string") || (tokens[i] == "char") || (tokens[i] == "float") || (tokens[i] == "void"))
        {
            bool functionLineFlag = false;
            if (tokens[i + 2] == "(")
            {
                functionLineFlag = true;
                auto it = parenthesisMap.find(i + 2);
                int closeBracNum = it->second;
                cout << "function " << tokens[i + 1] << endl;
                cout << indent << " return " << tokens[i] << endl;
                if (closeBracNum != (i + 3))
                {
                    for (int j = (i + 3); j < closeBracNum; j++)
                    {
                        if (j == (i + 3))
                        {
                            newVarTypeMap[tokens[j + 1]] = tokens[j];
                            cout << indent << " param " << tokens[j] << " " << tokens[j + 1] << endl;
                        }
                        else if (tokens[j] == ",")
                        {
                            newVarTypeMap[tokens[j + 2]] = tokens[j + 1];
                            cout << indent << " param " << tokens[j + 1] << " " << tokens[j + 2] << endl;
                        }
                    }
                }
                int openParNum;
                if (tokens[closeBracNum + 1] == "EndOfLine")
                    openParNum = closeBracNum + 2;
                else
                    openParNum = closeBracNum + 1;
                it = parenthesisMap.find(openParNum);
                int closeParNum = it->second;
                parseTree(closeBracNum + 2, closeParNum, tokens, parenthesisMap, newVarTypeMap, indent.append("-"));
                i = closeParNum;
                indent.pop_back();
                cout << endl;

                //cout << "this should be a function line, i: " << i << " ,tokens[i]: " << tokens[i] << endl;
            }
            else if ((tokens[i + 2] == ",") || (tokens[i + 2] == ";"))
            {
                //cout << "this should not be a function line,i:  " << i << " ,tokens[i]: " << tokens[i] << endl;
                if (tokens[i + 2] == ",")
                {
                    int k = i + 2;
                    while (tokens[k] != ";")
                    {
                        newVarTypeMap[tokens[k - 1]] = tokens[i];
                        cout << indent << " local " << tokens[i] << " " << tokens[k - 1] << endl;
                        k = k + 2;
                    }
                    newVarTypeMap[tokens[k - 1]] = tokens[i];
                    cout << indent << " local " << tokens[i] << " " << tokens[k - 1] << endl;
                }
            }
        }
        else if (tokens[i] == "if")
        {
            int openBracNum = i + 1;
            auto it = parenthesisMap.find(openBracNum);
            int closeBracNum = it->second;
            int openParNum;
            if (tokens[closeBracNum + 1] == "EndOfLine")
                openParNum = closeBracNum + 2;
            else
                openParNum = closeBracNum + 1;

            if ((closeBracNum - openBracNum) == 4)
            {
                string op;
                if (tokens[openBracNum + 2] == "<")
                {
                    op = "lt";
                }
                else if (tokens[openBracNum + 2] == ">")
                {
                    op = "gt";
                }
                cout << indent << " if " << tokens[openBracNum + 1] << " " << op << " " << tokens[openBracNum + 3] << endl;
            }
            else if ((closeBracNum - openBracNum) == 5)
            {
                string op;
                if (tokens[openBracNum + 2] == "<")
                {
                    op = "lte";
                }
                else if (tokens[openBracNum + 2] == ">")
                {
                    op = "gte";
                }
                else if (tokens[openBracNum + 2] == "=")
                {
                    op = "eq";
                }
                cout << indent << " if " << tokens[openBracNum + 1] << " " << op << " " << tokens[openBracNum + 3] << endl;
            }

            it = parenthesisMap.find(openParNum);
            int closeParNum = it->second;
            parseTree(openParNum + 1, closeParNum, tokens, parenthesisMap, newVarTypeMap, indent.append("-"));
            i = closeParNum;
            indent.pop_back();
        }
        else if (tokens[i] == "else")
        {
            if (tokens[i + 1] == "if")
            {
                //cout << "I" << endl;
                int openBracNum = i + 2;
                auto it = parenthesisMap.find(openBracNum);
                //cout << "II" << endl;
                //cout << "i: " << i <<" tokens[i]: " << tokens[i] << " tokens[i+1]: " << tokens[i+1] << endl;
                //cout << "start: " << start << " end: " << end << endl;
                int closeBracNum = it->second;
                //cout << "III" << endl;
                int openParNum;
                if (tokens[closeBracNum + 1] == "EndOfLine")
                    openParNum = closeBracNum + 2;
                else
                    openParNum = closeBracNum + 1;
                //cout << "IV" << endl;
                if ((closeBracNum - openBracNum) == 4)
                {
                    string op;
                    //  cout << "tokens[openBracNum] " << tokens[openBracNum] << endl;
                    // cout << "V" << endl;
                    if (tokens[openBracNum + 2] == "<")
                    {
                        //   cout << "VI" << endl;
                        op = "lt";
                    }
                    else if (tokens[openBracNum + 2] == ">")
                    {
                        // cout << "VI" << endl;
                        op = "gt";
                    }
                    cout << indent << " else if " << tokens[openBracNum + 1] << " " << op << " " << tokens[openBracNum + 3] << endl;
                }
                else if ((closeBracNum - openBracNum) == 5)
                {
                    string op;
                    if (tokens[openBracNum + 2] == "<")
                    {
                        op = "lte";
                    }
                    else if (tokens[openBracNum + 2] == ">")
                    {
                        op = "gte";
                    }
                    else if (tokens[openBracNum + 2] == "=")
                    {
                        op = "eq";
                    }
                    cout << indent << " else if " << tokens[openBracNum + 1] << " " << op << " " << tokens[openBracNum + 3] << endl;
                }

                it = parenthesisMap.find(openParNum);
                int closeParNum = it->second;
                parseTree(openParNum + 1, closeParNum, tokens, parenthesisMap, newVarTypeMap, indent.append("-"));
                i = closeParNum;
                indent.pop_back();
            }
            else
            {
                int openParNum;
                if (tokens[i + 1] == "EndOfLine")
                    openParNum = i + 2;
                else
                    openParNum = i + 1;
                auto it = parenthesisMap.find(openParNum);
                int closeParNum = it->second;
                cout << indent << " else" << endl;
                parseTree(openParNum + 1, closeParNum, tokens, parenthesisMap, newVarTypeMap, indent.append("-"));
                i = closeParNum;
                indent.pop_back();
            }
        }
        else if (specialCharSet.find(tokens[i]) == specialCharSet.end())
        {
            if (!is_number(tokens[i]))
            {
               // cout << "I" << endl;
                if (tokens[i + 1] == "(")
                {
                    string fnName = tokens[i];
                    //cout << "II here" << endl;
                    int openBracNum = i + 1;
                    //cout << "tokens[openBracNum]: " << tokens[openBracNum] << endl;
                    /*cout << "\nParenthesis map : \n";
                                unordered_map<int, int>::iterator itr;
                                for (itr = parenthesisMap.begin(); itr != parenthesisMap.end(); itr++)
                                {

                                    cout << itr->first << "  " << itr->second << endl;
                                }
                                cout << "--------------" << endl;*/
                    auto it = parenthesisMap.find(openBracNum);
                    //cout << "III here: " << it -> second << endl;
                    int closeBracNum = it->second;
                    //cout << "IV here" << endl;
                    
                    cout << indent << " call fn " << tokens[i] << endl;
                    indent.append("-");
                    for (int j = openBracNum + 1; j < closeBracNum; j++)
                    {
                        if (tokens[j] != ",")
                        {

                            if (tokens[j] == "\"")
                            {
                                int closeQuotes= 0; // code fixed according to github issue uninitialized variable #11
                                string stringVal = "\"";
                                for (int k = j + 1; k < end; k++)
                                {
                                    stringVal.append(tokens[k]);
                                    if (tokens[k] == "\"")
                                    {
                                        closeQuotes = k;
                                        break;
                                    }
                                }
                                cout << indent << " arg "
                                     << " string " << stringVal << endl;
                                j = closeQuotes + 1;
                                i = j;
                            }
                            else
                            {
                                //cout << "V, j: " << j << " tokens[j]: " << tokens[j] << endl;
                                /*cout << "\nAll Elements : \n";
                                unordered_map<string, string>::iterator itr;
                                for (itr = newVarTypeMap.begin(); itr != newVarTypeMap.end(); itr++)
                                {

                                    cout << itr->first << "  " << itr->second << endl;
                                }
                                cout << "--------------" << endl;*/
                                string key;
                                //cout << "fnNAme: " << fnName << endl;
                                if (fnName == "scanf")
                                {
                                   // cout << "I-" << endl;
                                    if(tokens[j].substr(0,1)=="&"){
                                        key = tokens[j].substr(1);
                                       // cout << "II-" << endl;
                                    }
                                }
                                else
                                {
                                    //cout << "II" << endl;
                                    key = tokens[j];
                                }
                               // cout << "key: " << key << endl;
                                auto it1 = newVarTypeMap.find(key);
                                 //cout << "VI" << endl;
                                //cout << it1->second << endl;
                                string type = it1->second;
                                //cout << "VII" << endl;
                                cout << indent << " arg " << type << " " << key << endl;
                            }
                        }
                    }
                    indent.pop_back();
                }
            }
        }
    }
    /*cout << "\nAll Elements : \n";
    unordered_map<string, string>:: iterator itr;
    for (itr = newVarTypeMap.begin(); itr != newVarTypeMap.end(); itr++)
    {

        cout << itr->first << "  " << itr->second << endl;
     }
     cout <<"--------------" << endl;*/
}

