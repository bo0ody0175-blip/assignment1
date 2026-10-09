#pragma once
#include <iostream>
using namespace std;

class Utility
{
public :
    static string readString(const string message)
    {
        string s = "";
        cout << message << endl;
        cin >> s;
        return s;
    }

    static int readNumber(const int from, const int to, const string message)
    {
        int x = 0;
        cout << message << endl;
        cin >> x;
        if (x < from || x > to)
        {
            cout << "Invalid Number!";
            x = -1;
        }
        return x;

    }

    static char readChar(const string message)
    {
        char ch = ' ';
        cout << message << endl;
        cin >> ch;
        return ch;
    }


};

