#include"student.h"

const auto ignoreMax = numeric_limits<streamsize>::max();

void StudentMenu()
{
	int choice;
	do
	{
		cout << "===================== Student menu ======================\n";
        cout << "Press 1: Check-in.\n";
        cout << "Press 2: View check-in result.\n";
        cout << "Press 3: View schedules.\n";
        cout << "Press 4: View score as a course.\n";
        cout << "Press 0: Exit.\n";

        cout << "Your choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore(ignoreMax, '\n');
        if (cin.fail()) choice = -1;
        switch (choice)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        default:
        {
            cout << "Invalid choice.\n";
            break;
        }
        }
        if (choice != 0)
        {
            cout << endl;
        }
	} while (choice != 0);
}