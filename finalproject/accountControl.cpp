#include "accountControl.h"
#include <fstream>
#include <iostream>
//#include <conio.h>

typedef unordered_map<string, account> loginMap;

const char *cancelCmd = "exit";
const char *loginFileDir = "data/login.dat";

loginMap loginInfo;

/* For Windows only
string passwordBuffer()
{
    char c;
    string password;

    do {
        c = _getch();
        if (c == '\b' && password.length() > 0) {           // '\b' is backspace char
            cout << "\b \b";                                // back 1 char, write a space to override that char, and back 1 char
            password.erase(password.length() - 1, 1);
        }
        else if (c != '\r' && c != '\0' && c != '\b') {
            cout << '*';
            password += c;
        }
        else if (c == '\r')
            cout << '\n';
    }
    while (c != '\r');          // read until enter char

    //cout << '\n' << password << '\n';

    return password;
}*/

// For any OS
string passwordBuffer()
{
    string s;
    getline(cin, s);

    return s;
}

void showProfile(account user)
{
    cout << "Username: " << user.username << "\nAccount type: ";
    switch (user.type) {
        case 1:
            cout << "student\n";
            break;
        case 2:
            cout << "lecturer\n";
            break;
        case 3:
            cout << "academic staff\n";
            break;
        case 4:
            cout << "admin\n";
            break;
        default:
            cout << "false account\n";
    }
}

void saveAccount()
{
    ofstream loginFile(loginFileDir);

    for (auto &x: loginInfo) {
        account user = x.second;
        loginFile << user.username << " " << user.type << " " << user.password << "\n";
    }

    loginFile.close();
}

void mapThing()
{
    for (auto &x: loginInfo) {
        cout << x.first << " " << loginInfo.bucket(x.first) << "\n";
    }
}

void changePassword(account &user)
{
    string password;

    do {
        cout << "Please enter your old password (enter \"" << cancelCmd << "\" to exit):\n";
        password = passwordBuffer();
        if (password.compare(cancelCmd) == 0)
            return;
        if (password.compare(user.password) == 0)
            break;
        cout << "Wrong password\n";
    }
    while (true);

    do {
        cout << "Please enter your new password (at least 8 character):\n";
        password = passwordBuffer();

        if (password.length() < 8)
            cout << "Your password is too short\n";
    }
    while (password.length() < 8);

    user.password = password;

    loginInfo.at(user.username) = user;

    cout << "Password changed successfully\n";
}

bool loadLoginFile(loginMap &loginInfo)
{
    account user;
    ifstream loginFile;

    loginFile.open(loginFileDir);

    if (!loginFile.is_open()) {
        cout << loginFileDir << " not found";
        return false;
    }

    while (loginFile >> user.username >> user.type >> user.password)
        loginInfo.emplace(user.username, user);

    loginFile.close();

    return true;
}

bool newAccount(loginMap &loginInfo)
{
    account newAcc;

    cout << "Please enter new username (enter \"" << cancelCmd << "\" to exit):\n";
    getline(cin, newAcc.username);

    if (loginInfo.find(newAcc.username) != loginInfo.end()) {
        cout << "Account already existed\n";
        return false;
    }

    cout << "Please enter new password (enter \"" << cancelCmd << "\" to exit):\n";
    getline(cin, newAcc.password);

    loginInfo.emplace(newAcc.username, newAcc);

    return true;
}

account login()
{
    string username, password;

    if (!loadLoginFile(loginInfo))
        return {"", "", 0};

    do {
        cout << "Please enter your username (enter \"" << cancelCmd << "\" to exit):\n";
        getline(cin, username);
        if (username.compare(cancelCmd) == 0)
            return {"", "", 0};
        if (loginInfo.find(username) != loginInfo.end())
            break;
        cout << "Account does not existed\n";
    }
    while (true);

    account currentAcc = loginInfo.at(username);

    cout << "Please enter your password (enter \"" << cancelCmd << "\" to exit):\n";
    do {
        password = passwordBuffer();
        if (password.compare(cancelCmd) == 0)
            return {"", "", 0};
        if (currentAcc.password.compare(password) == 0)
            break;
        cout << "Wrong password\n";
    }
    while (true);

    return currentAcc;
}
