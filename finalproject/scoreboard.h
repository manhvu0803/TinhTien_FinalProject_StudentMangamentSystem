#ifndef _SCOREBOARD_H_INCLUDED_
#define _SCOREBOARD_H_INCLUDED_
#include <iostream>
#include <fstream>
#include <string>
#include "dataStructure.h"
#include "utility.h"
using namespace std;

void ViewStudentScoreBoard(tt::vector<tt::score> &B);
void LoadClass(tt::vector<tt::student>& list, string inputpath);
void LoadStudent(ifstream& fin, tt::vector<tt::student>& list);
void LoadStudentCourse(ifstream& file, tt::vector<string>& course, string inputpath);
void SearchCourse(string& Year, string& Semester, string& Course);
void LoadFile(string inputpath, tt::vector<string>& A);
void PrintStudentScore(string inputpath, int choice, string year, string semester, string course);
void LoadCourseFile(tt::vector<tt::course>& list, string filePath);
void ExportCsv(tt::vector<tt::score>&B,string course);
void ImportCsv(string importpath,tt::vector<tt::score>& B);
void LoadYearFile(string inputpath, tt::vector<string>& A);
void DecideToView(string year, string semester, string course);
void EditScore(string inputpath, string year, string semester, string course);
void SaveFileScore(string outputpath, tt::score&student);
int ChangeDayToNumber(string line);
#endif _SCOREBOARD_H_INCLUDED_
