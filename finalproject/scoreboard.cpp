#include <iostream>
#include <ctime>
#include "scoreboard.h"
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void ViewStudentScoreBoard1(vector<student> A,vector<score> B) {
	cout << "\n\n\t\t=====YOUR SCOREBOARD=====\n";
	for (int i = 0; i < 87; i++) {
		cout << "-";
	}
	cout << "\n";
	cout << left << setw(10) << "ID" << left << setw(7) << "Class" << left << setw(30) << "Name" << left << setw(10) << "Midterm"
		<< left << setw(10) << "Final" << left << setw(10) << "Total" << left << setw(10) << "Bonus" << endl;
	for (int i = 0; i < 87; i++) {
		cout << "-";
	}
	cout << "\n";
	for (int i = 0; i < A.size(); i++) {
		cout << left << setw(10) << A[i].id << left << setw(7) << B[i].Class << left << setw(30) << A[i].lastName + " " + A[i].firstName
			<< left << setw(10) << B[i].mid << left << setw(10) << B[i].final << left << setw(10) << B[i].bonus
			<< left << setw(10) << B[i].bonus << endl;
		for (int i = 0; i < 87; i++) {
			cout << "-";
		}
		cout << endl;
	}
}
void FindStudent(student &A, int ID) {
	ifstream fin;
	string inputpath;
	string classname;
	string choose;
	vector<student> list;
	int a;
	int check = 0;
	fin.open("data/classes/class.dat");
	if (!fin.is_open()) {
		cout << "Error" << endl;
	}
	else {
		while (fin >> classname) {
			list.clear();
			inputpath = "data/classes/" + classname + ".dat";
			LoadClass(list, inputpath);
			for (int i = 0; i < list.size(); i++) {
				if (list[i].id == ID) {
					A = list[i];
					check = 1;
					break;
				}
			}
		}
		fin.close();
	}
	if (check == 0) {
		cout << "Student can't be found" << endl;
	}
}
void LoadClass(vector<student>& list, string inputpath){
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
void LoadStudent(ifstream& fin, vector<student>& list)
{
	student A;
	string temp, line;
	while (fin >> A.number)
	{
		fin >> A.id;
		fin.ignore(1);
		getline(fin, A.lastName);
		getline(fin, A.firstName);
		getline(fin, temp);
		A.gender = temp[0];
		getline(fin, temp, ' ');
		A.DoB.y = stoi(temp);
		getline(fin, temp, ' ');
		A.DoB.m = stoi(temp);
		getline(fin, temp);
		A.DoB.d = stoi(temp);
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
void SearchCourse() {
	ifstream file;
	int choice1, choice2, choice3, choice4;
	vector<string> year;
	vector<string> semester;
	vector<course> course;
	string inputpath;

	inputpath = "data/course/year.dat";
	LoadFile(inputpath, year);
	cout << " Year(s):\n";
	for (int i = 0; i < year.size(); i++) {
		cout << "(" << i << ") " << year[i] << endl;
	}
	cout << "Choose a year: ";
	cin >> choice1;
	while (choice1 < 0 || choice1 >= year.size() || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Choose a year: ";
		cin >> choice1;
	}

	inputpath = "data/course/" + year[choice1] + "/semester.dat";
	LoadFile(inputpath, semester);
	cout << "Semester(s):\n";
	for (int i = 0; i < semester.size(); i++) {
		cout << "(" << i << ") " << semester[i] << endl;
	}
	cout << "Choose a semester: ";
	cin >> choice2;
	while (choice2 < 0 || choice2 >= year.size() || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Choose a semester: ";
		cin >> choice2;
	}

	inputpath = "data/course/" + year[choice1] +"/"+ semester[choice2] + "/course.dat";
	LoadCourseFile(course, inputpath);
	cout << "Course(s):\n";
	for (int i = 0; i < course.size(); i++) {
		cout << "(" << i << ") " << course[i].id << endl;
	}
	cout << "Choose a course: ";
	cin >> choice3;
	while (choice3 < 0 || choice3 >= course.size() || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Choose a course: ";
		cin >> choice3;
	}

	cout << "Do you want to view scoreboard of the whole course or only some students ?" << endl;
	cout << "(0) Whole course" << endl;
	cout << "(1) Selected Students" << endl;
	cout << "Your choice: ";
	cin >> choice4;
	while (choice4 < 0 || choice4 > 1 || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Your choice: ";
		cin >> choice4;
	}
	inputpath = "data/course/" + year[choice1] +"/"+ semester[choice2] + "/" +course[choice3].id + ".dat";
	PrintStudentScore(inputpath, choice4,year[choice1],semester[choice2],course[choice3].id);

}
void LoadFile(string inputpath, vector<string> &A) {
	ifstream fin;
	string tmp;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "File cannot be found";
	}
	else {
		while (getline(fin, tmp)) {
			A.push_back(tmp);
		}
		fin.close();
	}
}
void PrintStudentScore(string inputpath, int choice,string year,string semester,string course) {
	ifstream fin,fin1;
	vector<student>Student;
	vector<score> Score;
	string scoreboard;
	vector<int>ID;
	vector<int>Select;
	int id,number,number1,decide;
	student A;
	score tmp;
	student tmp1;
	string trash, last, middle, first;
	if (choice == 0) {
		fin.open(inputpath);
		if (!fin.is_open()) {
			cout << "Can't open file course " << endl;
		}
		else {
			while (fin >> id) {
				/*FindStudent(A, id);
				Student.push_back(A);*/
				scoreboard = "data/course/" + year +"/"+ semester +"/"+ course +"/"+ to_string(id) + ".dat";
				fin1.open(scoreboard);
				if (!fin1.is_open()) {
					cout << "Student " << id << " can't be found" << endl;
				}
				else {
					tmp1.id = id;
					getline(fin1, trash);
					getline(fin1, last, ' ');
					getline(fin1, middle, ' ');
					getline(fin1, first);
					tmp1.lastName = last + " " + middle;
					tmp1.firstName = first;
					Student.push_back(tmp1);
					fin1 >> tmp.mid;
					fin1.ignore(1);
					fin1 >> tmp.final;
					fin1.ignore(1);
					fin1 >> tmp.total;
					fin1.ignore(1);
					fin1 >> tmp.bonus;
					Score.push_back(tmp);
				}
				fin1.close();
			}
			ViewStudentScoreBoard1(Student, Score);
			ExportCsv(Student, Score);
		}
		fin.close();
	}
	else if (choice == 1) {
		fin.open(inputpath);
		if (!fin.is_open()) {
			cout << "Can't open file " << endl;
		}
		else {
			while (fin >> id) {
				ID.push_back(id);
			}
			cout << "Students of this course: " << endl;
			for (int i = 0; i < ID.size(); i++) {
				cout << "(" << i << ") : " << ID[i] << endl;
			}
			cout << "How many students you want to view score ? : ";
			cin >> number;
			cin.ignore();
			for (int j = 0; j < number; j++) {
				cout << "Enter ordinal number of the student : ";
				cin >> number1;
				cin.ignore();
				Select.push_back(ID[number1]);
				cout << endl;
			}
			do{
				cout << "Do you want to add someone else ? " << endl;
				cout << "(1) YES " << endl << "(2) NO" << endl;
				cout << "Your choice : ";
				cin >> decide;
				cin.ignore();
				if (decide == 1) {
					cout << "How many students you want to add more ? : ";
					cin >> number;
					cin.ignore();
					for (int j = 0; j < number; j++) {
						cout << "Enter ordinal number of the student : ";
						cin >> number1;
						cin.ignore();
						Select.push_back(ID[number1]);
						cout << endl;
					}
				}
			} while (decide == 1);
			for (int i = 0; i < Select.size();i++) {
				scoreboard = "data/course/" + year +"/"+ semester +"/"+ course +"/"+ to_string(Select[i]) + ".dat";
				fin1.open(scoreboard);
				if (!fin1.is_open()) {
					cout << "Can't open file score" << endl;
				}
				else {
					tmp1.id = ID[i];
					getline(fin1, tmp.Class);
					getline(fin1, last, ' ');
					getline(fin1, middle, ' ');
					getline(fin1, first);
					tmp1.lastName = last + " " + middle;
					tmp1.firstName = first;
					Student.push_back(tmp1);
					fin1 >> tmp.mid;
					fin1.ignore(1);
					fin1 >> tmp.final;
					fin1.ignore(1);
					fin1 >> tmp.total;
					fin1.ignore(1);
					fin1 >> tmp.bonus;
					Score.push_back(tmp);
					fin.clear();
				}
				fin1.close();
			}
			ViewStudentScoreBoard1(Student, Score);
		}
	}
	else {
		cout << "Fail";
	}
}
void LoadCourseFile(vector<course>& list, string filePath)
{
	ifstream myFile(filePath);
	string line;
	course temp;
	int number;
	if (myFile.is_open())
	{
		while (myFile >> number)
		{
			temp.number = number;
			myFile.ignore(1);
			getline(myFile, temp.id);
			getline(myFile, temp.name);
			getline(myFile, temp.className);
			getline(myFile, temp.lecturer);
			myFile >> temp.startDate.y;
			myFile >> temp.startDate.m;
			myFile >> temp.startDate.d;
			myFile >> temp.endDate.y;
			myFile >> temp.endDate.m;
			myFile >> temp.endDate.d;
			myFile >> temp.DoW;
			myFile >> temp.startTime.h;
			myFile >> temp.startTime.m;
			temp.startTime.s = 0;
			myFile >> temp.endTime.h;
			myFile >> temp.endTime.m;
			temp.endTime.s = 0;
			myFile.ignore(1);
			getline(myFile, temp.room);
			list.push_back(temp);
		}

	}
	else
	{
		cout << "courses.dat not found" << endl;
		return;
	}
	myFile.close();
}
void ExportCsv(vector<student>A,vector<score>B) {
	ofstream fout;
	fout.open("export/scoreboard.csv");
	if (!fout.is_open()) {
		cout << "Can't open file export" << endl;
	}
	else {
		fout << "ID," << "Class," << "LastName," << "FirstName," << "Midterm," << "Final," << "Total," << "Bonus" << endl;
		for (int i = 0; i < A.size(); i++) {
			fout << A[i].id << "," << B[i].Class << "," << A[i].lastName << "," << A[i].firstName << "," << B[i].mid << "," << B[i].final << "," << B[i].bonus << "," << B[i].bonus << endl;
		}
	}
	fout.close();
}
void ImportCsv(vector<student>&A, vector<score>&B) {
	ifstream fin;
	string trash,tmp;
	student tmp1;
	score tmp2;
	fin.open("import/scoreboard.csv");
	if (!fin.is_open()) {
		cout << "Can't open file import" << endl;
	}
	else {
		getline(fin, trash);
		while (getline(fin, tmp, ',')) {
			tmp1.id = stoi(tmp);
			getline(fin, tmp, ',');
			tmp2.Class = tmp;
			getline(fin, tmp, ',');
			tmp1.lastName = tmp;
			getline(fin, tmp, ',');
			tmp1.firstName = tmp;
			getline(fin, tmp, ',');
			tmp2.mid = stof(tmp);
			getline(fin, tmp, ',');
			tmp2.final = stof(tmp);
			getline(fin, tmp, ',');
			tmp2.total = stof(tmp);
			getline(fin, tmp);
			tmp2.bonus = stof(tmp);
			A.push_back(tmp1);
			B.push_back(tmp2);
		}
	}
	fin.close();
}