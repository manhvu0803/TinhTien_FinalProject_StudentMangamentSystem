#include "class.h"
#include "dataStructure.h"
#include "utility.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include "accountControl.h"
#include <limits>

using namespace std;

const char* clss::classDir = "data/classes/";
const char* clss::classDat = "data/classes/class.dat";

const auto ignoreMax = numeric_limits<streamsize>::max();

clss::clss()
{
    ifstream file(classDat);
    string name;
    while (getline(file, name)) {
        classes.push_back(name);
        ifstream classFile(classDir + name + ".dat");
        tt::student res;
        res.cls = name;
        if (!classFile.is_open()) break;
        while (classFile >> res.number) {
            classFile >> res.id;
            classFile.ignore(ignoreMax, '\n');
            getline(classFile, res.lastName);
            getline(classFile, res.firstName);
            classFile >> res.gender >> res.DoB.y >> res.DoB.m >> res.DoB.d;
            students.push_back(res);
        }
        classFile.close();
    }
    file.close();
}

clss::~clss()
{
}

int clss::classPos(string className)
{
    className = tt::capitalize(className);
    for (int i = 0, lim = classes.size(); i < lim; ++i)
        if (className == classes[i]) return i;
    return -1;
}

tt::student clss::getStudent(string className, int id, bool cap)
{
    if (cap) className = tt::capitalize(className);
    tt::student res;
    res.number = -1;
    res.id = -1;
    for (int i = 0, lim = students.size(); i < lim; ++i)
        if (id == students[i].id && className == students[i].cls) return students[i];
    return res;
}

tt::student clss::getStudent(int id)
{
    tt::student res;
    res.id = -1;
    res.number = -1;
    for (int i = 0, lim = students.size(); i < lim; ++i)
        if (id == students[i].id) return students[i];
    return res;
}

void inline clss::studentToStream(ostream& stream, const tt::student& newStd)
{
    stream << newStd.number << '\n' << newStd.id << '\n';
    stream << newStd.lastName << '\n' << newStd.firstName << '\n' << newStd.gender << '\n';
    stream << newStd.DoB.y << ' ' << newStd.DoB.m << ' ' << newStd.DoB.d << '\n';
}

void clss::classListToFile()
{
    ofstream file(classDat);
    for (int i = 0, lim = classes.size(); i < lim; ++i)
        file << classes[i] << '\n';
}

bool clss::studentToFile(string className, tt::student newStd, bool cap)
{
    if (newStd.number == -1 || newStd.id == -1 || newStd.firstName == "" || newStd.lastName == "") return false;
    if (cap) className = tt::capitalize(className);
    ofstream file(classDir + className + ".dat", ios::app);
    studentToStream(file, newStd);
    file.close();
    return true;
}

void clss::classToFile(string className, tt::vector<tt::student>& newClass)
{
    className = tt::capitalize(className);
    ofstream file(classDir + className + ".dat");
    for (int i = 0, lim = newClass.size(); i < lim; ++i)
        studentToStream(file, newClass[i]);
    file.close();
}

bool clss::rewriteStudent(string className, const tt::student& newStd, int mode, bool cap)
{
    if (newStd.number == -1 || newStd.id == -1 || newStd.firstName == "" || newStd.lastName == "") return false;
    if (cap) className = tt::capitalize(className);

    ifstream file(classDir + className + ".dat");
    tt::vector<tt::student> thisCls;
    tt::student res;
    bool added = false;

    while (file >> res.number) {
        file >> res.id;
        file.ignore(ignoreMax, '\n');
        getline(file, res.lastName);
        getline(file, res.firstName);
        file >> res.gender >> res.DoB.y >> res.DoB.m >> res.DoB.d;
        if (res.id == newStd.id) {
            added = true;
            if (mode == 1) thisCls.push_back(newStd);
        }
        else thisCls.push_back(res);
    }

    if (added) {
        classToFile(className, thisCls);
        for (int i = 0, lim = students.size(); i < lim; ++i)
            if (students[i].id == newStd.id) students[i] = newStd;
    }
    return added;
}

