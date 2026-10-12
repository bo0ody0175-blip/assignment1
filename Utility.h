#pragma once
#include <iostream>
using namespace std;

class Utility
{
public :

    Utility() = delete;

    static string readString(const string message)
    {
        string s = "";
        cout << message << endl;
        getline(cin, s);
        return s;
    }

    static int readNumber(const int from, const int to, const string message)
    {
        int x = 0;
        cout << message << endl;
        cin >> x;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (x < from || x > to)
        {
            cout << "Invalid Number!";
            x = -1;
        }
        return x;

    }

    static int readNumber(const string message)
    {
        int x = 0;
        cout << message << endl;
        cin >> x;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return x;
    }

    static char readChar(const string message)
    {
        char ch = ' ';
        cout << message << endl;
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return ch;
    }

    template <typename T>
    static bool equals(T first, T second) { return first == second; }


};

