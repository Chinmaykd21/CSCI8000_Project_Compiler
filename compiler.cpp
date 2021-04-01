#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
using namespace std;

string convertToString(char *a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}

// This will check the parameters follow the strict rules which have been set by the professor.
bool checkParameters(string parameters)
{
    vector<string> result;
    stringstream s_stream(parameters);
    while (s_stream.good())
    {
        string substr;
        getline(s_stream, substr, ',');
        result.push_back(substr);
    }
    /*for(int i=0; i< result.size();i++){
        cout<< result[i]<< endl;
    } */
    return true;
}

bool checkFunction(vector<string> tokens)
{
    bool returnType; // This is to identify the return type of the function
    bool functionName;
    bool flagParameters;
    int count = 0;
    string parameters;
    // cout<<tokens.size()<<endl;
    // This loop will be used to
    for (int i = 0; i < tokens.size(); i++)
    {
        if ((tokens[i] == "int") || (tokens[i] == "float") || (tokens[i] == "char") || (tokens[i] == "double") || (tokens[i] == "void"))
        {
            returnType = true;
        }

        // This condition will check if the value of token[i] is other than int, float, char, double, void and also it will check if the next element is start of the (.
        // If this condition is satisfied then it will check if first character of token[i] is between ascii value 65-90 & 97-122.
        if (i < tokens.size() - 1)
        {
            if ((tokens[i] != "int") && (tokens[i] != "float") && (tokens[i] != "char") && (tokens[i] != "double") && (tokens[i] != "void") && (tokens[i + 1] == "("))
            {
                string checkChar = tokens[i];
                for (int k = 0; k < checkChar.size(); k++)
                {
                    if (((int(checkChar[k]) >= 65) && (int(checkChar[k]) <= 90)) || ((int(checkChar[k]) >= 97) && (int(checkChar[k] <= 122))))
                    {
                        functionName = true;
                    }
                    else
                    {
                        functionName = false;
                    }
                }
            }

            //This condition will check if the tokens[i] == "(", then it will store all the elements in single string till ")" came in value for tokens[i]
            if (tokens[i] == "(")
            {
                int j = i + 1;
                while (tokens[j] != ")")
                {
                    if (tokens[j] != "EndOfLine")
                    {
                        parameters = parameters + " " + tokens[j];
                        j++;
                    }
                }
                //cout << parameters << endl;
                // This function will check all the parameters follow the appropriate declaration format or not. Uncomment it after it is defined
                if (parameters.size() != 0)
                {
                    flagParameters = checkParameters(parameters);
                }
                else
                {
                    flagParameters = true;
                }
            }
        }
        //clear out the parameter string at the end
        parameters = "";
        // cout<<"count size:"<<endl;
        // cout<<count<<endl;
        // count++;
    }
    if ((returnType == true) && (functionName == true) && (flagParameters == true))
    {
        //cout<<"END TRUE"<<endl;
        return true;
    }
    else
    {
        //cout<<"END FALSE"<<endl;
        return false;
    }
}

bool checksemicolon(vector<string> tokens)
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
                cout << "error, i: " << i << " tokens[i+1]: " << tokens[i + 1] << endl;
                return false;
            }
        }
    }
    return true;
}

