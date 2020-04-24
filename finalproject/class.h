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
	int month = 0, day = 0, year = 0;
};

struct student {
	int No = 0, id = 0;;
	string Lastname, Firstname;
	char gender = '0';
	date DoB;
};
struct clss {
	vector<student> stL;
};

int maxdayinmonth(int month, int year);

//add new student one by one
void addonestudent(vector<student>& stL);

 //find and show information of a student that has the given id in the course.
//(if thar student study in more than 1 class->show information more than one time)
void findstudentinexistingclasses(vector<student>& stL, int id, int& check, student& st, string& classname);

//Input new data of new class or reinput all data of the existing class.
void createnewclass(vector<student>& stL, int& n);

//load from csv file.
void loadfromcsvfile(ifstream& fload, vector<student>& stL);

//do the import action with the csv file that has the given name.
void importtoprogram(vector<student>&stL, string flname);

//view information of 1 student.
void display1student(student st);

//VIEW INFORMATION OF 1 STUDENT LINE BY LINE.
void display1studentline(student st);

//view one class.
void displayclass(vector<student> stL);

//VIEW ONG CLASS LINE BY LINE.
void displayclassline(vector<student> stL);

//view all the class in course.
void displayallclassincourse(vector<student>stL);

//VIEW ALL THE CLASS IN COURSE LINE BY LINE.
void displayallclassincourseline (vector<student>stL);

//change the information of a student that has the given id.
void editinganexistingstudent(student &st);

//update the change of the information of a student that has the given id in all his/her classes.
void updateeditedstudentinallhisorherclasses(vector<student>& stL, int& id, student& st);

//remove a student that has the given id in the class has the given class's name.
void removestudentfromclass(vector<student> &stL, int id, string classname);
//remove a student in all of his / her classes.
void removestudentfromallclass(vector<student>stL, int id);

//erase a student that has the given id from class A and put into class B.
void changestudentfromclassAtoclassB(vector<student>& stLA, vector<student>& stLB, int id, int& check);

//save to csv file.
void exporttofile(ofstream& fsave, vector<student> stL);

//do the save to csv file.
void exporrfromprogram(vector<student>stL, string fsname);

//find a student that has the given id in just only the class that has class's name given.
void findstudentin1class(vector<student> stL, int id, string classname, int& check, student& st);

//load from dat file.
void loadfromdatfile(ifstream& fload, vector<student>& stL);

//do the load action.
void importtoprogram2(vector<student>& stL, string flname);

//save to dat file.
void savetodatfile(ofstream& fsave, vector<student> stL);

//do the save to dat file.
void exportfromprogram2(vector<student> stL, string fsname);

//Old menu.
void manageclassfunctionold();

//Menu update.
void manageclassfunctionnew();

#endif
