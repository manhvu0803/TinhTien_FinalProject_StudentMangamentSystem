#include <iostream>
#include <limits>
#include "accountControl.h"
#include "class.h"

using namespace std;

int main()
{
    cout << "Welcome to Tinh Tien's Student Management System\n";
    cout << "Please log out before closing the program\n\n";

    acc::account* user = acc::login();

    int choice;
    while (user) {
        cout << "Please choose an option:\n";
        cout << "Enter 1: View profile\n";
        cout << "Enter 2: Change password\n";
        if (user->type > 2) cout << "Enter 3: Class features\n";
        cout << "Enter 0: Log out\n\n";

        cout << "Your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            choice = -1;
        }
        switch (choice) {
            case 0:
                acc::saveToFile();
                cout << "Logged out successfully\n\n";
                cin.ignore(256, '\n');
                user = acc::login();
                break;
            case 1:
                acc::showProfile(*user);
                cout << "\nPress Enter to continue...\n";
                cin.get();
                cin.clear();
                cin.ignore(numeric_limits<int>::max(), '\n');
                break;
            case 2:
                cin.ignore(256, '\n');
                acc::changePassword(user);
                break;
            case 3: {
                cout << '\n';
                if (user->type < 3) {
                    cout << "Invalid choice\n";
                    break;
                }
                clss cl;
                cl.menu();
                break;
            }
            default:
                cout << "\nInvalid choice\n";
        }
        cout << "\n";
    }

    delete user;

    return 0;
}

