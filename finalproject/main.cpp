#include <iostream>
#include <conio.h>
#include "accountControl.h"

using namespace std;

int main()
{
    cout << "Welcome to Tinh Tien's Student Management System\nPlease log out before closing the program";

    account user = login();
    if (user.type == 0)
        return 0;

    do {
        cout << "Please choose an option:\n";
        cout << "Press 1: View profile\n";
        cout << "Press 2: Change password\n";
        cout << "Press 3: Log out\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                showProfile(user);
                break;
            case 2:
                changePassword(user);
                break;
            case 3:
                saveAccount();
                cout << "Logged out\n";
                user = login();
                break;
            default:
                cout << "Invalid choice\n";
                _getch();
        }

        if (choice == 4)
            break;
    }
    while (true);

    return 0;
}

