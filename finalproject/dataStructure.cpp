#include "dataStructure.h"
#include <sstream>
#include <iostream>

using namespace std;

int tt::checkDate(tt::date d)
{
    if (d.m > 12 || d.m < 1)
        return -1;
    int dom[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (d.y % 400 == 0 || (d.y % 4 == 0 && d.y % 100 != 0)) dom[2] = 29;
    if (d.d < 1 || d.d > dom[d.m]) return -2;
    return 1;
}

// Parse string to date struct
tt::date tt::stringToDate(string s)
{
    tt::date d = {-1, -1, -1};
    if (s.find('-') != string::npos) {
        try {
            stringstream ss(s);
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

    if (s.find('/') != string::npos) {
        try {
            stringstream ss(s);
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
