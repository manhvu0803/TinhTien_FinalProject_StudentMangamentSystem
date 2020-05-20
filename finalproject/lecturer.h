#ifndef LECTURER_H_INCLUDED
#define LECTURER_H_INCLUDED

#include "utility.h"
#include "dataStructure.h"
#include <string>

class ltr
{
    public:
        ltr();
        ~ltr();
        int position(const std::string& user);
        tt::lecturer get(const std::string& user);
        bool add(const tt::lecturer& user);
        bool replace(const std::string& username, const tt::lecturer& user);
        bool remove(const std::string& username);
        void menu();
        void showAll();
    private:
        static const char* ltrFile;
        tt::vector<tt::lecturer> ltrs;

        void saveToFile();
        void input(tt::lecturer& newLtr);
};

#endif // LECTURER_H_INCLUDED
