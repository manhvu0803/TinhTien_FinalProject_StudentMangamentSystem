#include "dataStructure.h"
#include <sstream>
#include <iostream>

using namespace std;

// Parse string to date struct
tt::date tt::parseToDate(string s)
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
