#ifndef CLASS_H_INCLUDE
#define CLASS_H_INCLUDE

#include <iostream>
#include <string>
#include "dataStructure.h"
#include "utility.h"

using namespace std;

class clss
{
    public:
        clss();
        ~clss();
        int classPos(string className);
        // Return true if student is valid and added to file
        bool studentToFile(string className, tt::student newStd, bool cap = true);
        void classToFile(string className, tt::vector<tt::student>& newClass);
        tt::student getStudent(string className, int id, bool cap = true);
        tt::student getStudent(int id);
        // Return true if the file is valid and saved
        bool import(istream& inFile, string className);
        void menu();
    private:
        static const char* classDir;
        static const char* classDat;
        tt::vector<string> classes;

        void studentToStream(ostream& stream, const tt::student& newStd);
        tt::student addStudentMenu(string className);
        void classesToFile();
};

#endif
