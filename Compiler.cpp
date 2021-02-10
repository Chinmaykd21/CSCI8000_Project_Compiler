#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
using namespace std;
int main()
{

  fstream newfile;
  vector<string> tokens;

  newfile.open("C:/Users/deost/OneDrive - University of Georgia/UGA/Adv Topics in CSCI/Project/C++/Files/demo.cpp", ios::in);

  if (newfile.is_open())
  { //checking whether the file is open
    string tp;
    while (getline(newfile, tp))
    {                                   //read data from file object and put it into string.
      cout << "\n\ntp: " << tp << "\n"; //print the data of the string
      stringstream check1(tp);
      string intermediate;
      while (getline(check1, intermediate, ' '))
      {
        vector<int> indexes;
        bool flag = true;
        cout << "\nintermediate: " << intermediate << "\n";
        if (intermediate.find("(") != std::string::npos)
        {
          int c = intermediate.find("(");
          indexes.push_back(c);
          flag = false;
          cout << "here (, pos: " << c << endl;
          int l = intermediate.length();
          //cout << intermediate.substr(0, c) << endl;
          //cout << intermediate.substr(c + 1, l) << endl;
        }
        if (intermediate.find("=") != std::string::npos)
        {
          int c = intermediate.find("=");
          cout << "here =, pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        if (intermediate.find("+") != std::string::npos)
        {
          int c = intermediate.find("+");
          cout << "here +, pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        if (intermediate.find("-") != std::string::npos)
        {
          int c = intermediate.find("-");
          cout << "here -, pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        if (intermediate.find("*") != std::string::npos)
        {
          int c = intermediate.find("*");
          cout << "here *, pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        if (intermediate.find("/") != std::string::npos)
        {
          int c = intermediate.find("/");
          cout << "here /, pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        if (intermediate.find(")") != std::string::npos)
        {
          int c = intermediate.find(")");
          cout << "here ), pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        if (intermediate.find(",") != std::string::npos)
        {
          int c = intermediate.find(",");
          cout << "here , , pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        if (intermediate.find(";") != std::string::npos)
        {
          int c = intermediate.find(";");
          cout << "here ; , pos: " << c << endl;
          indexes.push_back(c);
          flag = false;
        }
        cout << "indexes: \n";
        for (int i = 0; i < indexes.size(); i++)
        {
          cout << indexes[i];
        }
        cout << "\n";
        if (flag == true)
        {
          cout << "Size of intermediate: " << intermediate.size() << endl;
          if (intermediate.size() > 0)
          {
            cout << "no special char !" << intermediate << "!\n";
            tokens.push_back(intermediate);
          }
        }
        else
        {
          cout << "Special char found \n";
          sort(indexes.begin(), indexes.end());
          for (int i = 0; i < indexes.size(); i++)
          {
            if (i == 0)
            {
              if (indexes[i] != 0)
              {
                cout << "1if, i=" << i << ", " << intermediate.substr(0, indexes[0]) + "\n";
                tokens.push_back(intermediate.substr(0, indexes[i]));
                cout << "hereeee 1if " << intermediate.at(indexes[i]) << endl;
                string s;
                s.push_back(intermediate.at(indexes[i]));
                tokens.push_back(s);
              }
              if (indexes.size() == 1)
              {
                if (indexes[i] != (intermediate.size() - 1))
                {
                  cout << "i=" << i << ", " << intermediate.substr((indexes[i] + 1), intermediate.size()) + "\n";
                  tokens.push_back(intermediate.substr((indexes[i] + 1), intermediate.size()));
                  cout << "hereeee 2if " << intermediate.at(indexes[i]) << endl;
                }
              }
            }
            else if (i == (indexes.size() - 1))
            {
              string a = intermediate.substr((indexes[i - 1] + 1), indexes[i]);
              string b = intermediate.substr((indexes[i] + 1), intermediate.size());
              cout << "2if, i=" << i << ", " << a << " , " << b << "!\n";
              tokens.push_back(a);
              cout << "hereeee 3if " << intermediate.at(indexes[i]) << endl;

              string s;
              s.push_back(intermediate.at(indexes[i]));
              tokens.push_back(s);
              if (b.size() != 0)
                tokens.push_back(b);
            }
            else
            {
              cout << "3else, i=" << i << ", " << intermediate.substr((indexes[i - 1] + 1), indexes[i]);
              tokens.push_back(intermediate.substr((indexes[i - 1] + 1), indexes[i]));
              cout << "hereeee 1if " << intermediate.at(indexes[i]) << endl;

              string s;
              s.push_back(intermediate.at(indexes[i]));
              tokens.push_back(s);
            }
          }
        }
        cout << "Tokens: ";
        for (int i = 0; i < tokens.size(); i++)
          cout << tokens[i] << "--";

        cout << "\n\n";
      }
    }
    cout << "\n----- AFTER TOKENIZING(TOKENS): -----\n\n";
    for (int i = 0; i < tokens.size(); i++)
      cout << tokens[i] << '\n';
    newfile.close(); //close the file object.
  }

  /*string first_name,last_name;
    cout<<"Enter your first name: ";
    cin>>first_name;
    cout<<"Enter your last name: ";
    cin>>last_name;
    cout<<"Your full name is: "<<first_name+" "+last_name;*/

  return 0;
}