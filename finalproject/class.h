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
void addonestudent(vector<student>& stL);//add new student one by one
void findstudentincourse(vector<student> stL, int id, int& check, student& st);//find and show information of a student that has the given id.
void createnewclass(vector<student>& stL, int& n);//Input new data of new class or reinput all data of the existing class.
void loadfile(ifstream& fload, vector<student>& stL);//load from csv file.
void importtoprogram(vector<student>&stL, string flname);//load the class that have the given name.
void display1student(student st);//view student of one class.
void displayclass(vector<student> stL);//view one class.
void displayallclassincourse(vector<student>stL);//view all the class in course
void editinganexistingstudent(student &st);//change the information of a student that has the given id.
void updateeditedstudentinallhisorherclasses(vector<student>stL, int id, student st);//update the change of the information of a student
                                                                                    //that has the given id in all his/her classes.
void removestudentfromclass(vector<student> &stL, int id, string classname);//remove a student that has the given id in one of his/her classed 
                                                                    //or in all of his/her classes
void removestudentfromallclass(vector<student>stL, int id);
void changestudentfromclassAtoclassB(vector<student>& stLA, vector<student>& stLB, int id);//erase a student that has the given id from class A and 
                                                                                          //put into class B.
void exporttofile(ofstream& fsave, vector<student> stL);//save to csv file.
void exporrfromprogram(vector<student>stL);


#endif
