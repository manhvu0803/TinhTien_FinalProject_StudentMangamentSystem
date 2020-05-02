#include <iostream>
#include <limits>
#include "accountControl.h"

using namespace std;

int main()
{
    cout << "Welcome to Tinh Tien's Student Management System\n";
    cout << "Please log out before closing the program\n\n";

    account* user = login();

    int choice;
    while (user) {
        cout << "Please choose an option:\n";
        cout << "Enter 1: View profile\n";
        cout << "Enter 2: Change password\n";
        cout << "Enter 3: Log out\n";

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            choice = -1;
        }
        switch (choice) {
            case 1:
                showProfile(*user);
                break;
            case 2:
                cin.ignore(256, '\n');
                changePassword(user);
                break;
            case 3:
                saveToFile();
                cout << "Logged out\n\n";
                cin.ignore(256, '\n');
                user = login();
                break;
            default:
                cout << "\nInvalid choice\n";
        }

        cout << "\n";
    }

    delete user;

    return 0;
}

