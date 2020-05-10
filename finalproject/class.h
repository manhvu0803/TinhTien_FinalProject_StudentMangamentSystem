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
        void studentToFile(string className, tt::student newStd);
        void studentsToFile(string className, tt::vector<tt::student>& newClass);
        tt::student getStudent(string className, int id);
        void import(istream& inFile, string className);
        void menu();
    private:
        static const char* classDir;
        static const char* classDat;
        tt::vector<string> classes;

        void studentToStream(ostream& stream, const tt::student& newStd);
        tt::student addStudentMenu(string className, int id);
        void classesToFile();
};

#endif
