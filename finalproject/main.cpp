#include <iostream>
#include <limits>
#include "accountControl.h"
#include "class.h"
#include "academicYear.h"

using namespace std;

int main()
{
    acc::account* user = acc::login();

    int choice;
    while (user) {
        tt::clearConsole();
        cout << "Welcome to Tinh Tien's Student Management System\n";
        cout << "Please log out before closing the program\n\n";
        cout << "Please choose an option:\n";
        cout << "Enter 1: View profile\n";
        cout << "Enter 2: Change password\n";
        if (user->type == 1) {
            cout << "Enter 3: Check in\n";
            cout << "Enter 4: View schedule\n";
            cout << "Enter 5: View score\n";
        }
        else if (user->type > 1) {
            cout << "Enter 3: Course menu\n";
            cout << "Enter 4: Attendance menu\n";
            if (user->type > 2) {
                cout << "Enter 5: Class menu\n";
                cout << "Enter 6: Score menu\n";
            }
        }
        cout << "Enter 0: Log out\n\n";

        cout << "Your choice: ";
        if (!tt::cinIg(cin, choice)) choice = -1;

        tt::clearConsole();
        switch (choice) {
            case 0:
                acc::saveToFile();
                tt::clearConsole();
                user = acc::login();
                break;
            case 1:
                acc::showProfile(*user);
                cout << "\nPress Enter to continue...";
                getchar();
                break;
            case 2:
                acc::changePassword(user);
                break;
            case 3:
                if (user->type == 1);
                else academicYearMenu(user->type);
                break;
            case 4:
                if (user->type == 1);
                else;
                break;
            case 5:
                if (user->type == 1);
                else if (user->type > 2) {
                    clss cl;
                    cl.menu();
                }
                break;
            case 6:
            default:
                cout << "\nInvalid choice\n";
        }
        cout << "\n";
    }

    delete user;

    return 0;
}

