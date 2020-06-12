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

tt::vector<tt::student> clss::emptyVec;

const auto ignoreMax = numeric_limits<streamsize>::max();

clss::clss()
{
    ifstream file(classDat);
    string name;
    while (getline(file, name)) {
        ifstream classFile(classDir + name + ".dat");
        tt::vector<tt::student> tmpVec;
        tt::student res;
        res.cls = name;
        if (!classFile.is_open()) break;
        while (classFile >> res.number) {
            classFile >> res.id;
            classFile.ignore(ignoreMax, '\n');
            getline(classFile, res.lastName);
            getline(classFile, res.firstName);
            classFile >> res.gender >> res.DoB.y >> res.DoB.m >> res.DoB.d;
            tmpVec.push_back(res);
        }
        classes.push_back(name);
        students.push_back(tmpVec);
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
    int pos = classPos(className);
    for (int i = 0, lim = students[pos].size(); i < lim; ++i)
        if (id == students[pos][i].id) return students[pos][i];
    return res;
}

const tt::vector<tt::student>& clss::getClass(string className)
{
    int pos = classPos(tt::capitalize(className));
    if (pos > -1) return students[pos];
    return emptyVec;
}

tt::student clss::getStudent(int id)
{
    tt::student res;
    res.number = -1;
    res.id = -1;
    for (int pos = 0, lim = classes.size(); pos < lim; ++pos)
        for (int i = 0, lim2 = students[pos].size(); i < lim2; ++i)
            if (id == students[pos][i].id) return students[pos][i];
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
        int pos = classPos(className);
        for (int i = 0, lim = students[pos].size(); i < lim; ++i)
            if (students[pos][i].id == newStd.id) {
                if (mode == 1) students[pos][i] = newStd;
                else students[pos].erase(i);
            }
    }
    return added;
}

