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
                    int l = intermediate.length();
                }
                if (intermediate.find("=") != std::string::npos)
                {
                    int c = intermediate.find("=");
                    indexes.push_back(c);
                    flag = false;
                }
                if (intermediate.find("+") != std::string::npos)
                {
                    int c = intermediate.find("+");
                    indexes.push_back(c);
                    flag = false;
                }
                if (intermediate.find("-") != std::string::npos)
                {
                    int c = intermediate.find("-");
                    indexes.push_back(c);
                    flag = false;
                }

                if (intermediate.find("/") != std::string::npos)
                {
                    int c = intermediate.find("/");
                    indexes.push_back(c);
                    flag = false;
                }
                if (intermediate.find(")") != std::string::npos)
                {
                    int c = intermediate.find(")");
                    indexes.push_back(c);
                    flag = false;
                }
                if (intermediate.find(",") != std::string::npos)
                {
                    int c = intermediate.find(",");
                    indexes.push_back(c);
                    flag = false;
                }
                if (intermediate.find(";") != std::string::npos)
                {
                    int c = intermediate.find(";");
                    indexes.push_back(c);
                    flag = false;
                }
                if (intermediate.find("{") != std::string::npos)
                {
                    int c = intermediate.find("{");
                    indexes.push_back(c);
                    flag = false;
                }
                if (intermediate.find("}") != std::string::npos)
                {
                    int c = intermediate.find("}");
                    indexes.push_back(c);
                    flag = false;
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
                        if (i == 0)
                        {
                            if (indexes[i] != 0)
                            {
                                tokens.push_back(intermediate.substr(0, indexes[i]));
                                string s;
                                s.push_back(intermediate.at(indexes[i]));
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
                                        tokens.push_back(s);
                                    }
                                    ////cout << "3 -- " << intermediate.substr((indexes[i] + 1), intermediate.size()) + "\n";
                                    tokens.push_back(intermediate.substr((indexes[i] + 1), intermediate.size()));
                                    ////cout << "4 -- " << intermediate.at(indexes[i]) << endl;
                                }
                            }
                        }
                        else if (i == (indexes.size() - 1))
                        {

                            string a = intermediate.substr((indexes[i - 1] + 1), indexes[i]);
                            string b = intermediate.substr((indexes[i] + 1), intermediate.size());
                            if ((indexes[i - 1] + 1) != indexes[i])
                            {
                                tokens.push_back(a);
                            }
                            string s;
                            s.push_back(intermediate.at(indexes[i]));
                            tokens.push_back(s);
                            if (b.size() != 0)
                                tokens.push_back(b);
                        }
                        else
                        {
                            tokens.push_back(intermediate.substr((indexes[i - 1] + 1), indexes[i]));
                            string s;
                            s.push_back(intermediate.at(indexes[i]));
                            tokens.push_back(s);
                        }
                    }
                }
            }
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