#ifndef COURSE_H_INCLUDE
#define COURSE_H_INCLUDE

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct Student
{
	int Id;
	string lastName, firstName, Gender, DoB;
};
struct Course {
	int No=NULL;
	string Id, Name, Class, Account, startDate, endDate, DoWTheory, startHourTheory, endHourTheory, Room, DoWExcercise, startHourExcercise, endHourExcercise;
	vector<Student> student;
};
void scanCourse(vector<Course>& List);
void saveCourse(vector<Course>List);
void input1Course(vector<Course>& List);
void inputCourse(vector<Course>& List);
void output1Course(Course course);
void outputCourse(vector<Course> List);
void remove1Course(vector<Course>& List);
void editCourse(vector<Course>& List);
void sortList(vector<Course>& List);
#endif