bool clss::import(istream& inFile, string className)
{
    className = tt::capitalize(className);
    tt::vector<tt::student> newClass;
    tt::makeDir(classDir + className);

    if (classPos(className) < 0) classes.push_back(className);

    string s, output;
    getline(inFile, s);
    while (getline(inFile, s)) {
        tt::student newStd;
        stringstream ss(s);
        string input;

        getline(ss, input, ',');
        newStd.number = stoi(input);
        if (newStd.number < 0 || newStd.number > 999) {
            cout << "Student number cannot be lower than 0 and exceed 999";
            return false;
        }

        getline(ss, input, ',');
        newStd.id = stoi(input);
        tt::student res = getStudent(newStd.id);
        if (res.id > 0 && res.cls != className) {
            cout << "Student " << newStd.id << "has already existed\n\n";
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
        ofstream file(classDir + className + '/' + to_string(newStd.id) + ".dat");
    }

    classToFile(className, newClass);
    students.push_back(newClass);
    classListToFile();
    return true;
}

bool clss::inputStudent(tt::student& newStd)
{
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
    newStd.cls = className;
    inputStudent(newStd);
    int pos = classPos(className);
    newStd.number = students[pos].size();
    students[pos].push_back(newStd);
    return newStd;
}

void clss::showClass(tt::vector<tt::student>& thisCls)
{
    cout << "No. |  ID         |    Name                          | Gender | Date of birth\n";

    for (int i = 0, lim = thisCls.size(); i < lim; ++i) {
        cout.fill(' ');
        cout << "-------------------------------------------------------------------------------\n";
        cout << left << setw(4) << thisCls[i].number;
        cout << "| " << setw(12) << thisCls[i].id;
        cout << "| " << setw(33) << thisCls[i].lastName + " " + thisCls[i].firstName;
        cout << "| " << setw(7) << ((thisCls[i].gender == 'M') ? "Male" : "Female");
        cout << "|  " << thisCls[i].DoB.y << '-' << thisCls[i].DoB.m << '-' << thisCls[i].DoB.d << "\n";
    }
    cout << '\n';
}

void clss::menu()
{
    int choice;
    do {
        tt::clearConsole();
        cout << "===================== Class menu =====================\n\n";
        cout << "Press 1: Import a class from a csv file\n";
        cout << "Press 2: Add a student to a class\n";
        cout << "Press 3: Edit a student\n";
        cout << "Press 4: Remove a student from a class\n";
        cout << "Press 5: Change a student's class\n";
        cout << "Press 6: View list of class\n";
        cout << "Press 7: View list of student in a class\n";
        cout << "Press 0: Return\n";

        cout << "Your choice: ";
        if (!tt::cinIg(cin, choice)) choice = -1;
        if (choice > -1 && choice < 8) tt::clearConsole();

        switch (choice) {
            case 0:
                break;
            case 1: {
                string importDir, className;
                cout << "The csv file must be in format: No.,Student ID,Full name,Gender,Date of birth\n";

                cout << "Class name: ";
                cin >> className;
                if (classPos(className) > -1) {
                    char cfm = 'y';
                    cout << className << " has already existed\nDo you want to overwrite it? (Y/N): ";
                    cin >> cfm;
                    if (cfm != 'y' && cfm != 'Y') {
                        cout << "Aborted";
                        getchar();
                        break;
                    }
                }

                cout << "File directory to import: ";
                cin >> importDir;
                ifstream inFile(importDir);
                if (!inFile.is_open()) cout << importDir << " not found";
                else {
                    if (import(inFile, className)) cout << "Import successfully";
                    else cout << "Aborted";
                    inFile.close();
                }
                getchar();
                break;
            }
            case 2: {
                string className;
                cout << "Class to add new student: ";
                cin >> className;
                char cfm = 'y';
                if (classPos(className) == -1) {
                    cout << "Class " << className << " doesn't exist. Do you want to create it? (Y/N): ";
                    tt::cinIg(cin, cfm);
                    className = tt::capitalize(className);
                    if (cfm == 'y' || cfm == 'Y') {
                        classes.push_back(className);
                        classListToFile();
                        tt::makeDir("./data/classes/" + className);
                        cout << "Created " << className << '\n';
                    }
                    else cout << "Aborted";
                }

                if (cfm == 'y' || cfm == 'T') {
                    tt::student newStd = addStudentMenu(className);
                    if (studentToFile(className, newStd)) {
                        ofstream file("./data/classes/" + className + '/' + to_string(newStd.id) + ".dat");
                        cout << "Student added";
                        acc::createAccount(newStd);
                    }
                    else cout << "Aborted";
                }

                break;
            }
            case 3: {
                tt::student newStd;
                newStd.number = -1;

                cout << "Student ID to edit: ";
                if (!tt::cinIg(cin, newStd.id)) break;
                newStd = getStudent(newStd.id);

                if (newStd.id < 0) {
                    cout << "That student does not existed";
                    break;
                }

                char cfm;
                cout << "\nEdit student " << newStd.id << " in class " << newStd.cls << " (Y/N)?: ";
                tt::cinIg(cin, cfm);
                if (cfm == 'Y' || cfm == 'y') {
                    inputStudent(newStd);
                    if (rewriteStudent(newStd.cls, newStd)) cout << "Updated student " << newStd.id;
                    else cout << "Aborted";
                }
                else cout << "Aborted";
                break;
            }
            case 4: {
                tt::student tmpStd;
                tmpStd.number = -1;

                cout << "Student ID to remove: ";
                if (!tt::cinIg(cin, tmpStd.id)) break;
                tmpStd = getStudent(tmpStd.id);

                if (tmpStd.id < 0) cout << "That student does not existed";
                else {
                    char cfm;
                    cout << "\nRemove student " << tmpStd.id << " in class " << tmpStd.cls << " (Y/N)?: ";
                    tt::cinIg(cin, cfm);

                    if ((cfm == 'Y' || cfm == 'y') && rewriteStudent(tmpStd.cls, tmpStd, 2))
                        cout << "Student removed";
                    else cout << "Aborted";
                }
                break;
            }
            case 5: {
                tt::student tmpStd;
                tmpStd.number = -1;

                cout << "Student ID to move: ";
                if (!tt::cinIg(cin, tmpStd.id)) break;
                tmpStd = getStudent(tmpStd.id);

                if (tmpStd.id < 0) {
                    cout << "That student does not existed";
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
                    students[classPos(newClass)].push_back(tmpStd);
                    ofstream file(classDir + newClass + '/' + to_string(tmpStd.id) + ".dat");
                    file.close();
                    cout << "Moved student " << tmpStd.id << " from " << tmpStd.cls << " to " << newClass;
                }

                break;
            }
            case 6: {
                cout << "List of classes:\n";
                for (int i = 0, lim = classes.size(); i < lim; ++i)
                    cout << classes[i] << '\n';
                cout << '\n';
                break;
            }
            case 7: {
                cout << "Class to show: ";
                string className;
                tt::cinIg(cin, className);
                int pos = classPos(className);
                if (pos > -1) showClass(students[pos]);
                else cout << "That class doesn't exist";
                break;
            }
            default:
                cout << "Invalid choice";
        }

        cout << "\nPress enter to continue...";
        if (choice != 0) getchar();
    }
    while (choice != 0);
}
