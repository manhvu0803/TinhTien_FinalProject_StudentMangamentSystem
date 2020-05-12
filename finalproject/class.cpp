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
    className = tt::capitalize(className);
    for (int i = 0, lim = classes.size(); i < lim; ++i)
        if (className == classes[i]) return i;
    return -1;
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

bool clss::rewriteStudent(string className, tt::student newStd, bool cap)
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
            thisCls.push_back(newStd);
        }
        else thisCls.push_back(res);
    }

    if (added) classToFile(className, thisCls);
    return added;
}

tt::student clss::getStudent(string className, int id, bool cap)
{
    if (cap) className = tt::capitalize(className);
    tt::student res;
    res.id = -1;
    res.cls = className;
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
            for (int i = 0; i < 5; ++i)
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
        res = getStudent(classes[i], id, false);
        if (res.id > 0) return res;
    }
    res.id = -1;
    return res;
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

        getline(ss, input, ',');
        newStd.id = stoi(input);

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
    if (!tt::cinIg(cin, newStd.number) || newStd.number < 0) {
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
    cout << "Student ID: ";
    if (!tt::cinIg(cin, newStd.id)) return newStd;
    newStd = getStudent(newStd.id);
    if (newStd.id > -1) {
        cout << "Student " << newStd.id << " has already existed in class " << newStd.cls << "\n\n";
        newStd.number = -1;
        return newStd;
    }

    inputStudent(newStd);
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
                if (studentToFile(className, addStudentMenu(className))) cout << "Student added\n\n";
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
                    cout << "Student " << newStd.id << " does not existed\n\n";
                    break;
                }
                cout << "\nEditing student " << newStd.id << " in class " << newStd.cls << "\n";

                inputStudent(newStd);
                if (rewriteStudent(newStd.cls, newStd)) cout << "Updated student " << newStd.id << "\n\n";
                else cout << "Aborted\n\n";
                break;
            }
            default:
                cout << "Invalid choice\n\n";
        }
    }
    while (choice != 0);
}
