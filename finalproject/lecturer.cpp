#include "lecturer.h"
#include "dataStructure.h"
#include <iostream>
#include "accountControl.h"
#include <iomanip>
#include <fstream>

using namespace std;

const char* ltr::ltrFile = "data/lecturer.dat";

ltr::ltr()
{
    ifstream file(ltrFile);
    tt::lecturer newLtr;
    while (getline(file, newLtr.username)) {
        getline(file, newLtr.fullName);
        getline(file, newLtr.degree);
        file >> newLtr.gender;
        ltrs.push_back(newLtr);
        file.ignore(1024, '\n');
    }
    file.close();
}

ltr::~ltr()
{
}

void ltr::saveToFile()
{
    ofstream file(ltrFile);
    for (int i = 0, lim = ltrs.size(); i < lim; ++i) {
        file << ltrs[i].username << '\n' << ltrs[i].fullName << '\n';
        file << ltrs[i].degree << '\n' << ltrs[i].gender << '\n';
    }
    file.close();
}

int ltr::position(const string& username)
{
    for (int i = 0, lim = ltrs.size(); i < lim; ++i)
        if (username == ltrs[i].username) return i;
    return -1;
}

void ltr::input(tt::lecturer& newLtr)
{
    cout << "Degree: ";
    getline(cin, newLtr.degree);
    do {
        cout << "Gender (F/M): ";
        bool valid = tt::cinIg(cin, newLtr.gender);
        newLtr.gender = toupper(newLtr.gender);
        if ((newLtr.gender == 'F' || newLtr.gender == 'M') && valid) break;
        cout << "Invalid input\n";
    }
    while (true);
}

bool ltr::add(const tt::lecturer& user)
{
    if (position(user.username) > -1) return false;
    ltrs.push_back(user);
    acc::createAccount(user);
    saveToFile();
    return true;
}

bool ltr::replace(const string& username, const tt::lecturer& user)
{
    int pos = position(username);
    if (pos < 0) return false;
    ltrs[pos] = user;
    saveToFile();
    return true;
}

bool ltr::remove(const string& username)
{
    int pos = position(username);
    if (pos < 0) return false;
    ltrs.erase(pos);
    saveToFile();
    return true;
}

void ltr::showAll()
{
    cout << "Username      |  Name                            | Degree           | Gender\n";
    for (int i = 0, lim = ltrs.size(); i < lim; ++i) {
        cout << left << setw(14) << ltrs[i].username;
        cout << "| " << setw(33) << ltrs[i].fullName;
        cout << "| " << setw(17) << ltrs[i].degree;
        cout << "| " << ((ltrs[i].gender == 'M') ? "Male" : "Female") << '\n';
    }
}

void ltr::menu()
{
    int choice;
    do {
        cout << "Please choose an option:\n";
        cout << "Enter 1: Add a lecturer\n";
        cout << "Enter 2: Update a lecturer\n";
        cout << "Enter 3: Remove a lecturer\n";
        cout << "Enter 4: View all lecturer\n";
        cout << "Enter 0: Exit\n";

        cout << "Your choice: ";
        if (!tt::cinIg(cin, choice)) choice = -1;
        if (choice < -1 || choice > 4);

        switch (choice) {
            case 0:
                break;
            case 1: {
                tt::lecturer newLtr;
                cout << "Add a lecturer\n";
                cout << "Lecturer full name: ";
                getline(cin , newLtr.fullName);
                newLtr.username = acc::createUsername(newLtr.fullName);
                if (position(newLtr.username) > -1) cout << "Lecturer has already existed";
                else {
                    input(newLtr);
                    add(newLtr);
                    cout << "Added successfully";
                }
                break;
            }
            case 2: {
                string username;
                cout << "Edit a lecturer\n";
                cout << "Lecturer username: ";
                getline(cin , username);
                int pos = position(username);
                if (pos < 0) cout << "Lecturer doesn't exist";
                else {
                    tt::lecturer newLtr;
                    cout << "Full name: ";
                    getline(cin , newLtr.fullName);
                    newLtr.username = acc::createUsername(newLtr.fullName);
                    int pos2 = position(newLtr.username);
                    if (pos2 == pos) {
                        input(newLtr);
                        replace(username, newLtr);
                        cout << "Updated successfully";
                    }
                    else cout << "Username " << newLtr.username << " conflict with another lecturer";
                }
                break;
            }
            case 3: {
                string username;
                cout << "Remove a lecturer\n";
                cout << "Username: ";
                getline(cin , username);
                if (remove(username)) cout << "Removed successfully";
                else cout << "Lecturer doesn't exist";
                break;
            }
            case 4:
                showAll();
                break;
            default:
                cout << "Invalid choice\n";
        }

        cout << "\nPress enter to continue...";
        if (choice != 0) getchar();
    }
    while (choice != 0);
}
