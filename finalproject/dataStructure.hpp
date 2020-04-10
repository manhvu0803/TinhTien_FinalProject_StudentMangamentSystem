#ifndef DATASTRUCTER_HPP_INCLUDED
#define DATASTRUCTER_HPP_INCLUDED

#include <string>
#include <vector>

struct date
{
    int d, m, y;
};

struct time
{
    int h, m, s;
};

struct student
{
    int number;
    int id;
    std::string lastName, firstName;
    char gender; // 'M' for male, 'F' for female
    date DoB; // date of birth
};

struct course
{
    int number;
    int id;
    std::string name;
    std::string className;
    std::string lecturer
    std::string room;
    int DoW; // date of week, Monday is 0, Tuesday is 1,...
    date startDate, endDate;
    time startTime, endTime;
    std::vector<student *> students;
};

#endif // DATASTRUCTER_HPP_INCLUDED
