#ifndef _ATTENDANCE_H_INCLUDED_
#define _ATTENDANCE_H_INCLUDED_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dataStructure.h"
#include "utility.h"

using namespace std;


int CompareDate(tt::date A, tt::date B);
int SubtractDate(tt::date before, tt::date after);
int CompareTime(tt::time A, tt::time B);
bool isInTime(tt::checkIn student, tt::course study);
void SaveCheckInTime(tt::checkIn& student);
void FindStudent(tt::student& A, int ID, string& course);
void CheckIn();
void ViewAttendanceList(tt::vector<tt::score>& A, string course);
void FindStudentCourse(int id, string coursename, tt::vector<string>& rightcourse, tt::vector<tt::course>& coursestudent);
bool CheckStudentExist(int id, string inputpath);
void LoadScoreFile(tt::score& student, string inputpath);
void CheckAttendance(string year, string semester, string course, tt::date Date, tt::vector<tt::score>& A);
#endif _ATTENDANCE_H_INCLUDED_
