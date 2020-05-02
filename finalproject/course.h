#ifndef COURSE_INCLUDE_H_
#define COURSE_INCLUDE_H_
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "class.h"
#include "dataStructure.h"
using namespace std;
void courseMenu(int year, string semester);
void loadCsvFile(tt::vector<tt::course>& list, string filePath);
void loadDatFile(tt::vector<tt::course>& list, string filePath);
void loadCourseStudentFile(tt::course& Course, string filePath);
void saveCourseList(tt::vector<tt::course> list, string filePath);
void saveCourseStudentFile(tt::course Course, string filePath);
void importCsvFile(tt::vector<tt::course>& list, string filePath);
void output1Course(tt::course Course);
void outputCourseList(tt::vector<tt::course> list);
void output1CourseData(tt::course Course);
void outputSchedule(tt::vector<tt::course> list);
int  inputTime(tt::time& courseTime);
int  inputDate(tt::date& Date);
void input1Course(tt::course& newCourse);
void inputCourse(tt::vector<tt::course>& list, string filePath);
void editCourse(tt::vector<tt::course>& list, string filePath);
void deleteCourse(tt::vector<tt::course>& list, string filePath);
void remove1Student(tt::course& Course);
void add1Student(tt::course& Course);
void addStudent(tt::course& Course);
void viewStudentList(tt::course courseName);
void sortList(tt::vector<tt::course>& List);
void upperCase(string& name);
tt::student searchStudent(int id);
tt::course searchCourse(string filePath, string Id);

#endif