bool clss::import(istream& inFile, string className)
{
    className = tt::capitalize(className);
    tt::vector<tt::student> newClass;

    string s, output;
    getline(inFile, s);
    while (getline(inFile, s)) {
        tt::student newStd;
        stringstream ss(s);
        string input;

        getline(ss, input, ',');
        newStd.number = stoi(input);
        if (getStudent(newStd.id).id > 0) {
            cout << "Student number cannot exceed 3 characters";
            return false;
        }

        getline(ss, input, ',');
        newStd.id = stoi(input);
        if (getStudent(newStd.id).id > 0) {
            cout << "Student" << newStd.id << "has already existed\n\n";
            return false;
        }

        getline(ss, input, ',');
        int pos = input.find_last_of(' ');
        newStd.lastName = input.substr(0, pos);
        newStd.firstName = input.substr(pos + 1);

        getline(ss, input, ',');
        newStd.gender = toupper(input[0]);
        if (newStd.gender != 'F' && newStd.gender != 'M') {
            cout << "Invalid gender format\n";
            return false;
        }

        getline(ss, input, ',');
        newStd.DoB = tt::stringToDate(input);
        if (tt::checkDate(newStd.DoB) != 1) {
            cout << "Invalid date of birth format\n";
            return false;
        }

        newClass.push_back(newStd);
    }

    classToFile(className, newClass);
    if (classPos(className) < 0) classes.push_back(className);
    classListToFile();
    return true;
}

bool clss::inputStudent(tt::student& newStd)
{
    cout << "Student number: ";
    if (!tt::cinIg(cin, newStd.number) || newStd.number < 0 || newStd.number > 999) {
        cout << "Student number cannot be negative and exceed 3 character\n";
        newStd.id = -1;
        return false;
    }
    cout << "Family name and surname: ";
    getline(cin, newStd.lastName);
    cout << "Given name (first name): ";
    getline(cin, newStd.firstName);

    while (true) {
        cout << "Gender (F/M): ";
        bool valid = tt::cinIg(cin, newStd.gender);
        newStd.gender = toupper(newStd.gender);
        if (!valid || (newStd.gender != 'F' && newStd.gender != 'M')) cout << "Invalid gender\n";
        else break;
    }

    while (true) {
        cout << "Date of birth (YYYY MM DD): ";
        bool sc = tt::cinIg(cin, newStd.DoB.y, false) && tt::cinIg(cin, newStd.DoB.m, false) && tt::cinIg(cin, newStd.DoB.d);
        if (!sc || tt::checkDate(newStd.DoB) != 1) cout << "Invalid date\n";
        else break;
    }

    return true;
}

tt::student clss::addStudentMenu(string className)
{
    className = tt::capitalize(className);
    tt::student newStd;
    newStd.number = -1;

    cout << "\nStudent info\n";
    cout << "Student ID (no more than 12 character): ";
    int id;
    if (!tt::cinIg(cin, id) || id > 999999999999) return newStd;
    newStd = getStudent(id);
    if (newStd.id > -1) {
        cout << "Student " << newStd.id << " has already existed in class " << newStd.cls << "\n\n";
        newStd.number = -1;
        return newStd;
    }
    newStd.id = id;

    inputStudent(newStd);
    students.push_back(newStd);
    return newStd;
}

