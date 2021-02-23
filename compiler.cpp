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
                    //cout << endl ;
                    /*cout << "indexes: " << endl;
                    for (int i = 0; i < indexes.size(); i++)
                        cout << indexes[i] << ",";
                    cout << endl;   */
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
                    cout << endl ;
                    cout << "intermediate: " << intermediate << endl ;
                    string subintermediate = intermediate.substr(c + 1, intermediate.size());
                    cout << "subintermediate: " << subintermediate << " -- char: " << intermediate.at(c) << endl ;
                    while (subintermediate.find("\"") != std::string::npos)
                    {
                        int s = subintermediate.find("\"");
                        indexes.push_back(c + 1 + s);
                        subintermediate = subintermediate.substr(s + 1, intermediate.size());
                    }
                    //cout << endl ;
                    cout << "indexes: " << endl;
                    for (int i = 0; i < indexes.size(); i++)
                        cout << indexes[i] << ",";
                    cout << endl;   
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
                        cout << "Inside for loop" << endl;
                        //cout << "intermediate: " << intermediate << endl;
                        cout << "i: " << i << ", indexes[i]: " << indexes[i] << endl;

                        if (i == 0)
                        {
                            if (indexes[i] != 0)
                            {
                                int len = indexes[i];
                                tokens.push_back(intermediate.substr(0, len));
                                //tokens.push_back(intermediate.substr(0, indexes[i]));
                                string s;
                                s.push_back(intermediate.at(indexes[i]));
                                if(s.size()!=0)
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
                                        if(s.size()!=0)
                                            tokens.push_back(s);
                                    }
                                    int len = intermediate.size() - indexes[i];
                                    string inp = intermediate.substr((indexes[i] + 1), len);
                                    if(inp.size()!=0)
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
                            cout << "a: " << a << ", b: " << b << endl;
                            if ((indexes[i - 1] + 1) != indexes[i])
                            {   
                                if(a.size()!=0)
                                    tokens.push_back(a);
                            }
                            string s;
                            s.push_back(intermediate.at(indexes[i]));
                            if(s.size()!=0)
                                tokens.push_back(s);
                            if (b.size() != 0)
                                tokens.push_back(b);
                        }
                        else
                        {
                            int len = indexes[i] - (indexes[i - 1] + 1);
                            string b = intermediate.substr((indexes[i-1] + 1), len);
                            cout << "in else, b: " << b << endl;
                            if(b.size()!=0)
                                tokens.push_back(b);
                            //tokens.push_back(intermediate.substr((indexes[i - 1] + 1), indexes[i]));
                            string s;
                            s.push_back(intermediate.at(indexes[i]));
                            if(s.size()!=0)
                                tokens.push_back(s);
                        }
                    }
                }
            }
            tokens.push_back("EndOfLine");
        }
        cout << "\n----- AFTER TOKENIZING(TOKENS): -----\n\n";
        for (int i = 0; i < tokens.size(); i++)
            cout << tokens[i] << '\n';
        newfile.close(); //close the file object.
    }
    else
    {
        cout << "File not found!" << endl;
    }

    return 0;
}