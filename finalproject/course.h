#ifndef COURSE_H_INCLUDE
#define COURSE_H_INCLUDE

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
struct Course {
	int No;
	string Id, Name, Class, Account, startDate, endDate, DoW, startHour, endHour, Room;
};
void scanCourse(ifstream& myFile, vector<Course>& List);
void saveCourse(ofstream& myFile, vector<Course>List);
void input1Course(vector<Course>& List);
void inputCourse(vector<Course>& List, int& n);
void outputCourse(vector<Course> List);
#endif