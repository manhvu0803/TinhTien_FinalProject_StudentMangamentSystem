#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#include <string>
#include "utility.h"

namespace tt
{
    struct date
    {
        int d = 0, m = 0, y = 0;
    };

    struct time
    {
        int h, m, s;
    };

    struct lecturer
    {
        int number;
        std::string username;
        std::string fullName;
        std::string degree;
        char gender; // 'M' for male, 'F' for female
    };

    struct student
    {
        int number;
        int id;
        std::string lastName, firstName;
        char gender; // 'M' for male, 'F' for female
        date DoB; // date of birth
    };

    struct score
    {
        std::string cls; // class of the student
        std::string studentName;
        int id; // ID of the student this score belongs to
        float mid, final, bonus, total;
        tt::vector<date> checkedDate;
        tt::vector<time> checkedTime;
    };

    struct course
    {
        int number;
        std::string id;
        std::string name;
        std::string className;
        std::string lecturer;
        int DoW; // date of week, Monday is 0, Tuesday is 1,...
        date startDate, endDate;
        time startTime, endTime;
        //tt::vector<student *> students;
        std::string room;
    };

    struct checkIn
    {
        int id;
        date cDate;
        time cTime;
    };

    // Check is date valid. Return -1 if month is invalid, -2 if day is invalid, 1 otherwise
    int checkDate(const date& d);

    // Parse string to date struct, support YYYY-MM-DD and MM/DD/YYYY
    date stringToDate(const std::string& str);
}

#endif // DATASTRUCTURE_H_INCLUDED
