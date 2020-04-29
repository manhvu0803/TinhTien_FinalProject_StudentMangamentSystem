#ifndef ACCOUNTCONTROL_H_INCLUDED
#define ACCOUNTCONTROL_H_INCLUDED

#include <string>
#include "utility.h"

using namespace std;

struct account
{
    string username;
    string password;
    string id;
    int type; // 1 is student, 2 is lecturer, 3 is academic staff
};

account* login();

void showProfile(account user);

void changePassword(account* user);

void saveToFile();

#endif // ACCOUNTCONTROL_H_INCLUDED
