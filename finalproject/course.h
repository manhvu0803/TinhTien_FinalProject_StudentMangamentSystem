#ifndef COURSE_INCLUDE_H_
#define COURSE_INCLUDE_H_
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <cmath>
#include "class.h"

using namespace std;
struct courseTime
{
	int hour = 0;
	int min = 0;
	void clear();
};

struct course
{
	int No = NULL;
	string Name, Id, Class, lecturerAccount, lecturerName, lecturerDegree, lecturerGender, DoW, room;
	date startDate, endDate;
	courseTime startHour, endHour;
	vector<int> studentId;
	void clear();
};
void courseMenu(int year, string semester);
void loadCsvFile(vector<course>& list, string filePath);
void loadDatFile(vector<course>& list, string filePath);
void loadCourseStudentFile(course& Course, string filePath);
void saveCourseList(vector<course> list, string filePath);
void saveCourseStudentFile(course Course, string filePath);
void importCsvFile(vector<course>& list, string filePath);
void output1Course(course Course);
void outputCourseList(vector<course> list);
void output1CourseData(course Course);
void outputSchedule(vector<course> list);
int  inputTime(courseTime& time);
int  inputDate(date& Date);
void inputLecturer(course& Course);
void input1Course(course& newCourse);
void inputCourse(vector<course>& list, string filePath);
void editCourse(vector<course>& list, string filePath);
void deleteCourse(vector<course>& list, string filePath);
void remove1Student(course& Course);
void add1Student(course& Course);
void addStudent(course& Course);
void viewStudentList(course courseName);
void sortList(vector<course>& List);
void upperCase(string& name);
course searchCourse(string filePath, string Id);

#endif