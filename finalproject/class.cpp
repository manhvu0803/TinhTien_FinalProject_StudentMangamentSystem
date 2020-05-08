#include "class.h"
#include <sstream>
#include <fstream>

const char* clss::classDir = "data\\classes\\";
const char* clss::classDat = "data\\classes\\class.dat";

clss::clss()
{
    ifstream file(classDat);
    string name;
    while (getline(file, name))
        classes.push_back(name);
    file.close();
}

clss::~clss()
{

}

int clss::classPos(string className)
{
    for (int i = 0, lim = classes.size(); i < lim; ++i)
        if (className == classes[i]) return i;
    return -1;
}

void toFile(string dir, tt::vector<tt::student>& newClass)
{
    ofstream file(dir);
    for (int i = 0, lim = newClass.size(); i < lim; ++i) {
        file << newClass[i].number << '\n' << newClass[i].id << '\n';
        file << newClass[i].lastName << '\n' << newClass[i].firstName << '\n' << newClass[i].gender << '\n';
        file << newClass[i].DoB.y << '\n' << newClass[i].DoB.m << '\n' << newClass[i].DoB.d << '\n';
    }
    file.close();
}

void clss::import(ifstream& inFile, string className)
{
    for (int i = 0, lim = className.length(); i < lim; ++i)
        className[i] = toupper(className[i]);

    classes.push_back(classDir + className + ".dat");

    ofstream outFile(classDir + className + ".dat");
    string s;
    getline(inFile, s);
    while (getline(inFile, s)) {
        tt::student newStd;
        stringstream ss(s);
        string input;
        getline(ss, input, ',');
        outFile << input << '\n';
        getline(ss, input, ',');
        outFile << input << '\n';
        getline(ss, input, ',');
        int pos = input.find_last_of(' ');
        outFile << input.substr(0, pos) << '\n';
        outFile << input.substr(pos + 1) << '\n';
        getline(ss, input, ',');
        outFile << (char)toupper(input[0]) << '\n';
        getline(ss, input, ',');
        tt::date DoB = tt::parseToDate(input);
        outFile << DoB.y << ' ' << DoB.m << ' ' << DoB.d << '\n';
    }

    inFile.close();
    outFile.close();
}

void clss::menu()
{
    cout << "===================== Class menu =====================\n\n";
    cout << "Please enter your choice\n";

    int choice;
    do {
        cout << "Press 1: Import a class from a csv file\n";
        cout << "Press 2: Add a student to a class\n";
        cout << "Press 3: Edit a student\n";
        cout << "Press 4: Remove a student from a class\n";
        cout << "Press 5: Change a student's class";
        cout << "Press 6: View list of class\n";
        cout << "Press 7: View list of student in a class\n";
        cout << "Press 0: Exit\n";

        cout << "Your choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore(1024, '\n');
        if (cin.fail()) choice = -1;

        switch (choice) {
            case 0:
                break;
            case 1: {
                string importDir, className;
                cout << "\nThe csv must be in format: No.,Student ID,Fullname,Gender,DoB\n";
                cout << "Please enter the file directory to import: ";
                cin >> importDir;
                ifstream inFile(importDir);
                if (!inFile.is_open()) {
                    cout << importDir << " not found\n\n";
                    break;
                }
                cout << "Please enter the class' name: ";
                cin >> className;
                char cfm = 'y';
                if (classPos(className) > -1) {
                    cout << className << " is already existed\nDo you want to overwrite it? (Y/N)";
                    cin >> cfm;
                }
                if (cfm == 'Y' || cfm == 'y') {
                    import(inFile, className);
                    cout << "Import successfully\n\n";
                }
                inFile.close();
                break;
            }
            default:
                cout << "Invalid choice\n\n";
        }
    }
    while (choice != 0);
}
