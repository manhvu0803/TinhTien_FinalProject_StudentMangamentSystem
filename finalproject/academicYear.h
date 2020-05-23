#ifndef ACADEMICYEAR_H_INCLUDE
#define ACADEMICYEAR_H_INCLUDE

#include "semester.h"
#include "utility.h"
void academicYearMenu(int mode);
void outputYear(tt::vector<string>& year);
void scanYear(string filePath, tt::vector<string>& year);
void changeToSemester(tt::vector<string>& year, int mode);
void sortYear(tt::vector<string>& year);
void createYear(string filePath, tt::vector<string>& year);
void saveYear(string filePath, tt::vector<string>& year);
void deleteYear(string filePath, tt::vector<string>& year);
#endif  
