#ifndef ACCOUNTCONTROL_H_INCLUDED
#define ACCOUNTCONTROL_H_INCLUDED

#include <unordered_map>
#include <string>

using namespace std;

struct account
{
    string username;
    string password;
    int type; // 1 is student, 2 is lecturer, 3 is academic staff
};

account login();

void showProfile(account user);

void changePassword(account &user);

void saveAccount();

void mapThing();

#endif // ACCOUNTCONTROL_H_INCLUDED
