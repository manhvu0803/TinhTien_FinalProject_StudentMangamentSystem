#include "accountControl.h"
#include "dataStructure.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "lecturer.h"
#include "class.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <conio.h>
#endif // defined

using namespace std;
using namespace acc;

const char* cancelCmd = "exit";
const char* loginFileDir = "data/login.dat";

tt::vector<account> loginInfo;
//account nullAcc = {"", "", -1, -1};

void acc::saveToFile()
{
    ofstream loginFile(loginFileDir);
    for (size_t i = 0, lim = loginInfo.size(); i < lim; ++i) {
        loginFile << loginInfo[i].username << ' ' << loginInfo[i].type << ' ' << loginInfo[i].id << ' ';
        loginFile << loginInfo[i].password << '\n';
    }
    loginFile.close();
}

string acc::createUsername(string name)
{
    size_t pos1 = name.find(' ');
    size_t pos2 = name.find(' ', pos1 + 1);
    string username = "";

    username += (char)tolower(name[0]);
    if (pos1 == string::npos) return username + name.substr(1);

    username += (char)tolower(name[pos1 + 1]);
    if (pos2 == string::npos) return  username + name.substr(pos1 + 1);

    return username + (char)tolower(name[pos2 + 1]) + name.substr(pos2 + 2);
}

bool addAccount(account user)
{
    for (size_t i = 0, lim = loginInfo.size(); i < lim; ++i)
        if (user.id == loginInfo[i].id) {
            loginInfo[i] = user;
            saveToFile();
            return false;
        }
    loginInfo.push_back(user);
    saveToFile();
    return true;
}

bool acc::createAccount(const tt::lecturer& user)
{
    account newAcc;
    // Lecturer's username is also their ID
    newAcc.id = createUsername(user.fullName);
    newAcc.type = 2;
    newAcc.username = newAcc.id;

    // Lecturer default password is their degree + full name with no caps or space
    newAcc.password = "";
    string pass = user.degree + user.fullName;
    for (int i = 0, lim = pass.length(); i < lim; ++i)
        if (pass[i] != ' ') newAcc.password += tolower(pass[i]);

    return addAccount(newAcc);
}

bool acc::createAccount(const tt::student& user)
{
    account newAcc;
    newAcc.id = to_string(user.id);
    newAcc.type = 1;
    newAcc.username = createUsername(user.lastName + ' ' + user.firstName);

    // Student default password is their month->date->year of birth with leading 0 and no space
    stringstream ss;
    ss.fill('0');
    ss << setw(2) << user.DoB.m << setw(2) << user.DoB.d << setw(4) << user.DoB.y;
    ss >> newAcc.password;

    return addAccount(newAcc);
}

bool acc::removeAccount(string id)
{
    for (size_t i = 0, lim = loginInfo.size(); i < lim; ++i)
        if (id == loginInfo[i].id) {
            loginInfo.erase(i);
            acc::saveToFile();
            return true;
        }
    return false;
}

/*
bool acc::newAccount()
{
    account newAcc;

    cout << "Please enter new username (enter \"" << cancelCmd << "\" to exit):\n";
    getline(cin, newAcc.username);

    cout << "Please enter new password (enter \"" << cancelCmd << "\" to exit):\n";
    getline(cin, newAcc.password);

    return true;
}
*/

account* getAccount(string username)
{
    for (size_t i = 0, lim = loginInfo.size(); i < lim; ++i)
        if (username == loginInfo[i].username) return &loginInfo[i];
    return nullptr;
}


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    string passwordBuffer()
    {
        char c;
        string password;

        do {
            c = _getch();
            if (c == '\b' && password.length() > 0) {
                cout << "\b \b";    // back 1 char, write a space to override that char, and back 1 char
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

        return password;
}
#else
    string passwordBuffer()
    {
        string s;
        getline(cin, s);
        return s;
    }
#endif // defined

bool passwordCheck(string password, const char* type = "")
{
    string input;
    do {
        cout << "Please enter your " << type << "password (enter \"" << cancelCmd << "\" to return):\n";
        input = passwordBuffer();
        if (input == cancelCmd) return false;
        if (input == password) return true;
        cout << "Wrong password\n\n";
    }
    while (true);
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

account* acc::login()
{
    string username, password;

    if (!loadLoginFile())
        return nullptr;

    account* currentAcc = nullptr;

    do {
        cout << "Please enter your username (enter \"" << cancelCmd << "\" to exit):\n";
        getline(cin, username);
        if (username == cancelCmd) return nullptr;
        currentAcc = getAccount(username);
        if (currentAcc) {
            if (passwordCheck(currentAcc->password)) break;
            else continue;
        }
        cout << "Account does not existed\n\n";
    }
    while (!currentAcc);

    return currentAcc;
}

void acc::changePassword(account* user)
{
    cout << "\nChange password\n";

    if (!passwordCheck(user->password, "old ")) return;

    string input;
    do {
        cout << "Please enter your new password (at least 8 character):\n";
        input = passwordBuffer();
        if (input.length() >= 8) break;
        cout << "Your password is too short\n";
    }
    while (true);

    user->password = input;
    saveToFile();

    cout << "Password changed successfully\n";
}

void acc::showProfile(account user)
{
    cout << "Username: " << user.username << "\nAccount type: ";
    switch (user.type) {
        case 1: {
            cout << "student\n";
            clss cl;
            tt::student st = cl.getStudent(stoi(user.id));
            cout << "ID: " << st.id << '\n';
            cout << "Class: " << st.cls << '\n';
            cout << "Name: " << st.lastName + ' ' + st.firstName << '\n';
            cout << "Gender: " << ((st.gender == 'M') ? "Male\n" : "Female\n");
            cout << "Date of birth: " << st.DoB.y << '-' << st.DoB.m << '-' << st.DoB.d << '\n';
            break;
        }
        case 2: {
            cout << "lecturer\n";
            ltr lt;
            tt::lecturer l = lt.get(user.id);
            cout << "Name: " << l.fullName << '\n';
            cout << "Degree: " << l.degree << '\n';
            cout << "Gender: " << ((l.gender == 'M') ? "Male\n" : "Female\n");
            break;
        }
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
