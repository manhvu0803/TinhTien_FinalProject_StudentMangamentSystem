#include "class.h"
#include "dataStructure.h"
#include "utility.h"
#include <sstream>
#include <fstream>
#include <limits>

using namespace std;

const char* clss::classDir = "data/classes/";
const char* clss::classDat = "data/classes/class.dat";

const auto ignoreMax = numeric_limits<streamsize>::max();

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

void inline clss::studentToStream(ostream& stream, const tt::student& newStd)
{
    stream << newStd.number << '\n' << newStd.id << '\n';
    stream << newStd.lastName << '\n' << newStd.firstName << '\n' << newStd.gender << '\n';
    stream << newStd.DoB.y << ' ' << newStd.DoB.m << ' ' << newStd.DoB.d << ' ';
}

void clss::classesToFile()
{
    ofstream file(classDat);
    for (int i = 0, lim = classes.size(); i < lim; ++i)
        file << classes[i] << '\n';
}

void clss::studentToFile(string className, tt::student newStd)
{
    ofstream file(classDir + className + ".dat", ios::app);
    studentToStream(file, newStd);
    file.close();
}

void clss::studentsToFile(string className, tt::vector<tt::student>& newClass)
{
    ofstream file(classDir + className + ".dat");
    for (int i = 0, lim = newClass.size(); i < lim; ++i)
        studentToStream(file, newClass[i]);
    file.close();
}

tt::student clss::getStudent(string className, int id)
{
    tt::student res;
    res.id = -1;
    ifstream file(classDir + className + ".dat");
    if (!file.is_open()) return res;
    while (file >> res.number) {
        file >> res.id;
        if (id == res.id) {
            file.ignore(ignoreMax, '\n');
            getline(file, res.lastName);
            getline(file, res.firstName);
            file >> res.gender >> res.DoB.y >> res.DoB.m >> res.DoB.d;
            return res;
        }
        else {
            for (int i = 0; i < 4; ++i)
                file.ignore(ignoreMax, '\n');
        }
    }
    file.close();
    res.id = -1;
    return res;
}

tt::student clss::getStudent(int id)
{
    tt::student res;
    res.id = -1;
    for (int i = 0, lim = classes.size(); i < lim; ++i) {
        res = getStudent(classes[i], id);
        if (res.id > 0) return res;
    }
    res.id = -1;
    return res;
}

void clss::import(istream& inFile, string className)
{
    for (int i = 0, lim = className.length(); i < lim; ++i)
        className[i] = toupper(className[i]);

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
        tt::date DoB = tt::stringToDate(input);
        outFile << DoB.y << ' ' << DoB.m << ' ' << DoB.d << '\n';
    }
    outFile.close();

    classes.push_back(className);
    classesToFile();
}

tt::student clss::addStudentMenu(string className, int id)
{
    tt::student newStd;
    newStd.id = id;

    cout << "Student number: ";
    tt::cinIg(cin, newStd.number);
    cout << "Family name and surname: ";
    getline(cin, newStd.lastName);
    cout << "Given name (first name): ";
    getline(cin, newStd.firstName);
    while (true) {
        cout << "Gender (F/M): ";
        bool valid = tt::cinIg(cin, newStd.gender);
        newStd.gender = toupper(newStd.gender);
        if (!valid || (newStd.gender != 'F' && newStd.gender != 'M'))
            cout << "Invalid gender\n";
        else break;
    }
    while (true) {
        cout << "Date of birth (YYYY MM DD): ";
        bool sc = tt::cinIg(cin, newStd.DoB.y, false) && tt::cinIg(cin, newStd.DoB.m, false) && tt::cinIg(cin, newStd.DoB.y);
        if (!sc || tt::checkDate(newStd.DoB) < 0)
            cout << "Invalid date\n";
        else break;
    }
    return newStd;
}

void clss::menu()
{
    cout << "===================== Class menu =====================\n\n";

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
        if (!tt::cinIg(cin, choice)) choice = -1;

        switch (choice) {
            case 0:
                break;
            case 1: {
                string importDir, className;
                cout << "\nThe csv file must be in format: No.,Student ID,Full name,Gender,Date of birth\n";
                cout << "File directory to import: ";
                cin >> importDir;
                ifstream inFile(importDir);
                if (!inFile.is_open()) {
                    cout << importDir << " not found\n\n";
                    break;
                }
                cout << "Class name: ";
                cin >> className;
                char cfm = 'y';
                if (classPos(className) > -1) {
                    cout << className << " is already existed\nDo you want to overwrite it? (Y/N): ";
                    cin >> cfm;
                }
                if (cfm == 'Y' || cfm == 'y') {
                    import(inFile, className);
                    cout << "Import successfully\n\n";
                }
                inFile.close();
                break;
            }
            case 2: {
                string className;
                cout << "\nClass to add new student: ";
                cin >> className;
                className = tt::capitalize(className);
                if (classPos(className) == -1) {
                    cout << "Class " << className << " doesn't exist. Do you want to create it? (Y/N): ";
                    char cfm;
                    cin >> cfm;
                    cin.clear();
                    cin.ignore(ignoreMax, '\n');
                    if (cfm == 'y' || cfm == 'Y') {
                        classes.push_back(className);
                        cout << "Created " << className << '\n';
                    }
                    else {
                        cout << "Aborted\n\n";
                        break;
                    }
                }
                cout << "\nNew student info\n";
                cout << "Student ID: ";
                int id;
                cin >> id;
                if (getStudent(className, id).id > -1) {
                    cout << "ID " << id << " is already existed\n\n";
                    break;
                }
                studentToFile(className, addStudentMenu(className, id));
                cout << "Student added\n\n";
                break;
            }
            default:
                cout << "Invalid choice\n\n";
        }
    }
    while (choice != 0);
}
