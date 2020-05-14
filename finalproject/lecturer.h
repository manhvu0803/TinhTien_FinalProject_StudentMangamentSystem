#ifndef LECTURER_H_INCLUDED
#define LECTURER_H_INCLUDED

#include <fstream>
#include "utility.h"
#include "dataStructure.h"

class ltr
{
    public:
        ltr();
        ~ltr();
        int position(tt::lecturer user);
        void add(tt::lecturer user);
        void replace(tt::lecturer user, int pos);
        void courseMenu();
    private:
        static const char* ltrFile;
        tt::vector<tt::lecturer> ltrs;
};

#endif // LECTURER_H_INCLUDED
