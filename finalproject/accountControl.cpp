#include "accountControl.h"
#include <fstream>
#include <iostream>
#include <conio.h>

typedef unordered_map<string, account> loginMap;

loginMap loginInfo;

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
    }
    while (c != '\r');          // read until enter char

    //cout << '\n' << password << '\n';

    return password;
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

void changePassword(account user)
{
    cout << "Please enter your old password";

}

void saveAccount()
{

}

bool loadLoginInfo(loginMap &loginInfo, const char *loginFileName = "login.dat")
{
    account user;
    ifstream loginFile;

    loginFile.open(loginFileName);

    if (!loginFile.is_open()) {
        cout << loginFileName << " not found";
        return false;
    }

    while (loginFile >> user.username >> user.type >> user.password)
        loginInfo.emplace(user.username, user);

    return true;
}

bool newAccount(loginMap &loginInfo)
{
    account newAcc;

    cout << "Please enter new username:\n";
    getline(cin, newAcc.username);

    if (loginInfo.find(newAcc.username) != loginInfo.end()) {
        cout << "Account already existed\n";
        return false;
    }

    cout << "Please enter new password:\n";
    getline(cin, newAcc.password);

    loginInfo.emplace(newAcc.username, newAcc);

    return true;
}

account login()
{
    string username, password;

    if (!loadLoginInfo(loginInfo))
        return {"", "", 0};

    do {
        cout << "Please enter your username:\n";
        getline(cin, username);
        if (loginInfo.find(username) != loginInfo.end())
            break;
        cout << "Account does not existed\n";
    }
    while (true);

    account currentAcc = loginInfo.at(username);

    cout << "Please enter your password:\n";
    do {
        //getline(cin, password);

        if (currentAcc.password.compare(passwordBuffer()) == 0)
            break;
        cout << "Wrong password\n";
        password = "";
    }
    while (true);

    return currentAcc;
}
