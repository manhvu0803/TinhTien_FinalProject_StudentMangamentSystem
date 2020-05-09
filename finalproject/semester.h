#ifndef SEMESTER_H_INCLUDE
#define SEMESTER_H_INCLUDE
#include <iostream>
#include "utility.h"
#include <string>
#include <fstream>
#include <iomanip>
//#include "course.h"
using namespace std;
void semesterMenu(int year);
void outputSemester(tt::vector<string>semester);
void scanSemester(string filePath, tt::vector<string>& semester);
void changeToCourse(int year, tt::vector<string>semester);

#endif
