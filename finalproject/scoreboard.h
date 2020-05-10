#ifndef _SCOREBOARD_H_INCLUDED_
#define _SCOREBOARD_H_INCLUDED_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



struct date
{
	int d, m, y;
};

struct Time
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
	vector<date> checkedDate;
	vector<Time> checkedTime;
};

/*struct score
{
	float mid, final, bonus, total;
};*/
struct course
{
	int number;
	string id;
	std::string name;
	std::string className;
	std::string lecturer;
	string DoW; // date of week, Monday is 0, Tuesday is 1,...
	date startDate, endDate;
	Time startTime, endTime;
	//std::vector<student *> students;
	std::string room;
};
void ViewStudentScoreBoard(vector<score> B);
void FindStudent(student& A, int ID);
void LoadClass(vector<student>& list, string inputpath);
void LoadStudent(ifstream& fin, vector<student>& list);
void LoadStudentCourse(ifstream& file, vector<string>& course, string inputpath);
void SearchCourse(string& Year, string& Semester, string& Course);
void LoadFile(string inputpath, vector<string>& A);
void PrintStudentScore(string inputpath, int choice, string year, string semester, string course);
void LoadCourseFile(vector<course>& list, string filePath);
void ExportCsv(vector<score>B);
void ImportCsv(string importpath,vector<score>& B);
void LoadYearFile(string inputpath, vector<string>& A);
void DecideToView(string year, string semester, string course);
void EditScore(string inputpath, string year, string semester, string course);
void SaveFileScore(string outputpath, score student);
#endif _SCOREBOARD_H_INCLUDED_
