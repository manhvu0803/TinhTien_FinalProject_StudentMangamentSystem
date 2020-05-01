#ifndef ACCOUNTCONTROL_H_INCLUDED
#define ACCOUNTCONTROL_H_INCLUDED

#include <string>
#include "dataStructure.h"
#include "utility.h"

using namespace std;

struct account
{
    string username;
    string password;
    string id;
    int type; // 1 is student, 2 is lecturer, 3 is academic staff
};

void saveToFile();

bool createAccount(lecturer& user);
bool createAccount(student user);

account* login();

void changePassword(account* user);

void showProfile(account user);

#endif // ACCOUNTCONTROL_H_INCLUDED
