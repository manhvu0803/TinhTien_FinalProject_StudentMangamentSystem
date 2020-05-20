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

        // Return -1 if input class does not exist
        int classPos(string className);

        tt::student getStudent(string className, int id, bool cap = true);
        tt::student getStudent(int id);

        const tt::vector<tt::student>& getClass(string className);

        void showClass(tt::vector<tt::student>& thisCls);

        void menu();

    private:
        static const char* classDir;
        static const char* classDat;
        static tt::vector<tt::student> emptyVec;

        tt::vector<string> classes;
        tt::vector<tt::vector<tt::student>> students;

        void studentToStream(ostream& stream, const tt::student& newStd);

        // Return true if student is valid and added to file
        bool studentToFile(string className, tt::student newStd, bool cap = true);

        void classToFile(string className, tt::vector<tt::student>& newClass);

        void classListToFile();

        bool rewriteStudent(string className, const tt::student& newStd, int mode = 1, bool cap = true);

        // Return true if the file is valid and saved
        bool import(istream& inFile, string className);

        bool inputStudent(tt::student& newStd);

        tt::student addStudentMenu(string className);
        tt::student editStudentMenu();
};

#endif
