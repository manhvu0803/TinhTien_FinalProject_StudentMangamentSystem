#include <iostream>
#include <conio.h>
#include "accountControl.h"

using namespace std;

int main()
{
    cout << "Welcome to Tinh Tien's Student Management System\n";
    cout << "Please log out before closing the program\n\n";

    account user = login();

    int choice;

    while (user.type != 0) {
        cout << "Please choose an option:\n";
        cout << "Enter 1: View profile\n";
        cout << "Enter 2: Change password\n";
        cout << "Enter 3: Log out\n";

        cin >> choice;
        switch (choice) {
            case 1:
                showProfile(user);
                break;
            case 2:
                cin.ignore(256, '\n');
                changePassword(user);
                break;
            case 3:
                saveAccount();
                cout << "Logged out\n";
                cin.ignore(256, '\n');
                user = login();
                break;
            default:
                cout << "Invalid choice\n";
        }

        cout << "\n";
    }

    return 0;
}

