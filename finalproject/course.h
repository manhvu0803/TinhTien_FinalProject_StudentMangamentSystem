#ifndef COURSE_H_INCLUDE
#define COURSE_H_INCLUDE

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
struct Course {
	int No;
	string Id, Name, Class, Account, startDate, endDate, DoWTheory, startHourTheory, endHourTheory, Room, DoWExcercise, startHourExcercise, endHourExcercise;

};
void scanCourse( vector<Course>& List);
void saveCourse( vector<Course>List);
void input1Course(vector<Course>& List);
void inputCourse(vector<Course>& List, int& n);
void output1Course(Course course);
void outputCourse(vector<Course> List);
void delete1Course(vector<Course>& List, int n);
void editCourse(vector<Course>& List, int n);
void sortList(vector<Course>& List);
#endif