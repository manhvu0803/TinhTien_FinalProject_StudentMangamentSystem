#ifndef LECTURER_H_INCLUDED
#define LECTURER_H_INCLUDED

#include "utility.h"
#include "dataStructure.h"

class ltr
{
    public:
        ltr();
        ~ltr();
        int position(const tt::lecturer& user);
        void add(tt::lecturer user);
        void replace(tt::lecturer user, int pos);
        void menu();
        void showAll();
    private:
        static const char* ltrFile;
        tt::vector<tt::lecturer> ltrs;

        void saveToFile();
        void input(tt::lecturer& newLtr);
};

#endif // LECTURER_H_INCLUDED
