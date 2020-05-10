#include "dataStructure.h"
#include <sstream>
#include <iostream>

using namespace std;

// Check is date valid. Return -1 if month is invalid, -2 if day is invalid, 1 otherwise
int tt::checkDate(const tt::date& d)
{
    int dom[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (d.y % 400 == 0 || (d.y % 4 == 0 && d.y % 100 != 0)) dom[2] = 29;

    if (d.m > 12 || d.m < 1) return -1;
    if (d.d < 1 || d.d > dom[d.m]) return -2;
    return 1;
}

// Parse string to date struct
tt::date tt::stringToDate(const string& str)
{
    tt::date d;
    stringstream ss(str);
    string s;

    if (str.find('-') != string::npos) {
        try {
            getline(ss, s, '-');
            d.y = stoi(s);
            getline(ss, s, '-');
            d.m = stoi(s);
            getline(ss, s, '-');
            d.d = stoi(s);
        }
        catch (...) {
            cout << "Invalid date format\n";
        }
        return d;
    }
    else if (str.find('/') != string::npos) {
        try {
            getline(ss, s, '/');
            d.m = stoi(s);
            getline(ss, s, '/');
            d.d = stoi(s);
            getline(ss, s, '/');
            d.y = stoi(s);
        }
        catch (...) {
            cout << "Invalid date format\n";
        }
        return d;
    }

    return d;
}
