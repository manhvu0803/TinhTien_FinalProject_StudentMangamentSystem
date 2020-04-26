#ifndef _SCOREBOARD_H_INCLUDED_
#define _SCOREBOARD_H_INCLUDED_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct DoB {
	int day;
	int month;
	int year;
};
struct Score {
	int Midtern;
	int Final;
	int Total;
	int Bonus;
};
struct Student {
	int No;
	int ID;
	string LastName,
		MiddleName,
		FirstName,
		Gender;
	DoB Birth;
	Score Grade;
};

#endif
