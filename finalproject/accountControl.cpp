#include "accountControl.h"
#include <fstream>
#include <iostream>
#include <conio.h>

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

int login()
{
    string username, password;
    loginMap loginInfo;

    if (!loadLoginInfo(loginInfo))
        return 0;

    do {
        cout << "Please enter your username:\n";
        getline(cin, username);
        if (loginInfo.find(username) != loginInfo.end())
            break;
        cout << "Account does not existed\n";
    }
    while (true);

    account currentAcc = loginInfo.at(username);

    do {
        cout << "Please enter your password:\n";

        //getline(cin, password);

        char c;
        do {
            c = _getch();
            if (c != '\r') {
                cout << "*";
                password += c;
            }
        }
        while (c != '\r');

        if (password.compare(password) == 0)
            break;
        cout << "Wrong password";
    }
    while (true);

    return currentAcc.type;
}
