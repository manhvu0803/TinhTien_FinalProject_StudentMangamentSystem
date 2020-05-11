#include "dataStructure.h"
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

tt::date tt::currentDate()
{
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm* d = localtime(&now);
    return {d->tm_mday, d->tm_mon + 1, d->tm_year + 1900};
}

tt::time tt::currentTime()
{
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm* d = localtime(&now);
    return {d->tm_hour, d->tm_min, d->tm_sec};
}

// Return -1 if month is invalid, -2 if day is invalid, 1 if valid past date, 2 if valid future date
int tt::checkDate(const tt::date& dt)
{
    int dom[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt.y % 400 == 0 || (dt.y % 4 == 0 && dt.y % 100 != 0)) dom[2] = 29;

    if (dt.m > 12 || dt.m < 1) return -1;
    if (dt.d < 1 || dt.d > dom[dt.m]) return -2;

    date now = currentDate();
    if (dt.y > now.y) return 2;
    else if (dt.y < now.y) return 1;
    if (dt.m > now.m) return 2;
    else if (dt.m < now.m) return 1;
    if (dt.d > now.d) return 2;
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
