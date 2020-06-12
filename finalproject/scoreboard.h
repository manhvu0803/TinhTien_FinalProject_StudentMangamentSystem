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
void LoadFile(string inputpath, tt::vector<string>& A);
void PrintStudentScore(string inputpath, int choice, string year, string semester, string course);
void LoadCourseFile(tt::vector<tt::course>& list, string filePath);
void ExportCsv(tt::vector<tt::score>&B,string year , string semester ,string course);
void ImportCsv(tt::vector<tt::score>& B , string &year, string &semester, string &course , int &check, string importpath);
void LoadYearFile(string inputpath, tt::vector<string>& A);
void DecideToView(string year, string semester, string course);
void EditScore(string inputpath, string year, string semester, string course);
void SaveFileScore(string outputpath, tt::score&student);
int ChangeDayToNumber(string line);
void SaveScoreFromImport(tt::vector<tt::score> &B, string year, string semester, string course);
void ViewScoreForStudent(int id);
void ExportCsvForStudent(tt::score& student, string course);
void MoveToYear(string& Year);
void MoveToSemester(string& Semester, string Year);
void ChooseCourse(string Year, string Semester, string& Course, int type, string lecturer);
int MainForScoreboardandAttendance(string information, int type);
#endif _SCOREBOARD_H_INCLUDED_
