#include <iostream>
#include <ctime>
#include "scoreboard.h"
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void ViewStudentScoreBoard(Student A) {
	cout << "\n\n\t\t=====YOUR SCOREBOARD=====\n";
	for (int i = 0; i < 62; i++) {
		cout << "-";
	}
	cout << "\n";
	cout << left << setw(10) << "ID" << left << setw(30) << "Name" << left << setw(7) << "Midterm"
		<< left << setw(5) << "Final" << left << setw(5) << "Total" << left << setw(5) << "Bonus" << endl;
	for (int i = 0; i < 62; i++) {
		cout << "-";
	}
	cout << "\n";
	cout << left << setw(10) << A.ID << left << setw(30) << A.LastName << " " << A.MiddleName << " " <<A.FirstName 
		<< left << setw(7) << A.Grade.Midtern << left << setw(5) << A.Grade.Final << left << setw(5) << A.Grade.Total 
		<< left << setw(5) << A.Grade.Bonus << endl;
	for (int i = 0; i < 62; i++) {
		cout << "-";
	}
}
void FindStudent(vector<Student>& list, Student &A, int ID, int choice, vector<string> &course) {
	ifstream fin;
	string inputpath;
	string classname;
	string choose;
	int a;
	int check = 0;
	fin.open("/data/classes/class.dat");
	if (!fin.is_open()) {
		cout << "Error" << endl;
	}
	else {
		while (fin >> classname) {
			list.clear();
			inputpath = "/data/classes /" + classname + ".dat";
			LoadClass(list, inputpath);
			for (int i = 0; i < list.size; i++) {
				if (list[i].ID == ID) {
					A = list[i];
					check = 1;
					break;
				}
			}
			if (check == 1) {
				inputpath = "/data/classes" + classname + "/" + to_string(ID) + ".dat";
				LoadStudentCourse(fin, course, inputpath);
				break;
			}
		}
		cout << "This student course : " << endl;
		for (int i = 0; i < course.size; i++) {
			cout << "(" << i << ")" << " : " << course[i] << endl;
		}
		cout << "Choose course you want to find your score : ";
		cin >> choose;
		a = stoi(choose);

	}
}
void LoadClass(vector<Student>& list, string inputpath){
	ifstream fin;
	fin.open(inputpath);
	if (!fin.is_open())
	{
		cout << "Error" << endl;
	}
	else
	{
		LoadStudent(fin, list);
		fin.close();
	}
}
void LoadStudent(ifstream& fin, vector<Student>& list)
{
	Student A;
	string temp, line;
	while (fin >> A.No)
	{
		fin >> A.ID;
		getline(fin, A.LastName);
		getline(fin, A.LastName);
		getline(fin, A.FirstName);
		getline(fin, temp);
		A.Gender = temp[0];
		getline(fin, temp, ' ');
		A.Birth.year = stoi(temp);
		getline(fin, temp, ' ');
		A.Birth.month = stoi(temp);
		getline(fin, temp);
		A.Birth.day = stoi(temp);
		list.push_back(A);
	}
}
void LoadStudentCourse(ifstream& file, vector<string>& course, string inputpath) {
	file.open(inputpath);
	string tmp;
	int n = 0;
	if (!file.is_open()) {
		cout << "Error";
	}
	else {
		while (getline(file, tmp)) {
			course[n] = tmp;
			n++;
		}

	}
}