void clss::showClass(string className)
{
    ifstream file(classDir + className + ".dat");
    tt::student res;

    cout << "No. |  ID         |    Name                          | Gender | Date of birth\n";

    while (file >> res.number) {
        cout << "-------------------------------------------------------------------------------\n";
        cout << left << setw(4) << res.number;
        file >> res.id;
        cout << "| " << setw(12) << res.id;
        file.ignore(ignoreMax, '\n');
        getline(file, res.lastName);
        getline(file, res.firstName);
        cout << "| " << setw(33) << res.lastName + " " + res.firstName;
        file >> res.gender;
        cout << "| " << setw(7) << ((res.gender == 'M') ? "Male" : "Female");
        file >> res.DoB.y >> res.DoB.m >> res.DoB.d;
        cout << "|  " << res.DoB.y << '-' << res.DoB.m << '-' << res.DoB.d << "\n";
    }
    cout << '\n';
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
        cout << "Press 5: Change a student's class\n";
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

                cout << "Class name: ";
                cin >> className;
                if (classPos(className) > -1) {
                    char cfm = 'y';
                    cout << className << " has already existed\nDo you want to overwrite it? (Y/N): ";
                    cin >> cfm;
                    if (cfm != 'y' && cfm != 'Y') {
                        cout << "Aborted\n\n";
                        break;
                    }
                }

                cout << "File directory to import: ";
                cin >> importDir;
                ifstream inFile(importDir);
                if (!inFile.is_open()) {
                    cout << importDir << " not found\n\n";
                    break;
                }
                if (import(inFile, className)) cout << "Import successfully\n\n";
                else cout << "Aborted\n\n";
                inFile.close();

                break;
            }
            case 2: {
                string className;
                cout << "\nClass to add new student: ";
                cin >> className;
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
                tt::student newStd = addStudentMenu(className);
                if (studentToFile(className, newStd)) {
                    cout << "Student added\n\n";
                    acc::createAccount(newStd);
                }
                else cout << "Aborted\n\n";

                break;
            }
            case 3: {
                tt::student newStd;
                newStd.number = -1;

                cout << "\nStudent ID to edit: ";
                if (!tt::cinIg(cin, newStd.id)) break;
                newStd = getStudent(newStd.id);

                if (newStd.id < 0) {
                    cout << "That student does not existed\n\n";
                    break;
                }

                char cfm;
                cout << "\nEdit student " << newStd.id << " in class " << newStd.cls << " (Y/N)?: ";
                tt::cinIg(cin, cfm);
                if (cfm != 'Y' && cfm != 'y') {
                    cout << "Aborted\n\n";
                    break;
                }

                inputStudent(newStd);
                if (rewriteStudent(newStd.cls, newStd)) cout << "Updated student " << newStd.id << "\n\n";
                else cout << "Aborted\n\n";
                break;
            }
            case 4: {
                tt::student tmpStd;
                tmpStd.number = -1;

                cout << "\nStudent ID to remove: ";
                if (!tt::cinIg(cin, tmpStd.id)) break;
                tmpStd = getStudent(tmpStd.id);

                if (tmpStd.id < 0) {
                    cout << "That student does not existed\n\n";
                    break;
                }

                char cfm;
                cout << "\nRemove student " << tmpStd.id << " in class " << tmpStd.cls << " (Y/N)?: ";
                tt::cinIg(cin, cfm);

                if ((cfm == 'Y' || cfm == 'y') && rewriteStudent(tmpStd.cls, tmpStd, 2)) cout << "Removed\n\n";
                else cout << "Aborted\n\n";
                break;
            }
            case 5: {
                tt::student tmpStd;
                tmpStd.number = -1;

                cout << "\nStudent ID to move: ";
                if (!tt::cinIg(cin, tmpStd.id)) break;
                tmpStd = getStudent(tmpStd.id);

                if (tmpStd.id < 0) {
                    cout << "That student does not existed\n\n";
                    break;
                }
                cout << "Found in class " << tmpStd.cls << '\n';

                cout << "Class to move this student to: ";
                string newClass;
                tt::cinIg(cin, newClass);
                newClass = tt::capitalize(newClass);
                if (newClass == tmpStd.cls) cout << "Same class. Abort move\n\n";
                else if (classPos(newClass) < 0) cout << "That class doesn't exist\n\n";
                else {
                    rewriteStudent(tmpStd.cls, tmpStd, 2);
                    studentToFile(newClass, tmpStd, false);
                    cout << "Moved student " << tmpStd.id << " from " << tmpStd.cls << " to " << newClass << "\n\n";
                }

                break;
            }
            case 6: {
                cout << "\nList of classes:\n";
                for (int i = 0, lim = classes.size(); i < lim; ++i)
                    cout << classes[i] << '\n';
                cout << "\nPress enter to continue...";
                getchar();
                cout << '\n';
            }
            case 7: {
                cout << "\nClass to show: ";
                string className;
                tt::cinIg(cin, className);
                if (classPos(className) > 0)
                    showClass(className);
                else cout << "That class doesn't exist\n\n";
                break;
            }
            default:
                cout << "Invalid choice\n\n";
        }
    }
    while (choice != 0);
}
