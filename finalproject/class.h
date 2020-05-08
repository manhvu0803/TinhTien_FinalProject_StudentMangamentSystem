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
        void menu();
        int classPos(string className);
    private:
        static const char* classDir;
        static const char* classDat;
        tt::vector<string> classes;

        void import(ifstream& inFile, string className);
};

#endif
