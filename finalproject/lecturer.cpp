#include "lecturer.h"
#include "dataStructure.h"
#include <iostream>
#include <iomanip>

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

int ltr::position(tt::lecturer user)
{
    for (int i = 0, lim = ltrs.size(); i < lim; ++i)
        if (user.username == ltrs[i].username) return i;
    return -1;
}

void ltr::input(tt::lecturer newLtr)
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

void ltr::add(tt::lecturer user)
{
    ltrs.push_back(user);
    saveToFile();
}

void ltr::replace(tt::lecturer user, int pos)
{
    ltrs[pos] = user;
    saveToFile();
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
                cout << "\nAdd a lecturer\n";
                cout << "Name: ";
                cin.ignore(1024, '\n');
                getline(cin , newLtr.fullName);
                if (position(newLtr) > -1) cout << "Lecturer has already exist";
                else {
                    input(newLtr);
                    add(newLtr);
                    cout << "Added successfully";
                }
                break;
            }
            case 3:
                break;
            case 4:
                showAll();
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice\n";
        }

        cout << "\nPress enter to continue...";
        if (choice != 0) getchar();
    }
    while (choice != 0);
}
