#ifndef CLASS_H_INCLUDE
#define CLASS_H_INCLUDE

#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

struct date {
	int m = 0, d = 0, y = 0;
};

struct account {
	int ID = 0, status = 0;
	string password;
};

struct student {
	int No = 0, id = 0;;
	string Lastname, Firstname;
	char gender = '0';
	date DoB;
	account acc;
};
struct clss {
	vector<student> stL;
};

int MaxDayInMonth(int month, int year);

//add new student one by one
void AddOneStudent(vector<student>& stL);

 //find and show information of a student that has the given id in the course.
//(if thar student study in more than 1 class->show information more than one time)
void FindStudentInAllClass(vector<student>& stL, int id, int& check, student& st, string& classname, int& count);

//Input new data of new class or reinput all data of the existing class.
void CreateNewClass(vector<student>& stL, int& n);

//load from csv file.
void LoadFromCSVFile(ifstream& fload, vector<student>& stL);

//do the import action with the csv file that has the given name.
void ImportToProgram(vector<student>&stL, string flname);

//view information of 1 student.
void DisPlay1Student(student st);

//VIEW INFORMATION OF 1 STUDENT LINE BY LINE.
void DisPlay1StudentLine(student st);

//view one class.
void DisPlayClass(vector<student> stL);

//VIEW ONG CLASS LINE BY LINE.
void DisPlayClassLine(vector<student> stL);

//view all the class in course.
void DisPlayAllClass(vector<student>stL);

//VIEW ALL THE CLASS IN COURSE LINE BY LINE.
void DisPlayAllClassLine(vector<student>stL);

//change the information of a student that has the given id.
void Edit1Student(student &st);

// update the change of the information of a student that has the given id in his/her class.
void UpateIn1Class(vector<student>& stL, int No, student st);

//update the change of the information of a student that has the given id in all his/her classes.
void UpateInAllClass(vector<student>& stL, int id, student st);

//remove a student that has the given id in the class has the given class's name.
void RemoveStudentFrom1Class(vector<student> &stL, int id, string classname);
//remove a student in all of his / her classes.
void RemoveStudentFromAllClass(vector<student>stL, int id);

//erase a student that has the given id from class A and put into class B.
void ChangeStudentFromClassAToClassB(vector<student>& stLA, vector<student>& stLB, int No, int& check, int id);

//save to csv file.
void ExportToCSVFile(ofstream& fsave, vector<student> stL);

//do the save to csv file.
void ExportFromProgram(vector<student>stL, string fsname);

//find a student that has the given id in just only the class that has class's name given.
void FindStudentIn1Class(vector<student> stL, int id, string classname, int& check, student& st, int& count);

//load from dat file.
void LoadFromDATFile(ifstream& fload, vector<student>& stL);

//do the load action.
void ImportToProgram2(vector<student>& stL, string flname);

//save to dat file.
void SaveToDATFile(ofstream& fsave, vector<student> stL);

//do the save to dat file.
void ExportFromProgram2(vector<student> stL, string fsname);

//sort the class in ascending order.
void SortClassInAscendingOrderByID(vector<student>& stL);

//Check if the account has existed or not.
int checkaccounteon(student st);

//Write a new account to data.
void pushbacktoaccfile(student& st);
//load the file which is holding all accounts's data.
void loadaccsavefile(ifstream& fload, vector<account>& accL);

//save all accounts's data to file.
void saveaccount(ofstream& fsave, vector<account> accL);

//Reactivate the disabled account.
void activeacccount(student st);

//disable the account has the ID of student who has already been remove.
void disableaccount(student st);


//CLASS MANAGE MENU.
void ManageClassFunction();

#endif
