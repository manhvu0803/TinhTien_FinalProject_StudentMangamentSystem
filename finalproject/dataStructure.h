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

struct lecturer
{
	int number;
	std::string username;
	std::string fullName;
	std::string degree;
	char gender; // 'M' for male, 'F' for female
}

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
	int number
	int id; // ID of the student this score belongs to
	int mid, final, bonus, total;
}

struct course
{
    int number;
    int id;
    std::string name;
    std::string className;
    std::string lecturer;
    int DoW; // date of week, Monday is 0, Tuesday is 1,...
    date startDate, endDate;
    time startTime, endTime;
    //std::vector<student *> students;
    std::string room;
};