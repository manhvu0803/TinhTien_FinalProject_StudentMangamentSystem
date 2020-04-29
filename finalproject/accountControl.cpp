#include "accountControl.h"
#include <fstream>
#include <iostream>
#include <iomanip>
//#include <conio.h>

const char* cancelCmd = "exit";
const char* loginFileDir = "data/login.dat";

tt::vector<account> loginInfo;
//account nullAcc = {"", "", -1, -1};

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
    cout << "\nProfile\n" "Username: " << user.username << "\nAccount type: ";
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

void saveToFile()
{
    ofstream loginFile(loginFileDir);
    for (size_t i = 0, lim = loginInfo.size(); i < lim; ++i) {
        loginFile << loginInfo[i].username << ' ' << loginInfo[i].type << ' ' << loginInfo[i].id << ' ';
        loginFile << loginInfo[i].password << '\n';
    }
    loginFile.close();
}

void changePassword(account* user)
{
    string password;

    cout << "\nChange password\n";
    do {
        cout << "Please enter your old password (enter \"" << cancelCmd << "\" to return):\n";
        password = passwordBuffer();
        if (password.compare(cancelCmd) == 0) return;
        if (password.compare(user->password) == 0) break;
        cout << "Wrong password\n";
    }
    while (true);

    do {
        cout << "Please enter your new password (at least 8 character):\n";
        password = passwordBuffer();
        if (password.length() >= 8) break;
        cout << "Your password is too short\n";
    }
    while (true);

    user->password = password;
    saveToFile();
    cout << "Password changed successfully\n";
}

bool loadLoginFile()
{
    account user;
    ifstream loginFile;

    loginFile.open(loginFileDir);
    if (!loginFile.is_open()) {
        cout << loginFileDir << " not found";
        return false;
    }
    while (loginFile >> user.username >> user.type >> user.id >> user.password)
        loginInfo.push_back(user);
    loginFile.close();

    return true;
}

bool createAccount(student user)
{
    account newAcc;
    newAcc.id = user.id;
    newAcc.type = 1;

    // Generate username
    newAcc.username = user.lastName[0];
    size_t pos = user.lastName.find(' ');
    if (pos != string::npos) newAcc.username += user.lastName[pos + 1];
    newAcc.username += user.firstName[0];

    // Generate password
    stringstream ss;
    ss.fill('0');
    ss << setw(2) << user.DoB.m << setw(2) << user.DoB.d << setw(4) << user.DoB.y;
    ss >> newAcc.password;

    // Check existing accounts
    pos = -1;
    for (size_t i = 0, lim = loginInfo.size(); i < lim; ++i)
        if (to_string(user.id).compare(loginInfo[i].id) == 0) {
            pos = i;
            break;
        }

    if (pos < 0) loginInfo.push_back(newAcc);
    else loginInfo[pos] = newAcc;
    saveToFile();
    return true;
}

bool newAccount(account& user)
{
    account newAcc;

    cout << "Please enter new username (enter \"" << cancelCmd << "\" to exit):\n";
    getline(cin, newAcc.username);

    if (user.username.compare(newAcc.username) == 0) {
        cout << "Account already existed\n";
        return false;
    }

    cout << "Please enter new password (enter \"" << cancelCmd << "\" to exit):\n";
    getline(cin, newAcc.password);

    return true;
}

account* getAccount(string username)
{
    for (size_t i = 0, lim = loginInfo.size(); i < lim; ++i)
        if (username.compare(loginInfo[i].username) == 0) return &loginInfo[i];

    return nullptr;
}

account* login()
{
    string username, password;

    if (!loadLoginFile())
        return nullptr;

    account* currentAcc = nullptr;

    cout << "Please enter your username (enter \"" << cancelCmd << "\" to exit):\n";
    do {
        getline(cin, username);
        if (username.compare(cancelCmd) == 0) return nullptr;
        currentAcc = getAccount(username);
        if (currentAcc) break;
        cout << "Account does not existed\n";
    }
    while (!currentAcc);

    cout << "Please enter your password (enter \"" << cancelCmd << "\" to exit):\n";
    do {
        password = passwordBuffer();
        if (password.compare(cancelCmd) == 0) return nullptr;
        if (password.compare(currentAcc->password) == 0) break;
        cout << "Wrong password\n";
    }
    while (true);

    return currentAcc;
}