bool areParenthesisBalanced(vector<string> tokens, unordered_map<int, int> *imap)
{
    stack<int> t;
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
                int p = t.top();
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

vector<string> Tokenize(string input)
{
    vector<string> tokens;
    fstream newfile;

    newfile.open(input, ios::in);

    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            stringstream check1(tp);
            string intermediate;
            while (getline(check1, intermediate, ' '))
            {
                vector<int> indexes;
                bool flag = true;

                if (intermediate.find("(") != std::string::npos)
                {
                    int c = intermediate.find("(");
                    indexes.push_back(c);
                    flag = false;
                    //cout << "subintermediate: " << subintermediate << endl ;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("(") != std::string::npos)
                    {
                        int s = subintermediate.find("(");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }

                if (intermediate.find("=") != std::string::npos)
                {
                    int c = intermediate.find("=");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("=") != std::string::npos)
                    {
                        int s = subintermediate.find("=");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find("+") != std::string::npos)
                {
                    int c = intermediate.find("+");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("+") != std::string::npos)
                    {
                        int s = subintermediate.find("+");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find("-") != std::string::npos)
                {
                    int c = intermediate.find("-");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("-") != std::string::npos)
                    {
                        int s = subintermediate.find("-");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find("<") != std::string::npos)
                {
                    int c = intermediate.find("<");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("<") != std::string::npos)
                    {
                        int s = subintermediate.find("<");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find(">") != std::string::npos)
                {
                    int c = intermediate.find(">");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find(">") != std::string::npos)
                    {
                        int s = subintermediate.find(">");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find("/") != std::string::npos)
                {
                    int c = intermediate.find("/");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("/") != std::string::npos)
                    {
                        int s = subintermediate.find("/");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find(")") != std::string::npos)
                {
                    int c = intermediate.find(")");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find(")") != std::string::npos)
                    {
                        int s = subintermediate.find(")");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find(",") != std::string::npos)
                {
                    int c = intermediate.find(",");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find(",") != std::string::npos)
                    {
                        int s = subintermediate.find(",");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find(";") != std::string::npos)
                {
                    int c = intermediate.find(";");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find(";") != std::string::npos)
                    {
                        int s = subintermediate.find(";");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find("{") != std::string::npos)
                {
                    int c = intermediate.find("{");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("{") != std::string::npos)
                    {
                        int s = subintermediate.find("{");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find("}") != std::string::npos)
                {
                    int c = intermediate.find("}");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("}") != std::string::npos)
                    {
                        int s = subintermediate.find("}");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (intermediate.find("\"") != std::string::npos)
                {
                    int c = intermediate.find("\"");
                    indexes.push_back(c);
                    flag = false;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    while (subintermediate.find("\"") != std::string::npos)
                    {
                        int s = subintermediate.find("\"");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                }
                if (flag == true)
                {
                    if (intermediate.size() > 0)
                    {
                        tokens.push_back(intermediate);
                    }
                }
                else
                {
                    sort(indexes.begin(), indexes.end());
                    if (intermediate.size() == 1)
                    {
                        string s;
                        s.push_back(intermediate.at(0));
                        tokens.push_back(s);
                    }
                    for (int i = 0; i < indexes.size(); i++)
                    {
                        //cout << "Inside for loop" << endl;
                        //cout << "intermediate: " << intermediate << endl;
                        //cout << "i: " << i << ", indexes[i]: " << indexes[i] << endl;

                        if (i == 0)
                        {
                            if (indexes[i] != 0)
                            {
                                int len = indexes[i];
                                tokens.push_back(intermediate.substr(0, len));
                                //tokens.push_back(intermediate.substr(0, indexes[i]));
                                string s;
                                s.push_back(intermediate.at(indexes[i]));
                                if (s.size() != 0)
                                    tokens.push_back(s);
                            }
                            if (indexes.size() == 1)
                            {
                                if (indexes[i] != (intermediate.size() - 1))
                                {
                                    if (indexes[i] == 0)
                                    {
                                        string s;
                                        s.push_back(intermediate.at(indexes[i]));
                                        if (s.size() != 0)
                                            tokens.push_back(s);
                                    }
                                    int len = intermediate.size() - indexes[i];
                                    string inp = intermediate.substr((indexes[i] + 1), len);
                                    if (inp.size() != 0)
                                        tokens.push_back(inp);
                                    //tokens.push_back(intermediate.substr((indexes[i] + 1), intermediate.size()));
                                }
                            }
                        }
                        else if (i == (indexes.size() - 1))
                        {
                            int lena = indexes[i] - (indexes[i - 1] + 1);
                            string a = intermediate.substr((indexes[i - 1] + 1), lena);
                            //string a = intermediate.substr((indexes[i - 1] + 1), indexes[i]);
                            int lenb = intermediate.size() - (indexes[i] + 1);
                            string b = intermediate.substr((indexes[i] + 1), lenb);
                            //string b = intermediate.substr((indexes[i] + 1), intermediate.size());
                            //cout << "a: " << a << ", b: " << b << endl;
                            if ((indexes[i - 1] + 1) != indexes[i])
                            {
                                if (a.size() != 0)
                                    tokens.push_back(a);
                            }
                            string s;
                            s.push_back(intermediate.at(indexes[i]));
                            if (s.size() != 0)
                                tokens.push_back(s);
                            if (b.size() != 0)
                                tokens.push_back(b);
                        }
                        else
                        {
                            int len = indexes[i] - (indexes[i - 1] + 1);
                            string b = intermediate.substr((indexes[i - 1] + 1), len);
                            //cout << "in else, b: " << b << endl;
                            if (b.size() != 0)
                                tokens.push_back(b);
                            //tokens.push_back(intermediate.substr((indexes[i - 1] + 1), indexes[i]));
                            string s;
                            s.push_back(intermediate.at(indexes[i]));
                            if (s.size() != 0)
                                tokens.push_back(s);
                        }
                    }
                }
            }
            if (tp.find_first_not_of(' ') != std::string::npos)
            {
                tokens.push_back("EndOfLine");
            }
        }
        /*cout << "\n----- AFTER TOKENIZING(TOKENS): -----\n\n";
        for (int i = 0; i < tokens.size(); i++)
            cout << tokens[i] << '\n';*/

        newfile.close(); //close the file object.
    }
    else
    {
        cout << "File not found!" << endl;
    }
    return tokens;
}

bool checkIfConditionalStatement(int start, int end, vector<string> tokens)
{

    if ((end - start) == 3)
    {
        for (int a = start; a < end; a++)
        {
            if ((a == start) || (a == end - 1))
            {
                string checkChar = tokens[a];
                for (int k = 0; k < checkChar.size(); k++)
                {
                    if (((int(checkChar[k]) >= 65) && (int(checkChar[k]) <= 90)) || ((int(checkChar[k]) >= 97) && (int(checkChar[k] <= 122))))
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                if ((tokens[a] != "<") && (tokens[a] != ">"))
                {
                    return false;
                }
            }
        }
    }
    else if ((end - start) == 4)
    {
        for (int a = start; a < end; a++)
        {
            if ((a == start) || (a == end - 1))
            {
                string checkChar = tokens[a];
                for (int k = 0; k < checkChar.size(); k++)
                {
                    if (((int(checkChar[k]) >= 65) && (int(checkChar[k]) <= 90)) || ((int(checkChar[k]) >= 97) && (int(checkChar[k] <= 122))))
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else if (a = 1)
            {
                if ((tokens[a] != "<") && (tokens[a] != ">") && (tokens[a] != "=") && (tokens[a] != "!"))
                {
                    return false;
                }
            }
            else
            {
                if (tokens[a] != "=")
                {
                    return false;
                }
            }
        }
    }

    return true;
}

string checkIfElseSyntax(int start, int end, vector<string> tokens, unordered_map<int, int> parenthesisMap)
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
                    int closeBracket = i + 5;
                    if (i < (end - 1))
                    {
                        auto it = parenthesisMap.find(i + 1);
                        //cout << "I--" << endl;
                        if (it->second)
                        {
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

                        if ((closeBracket + 1) < end - 1)
                        {
                            auto it = parenthesisMap.find(closeBracket + 1);
                            int closeParNum = it->second; //i+10

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
                                // code fix based on github issue - Uninitialized variable - start
                                // int closeQuotes;
                                int closeQuotes = 0;
                                // code fix based on github issue - Uninitialized variable - end
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
                                    if (tokens[j].substr(0, 1) == "&")
                                    {
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
                                if (it1 != newVarTypeMap.end()) //code fixed acc to issue:Invalid memory dereference #13
                                {
                                    string type = it1->second;
                                    //cout << "VII" << endl;
                                    cout << indent << " arg " << type << " " << key << endl;
                                }
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
    bool opFunction = checkFunction(tokens);                              // check function
    bool opColons = checksemicolon(tokens);                               //check Semicolon

    if (opParenthesis == false)
        cout << "Syntax error: Parenthesis Not Balanced" << endl;
    else if (opColons == false)
        cout << "Syntax error: Missing semi-colon in a statement." << endl;
    else if (opFunction == false)
        cout << "Please check the function definition properly." << endl;
    else
    {
        string ieVal = checkIfElseSyntax(0, tokens.size(), tokens, parenthesisMap);
        cout << "ieVal: " << ieVal << endl;
        unordered_map<string, string> varTypeMAp;
        /*cout << "\nParenthesis map : \n";
                                unordered_map<int, int>::iterator itr;
                                for (itr = parenthesisMap.begin(); itr != parenthesisMap.end(); itr++)
                                {

                                    cout << itr->first << "  " << itr->second << endl;
                                }
                                cout << "--------------" << endl;*/
        parseTree(0, tokens.size(), tokens, parenthesisMap, varTypeMAp, "-");
    }
}
