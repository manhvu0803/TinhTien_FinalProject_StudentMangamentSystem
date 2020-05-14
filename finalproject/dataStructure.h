#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#include <string>
#include "utility.h"

namespace tt
{
    struct date
    {
        int d = -1, m = -1, y = -1;
    };

    struct time
    {
        int h = -1, m = -1, s = -1;
    };

    struct lecturer
    {
        int number = -1;
        std::string username = "";
        std::string fullName = "";
        std::string degree = "";
        char gender = 'T'; // 'M' for male, 'F' for female
    };

    struct student
    {
        int number = -1;
        int id = -1;
        std::string lastName = "", firstName = "";
        std::string cls = ""; // class of the student, won't be use most of the time
        char gender = 'T'; // 'M' for male, 'F' for female
        date DoB; // date of birth
    };

    struct score
    {
        std::string cls = ""; // class of the student
        std::string studentName = "";
        int id = -1; // ID of the student this score belongs to
        float mid = -1, final = -1, bonus = -1, total = -1;
        float mid = -1, final = -1, bonus = -1, total = -1;
        tt::vector<date> checkedDate;
        tt::vector<time> checkedTime;
    };

    struct course
    {
        int number = -1;
        std::string id = "";
        std::string name = "";
        std::string className = "";
        std::string lecturer = "";
        int DoW = -1; // date of week, Monday is 0, Tuesday is 1,...
        date startDate, endDate;
        time startTime, endTime;
        //tt::vector<student *> students;
        std::string room = "";
    };

    struct checkIn
    {
        int id = -1;
        date cDate;
        time cTime;
    };

    date currentDate();

    // Return 24-hour format
    time currentTime();

    // Return -1 if month is invalid, -2 if day is invalid, 1 if valid past date, 2 if valid future date
    int checkDate(const date& dt);

    // Parse string to date struct, support YYYY-MM-DD and MM/DD/YYYY
    date stringToDate(const std::string& str);
}

#endif // DATASTRUCTURE_H_INCLUDED
