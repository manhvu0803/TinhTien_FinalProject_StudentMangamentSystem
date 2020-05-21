#include <iostream>
#include <ctime>
#include "scoreboard.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "dataStructure.h"
#include "utility.h"
#include "attendance.h"

using namespace std;

void ViewStudentScoreBoard(tt::vector<tt::score>& B,string year,string semester , string course) {
	tt::clearConsole();
	cout << "\n\n\t\t=====YOUR SCOREBOARD=====\n";
	for (int i = 0; i < 117; i++) {
		cout << "-";
	}
	cout << "\n";
	cout << left << setw(10) << "ID" << left << setw(10) << "Year" << left << setw(10) << "Semester" << left << setw(10) << "Course" << left << setw(7) << "Class" << left << setw(30) << "Name" << left << setw(10) << "Midterm"
		<< left << setw(10) << "Final" << left << setw(10) << "Total" << left << setw(10) << "Bonus" << endl;
	for (int i = 0; i < 117; i++) {
		cout << "-";
	}
	cout << "\n";
	for (int i = 0; i < B.size(); i++) {
		cout << left << setw(10) << B[i].id << left << setw(10) << year << left << setw(10) << semester << left << setw(10) << course << left << setw(7) << B[i].cls << left << setw(30) << B[i].studentName
			<< left << setw(10) << B[i].mid << left << setw(10) << B[i].final << left << setw(10) << B[i].total
			<< left << setw(10) << B[i].bonus << endl;
		for (int i = 0; i < 117; i++) {
			cout << "-";
		}
		cout << endl;
	}
}
void LoadClass(tt::vector<tt::student>& list, string inputpath){
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
void LoadStudent(ifstream& fin, tt::vector<tt::student>& list)
{
	tt::student A;
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
void LoadStudentCourse(ifstream& file, tt::vector<string>& course, string inputpath) {
	file.open(inputpath);
	string tmp;
	int n = 0;
	if (!file.is_open()) {
		cout << "Error";
	}
	else {
		while (getline(file, tmp)) {
			course.push_back(tmp);
		}

	}
}
void SearchCourse(string &Year,string &Semester ,string &Course) {
	ifstream file;
	int choice1, choice2, choice3, choice4;
	tt::vector<string> year;
	tt::vector<string> semester;
	tt::vector<tt::course> course;
	string inputpath;
		tt::clearConsole();
		inputpath = "./data/course/year.dat";
		LoadYearFile(inputpath, year);
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
		tt::clearConsole();
		inputpath = "./data/course/" + year[choice1] + "/semester.dat";
		LoadFile(inputpath, semester);
		cout << "Semester(s):\n";
		for (int i = 0; i < semester.size(); i++) {
			cout << "(" << i << ") " << semester[i] << endl;
		}
		cout << "Choose a semester: ";
		cin >> choice2;
		while (choice2 < -1 || choice2 >= year.size() || cin.fail()) {
			cin.clear();
			cout << "Error , try again" << endl;
			cout << "Choose a semester: ";
			cin >> choice2;
		}
	
		tt::clearConsole();
		inputpath = "./data/course/" + year[choice1] + "/" + semester[choice2] + "/course.dat";
		LoadCourseFile(course, inputpath);
		cout << "Course(s):\n";
		for (int i = 0; i < course.size(); i++) {
			cout << "(" << i << ") " << course[i].id << endl;
		}
		cout << "Choose a course: ";
		cin >> choice3;
		while (choice3 < -1 || choice3 >= course.size() || cin.fail()) {
			cin.clear();
			cout << "Error , try again" << endl;
			cout << "Choose a course: ";
			cin >> choice3;
		}
	Year = year[choice1];
	Semester = semester[choice2];
	Course = course[choice3].id;

}
void LoadFile(string inputpath, tt::vector<string> &A) {
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
	tt::vector<tt::student>Student;
	tt::vector<tt::score>Score;
	string scoreboard;
	tt::vector<int>ID;
	tt::vector<int>Select;
	int id,number,number1,decide,choice1;
	tt::student A;
	tt::score tmp;
	tt::checkIn tmp1;
	string line, last, middle, first;
	if (choice == 0) {
		fin.open(inputpath);
		if (!fin.is_open()) {
			cout << "Can't open file course " << endl;
		}
		else {
			while (fin >> id) {
				scoreboard = "./data/course/" + year +"/"+ semester +"/"+ course +"/"+ to_string(id) + ".dat";
				fin1.open(scoreboard);
				if (!fin1.is_open()) {
					cout << "Student " << id << " can't be found" << endl;
				}
				else {
					tmp.id = id;
					getline(fin1, line);
					tmp.cls = line;
					getline(fin1, line);
					tmp.studentName = line;
					fin1 >> tmp.mid;
					fin1.ignore(1);
					fin1 >> tmp.final;
					fin1.ignore(1);
					fin1 >> tmp.total;
					fin1.ignore(1);
					fin1 >> tmp.bonus;
					fin1.ignore(1);
					while (fin1 >> tmp1.cDate.y) {
						fin1.ignore(1);
						fin1 >> tmp1.cDate.m;
						fin1.ignore(1);
						fin1 >> tmp1.cDate.d;
						fin1.ignore(1);
						fin1 >> tmp1.cTime.h;
						fin1.ignore(1);
						fin1 >> tmp1.cTime.m;
						fin1.ignore(1);
						fin1 >> tmp1.cTime.s;
						fin1.ignore(1);
						tmp.chkIn.push_back(tmp1);
					}
					Score.push_back(tmp);
				}
				fin1.close();
			}
			ViewStudentScoreBoard(Score,year,semester,course);
			cout << "Do you want to export this score board ?" << endl;
			cout << "(1) Yes " << endl << "(0) No" << endl;
			cout << "Your choice : ";
			cin >> choice1;
			while (choice1 != 1 && choice1 != 0 || cin.fail()) {
				cin.clear();
				cout << "Error , try again" << endl;
				cout << "Your choice ";
				cin >> choice1;
			}
			if (choice1 == 1) {
				ExportCsv(Score,year,semester,course);
				cout << "Please check your exported scoreboard in export folder" << endl;
			}
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
			tt::clearConsole();
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
				tt::clearConsole();
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
				scoreboard = "./data/course/" + year +"/"+ semester +"/"+ course +"/"+ to_string(Select[i]) + ".dat";
				fin1.open(scoreboard);
				if (!fin1.is_open()) {
					cout << "Can't open file score" << endl;
				}
				else {
					tmp.id = id;
					getline(fin1, line);
					tmp.cls = line;
					getline(fin1, line);
					tmp.studentName = line;
					fin1 >> tmp.mid;
					fin1.ignore(1);
					fin1 >> tmp.final;
					fin1.ignore(1);
					fin1 >> tmp.total;
					fin1.ignore(1);
					fin1 >> tmp.bonus;
					fin1.ignore(1);
					while (fin1 >> tmp1.cDate.y) {
						fin1.ignore(1);
						fin1 >> tmp1.cDate.m;
						fin1.ignore(1);
						fin1 >> tmp1.cDate.d;
						fin1.ignore(1);
						fin1 >> tmp1.cTime.h;
						fin1.ignore(1);
						fin1 >> tmp1.cTime.m;
						fin1.ignore(1);
						fin1 >> tmp1.cTime.s;
						fin1.ignore(1);
						tmp.chkIn.push_back(tmp1);
					}
					Score.push_back(tmp);
				}
				fin1.close();
			}
			ViewStudentScoreBoard(Score,year,semester,course);
			cout << "Do you want to export this scoreboard ?" << endl;
			cout << "(1) Yes " << endl << "(0) No" << endl;
			cout << "Your choice : ";
			cin >> choice1;
			while (choice1 != 1 && choice1 != 0 || cin.fail()) {
				cin.clear();
				cout << "Error , try again" << endl;
				cout << "Your choice ";
				cin >> choice1;
			}
			if (choice1 == 1) {
				ExportCsv(Score, year , semester ,course);
				cout << "Please check your exported scoreboard in export folder" << endl;
			}
		}
	}
	else {
		cout << "Fail";
	}
}
void LoadCourseFile(tt::vector<tt::course>& list, string filePath)
{
	ifstream fin(filePath);
	tt::course temp;
	int number;
	string line;
	if (fin.is_open())
	{
		while (fin >> number)
		{
			temp.number = number;
			fin.ignore(1);
			getline(fin, temp.id);
			getline(fin, temp.name);
			getline(fin, temp.className);
			getline(fin, temp.lecturer);
			fin >> temp.startDate.y;
			fin >> temp.startDate.m;
			fin >> temp.startDate.d;
			fin >> temp.endDate.y;
			fin >> temp.endDate.m;
			fin >> temp.endDate.d;
			fin.ignore(1);
			getline(fin, line);
			temp.DoW = ChangeDayToNumber(line);
			fin >> temp.startTime.h;
			fin >> temp.startTime.m;
			temp.startTime.s = 0;
			fin >> temp.endTime.h;
			fin >> temp.endTime.m;
			temp.endTime.s = 0;
			fin.ignore(1);
			getline(fin, temp.room);
			list.push_back(temp);
		}
	}
	else
	{
		cout << "courses.dat not found" << endl;
		return;
	}
	fin.close();
}
void ExportCsv(tt::vector<tt::score>&B , string year, string semester, string course) {
	ofstream fout;
	string outputpath;
	outputpath = "./export/" + course + "_scoreboard.csv";
	fout.open(outputpath);
	if (!fout.is_open()) {
		cout << "Can't open file export" << endl;
	}
	else {
		fout << "ID," << "Year," << "Semester," << "Course," << "Class," << "StudentName," << "Midterm," << "Final," << "Total," << "Bonus" << endl;
		for (int i = 0; i < B.size(); i++) {
			fout << B[i].id << "," << year << "," << semester << "," << course << "," << B[i].cls << "," << B[i].studentName << ","  << B[i].mid << "," << B[i].final << "," << B[i].total << "," << B[i].bonus << endl;
		}
	}
	fout.close();
}
void ImportCsv(string importpath,tt::vector<tt::score>&B, string &year, string &semester, string &course) {
	ifstream fin;
	string trash,tmp;
	tt::score tmp2;
	fin.open(importpath);
	if (!fin.is_open()) {
		cout << "Can't open file import" << endl;
	}
	else {
		getline(fin, trash);
		while (getline(fin, tmp, ',')) {
			tmp2.id = stoi(tmp);
			getline(fin, tmp, ',');
			year = tmp;
			getline(fin, tmp, ',');
			semester = tmp;
			getline(fin, tmp, ',');
			course = tmp;
			getline(fin, tmp, ',');
			tmp2.cls = tmp;
			getline(fin, tmp, ',');
			tmp2.studentName = tmp;
			getline(fin, tmp, ',');
			tmp2.mid = stof(tmp);
			getline(fin, tmp, ',');
			tmp2.final = stof(tmp);
			getline(fin, tmp, ',');
			tmp2.total = stof(tmp);
			getline(fin, tmp);
			tmp2.bonus = stof(tmp);
			B.push_back(tmp2);
		}
	}
	fin.close();
}
void LoadYearFile(string inputpath, tt::vector<string>& A) {
	ifstream fin;
	string tmp;
	string year1, year2;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "File cannot be found";
	}
	else {
		while (getline(fin, year1,' ')) {
			getline(fin, year2);
			tmp = year1 + "-" + year2;
			A.push_back(tmp);
		}
		fin.close();
	}
}
void DecideToView(string year , string semester, string course) {
	int choice;
	string inputpath;
	tt::clearConsole();
	cout << "Do you want to view scoreboard of the whole course or only some students ?" << endl;
	cout << "(0) Whole course" << endl;
	cout << "(1) Selected Students" << endl;
	cout << "Your choice: ";
	cin >> choice;
	while (choice < 0 || choice > 1 || cin.fail()) {
		cin.clear();
		cout << "Error , try again" << endl;
		cout << "Your choice: ";
		cin >> choice;
	}
	inputpath = "./data/course/" + year + "/" + semester + "/" + course + ".dat";
	PrintStudentScore(inputpath, choice, year, semester, course);

}
void EditScore(string inputpath, string year, string semester , string course) {
	ifstream fin, fin1;
	int id,number,choice,choice1 = 0;
	tt::vector<int>ID;
	string studentfile, line;
	tt::vector<tt::score>Score;
	tt::score tmp;
	tt::checkIn tmp1;
	fin.open(inputpath);
	if (!fin.is_open()) {
		cout << "Can't edit score" << endl;
	}
	else {
		while (fin >> id) {
			ID.push_back(id);
		}
		tt::clearConsole();
		cout << "Student(s) of this course: " << endl;
		for (int i = 0; i < ID.size(); i++) {
			cout << "(" << i << ") : " << ID[i] << endl;
		}
		cout << "Enter the ordinal number of the student you want to edit score: ";
		cin >> number;
		cin.ignore(1);
		studentfile = "./data/course/" + year + "/" + semester + "/" + course + "/" + to_string(ID[number])+ ".dat";
		fin1.open(studentfile);
		if (!fin1.is_open()) {
			cout << "Can't open student file to edit" << endl;
		}
		else {
			tmp.id = id;
			getline(fin1, line);
			tmp.cls = line;
			getline(fin1, line);
			tmp.studentName = line;
			fin1 >> tmp.mid;
			fin1.ignore(1);
			fin1 >> tmp.final;
			fin1.ignore(1);
			fin1 >> tmp.total;
			fin1.ignore(1);
			fin1 >> tmp.bonus;
			fin1.ignore(1);
			while (fin1 >> tmp1.cDate.y) {
				fin1.ignore(1);
				fin1 >> tmp1.cDate.m;
				fin1.ignore(1);
				fin1 >> tmp1.cDate.d;
				fin1.ignore(1);
				fin1 >> tmp1.cTime.h;
				fin1.ignore(1);
				fin1 >> tmp1.cTime.m;
				fin1.ignore(1);
				fin1 >> tmp1.cTime.s;
				fin1.ignore(1);
				tmp.chkIn.push_back(tmp1);
			}
			Score.push_back(tmp);
		}
		fin1.close();
		ViewStudentScoreBoard(Score,year,semester,course);
		cout << "\n\nDo you want to edit this student's score ?" << endl;
		cout << "(1) Yes" << endl << "(2) No" << endl;
		cout << "Your choice : ";
		cin >> choice;
		while (choice != 1 && choice != 2 || cin.fail()) {
			cin.clear();
			cout << "Error , try again" << endl;
			cout << "Your choice : ";
			cin >> choice;
		}
		do{
			tt::clearConsole();
			if (choice == 1) {
				cout << "\nEnter the new score: " << endl;
				cout << "Midterm score : ";
				cin >> Score[0].mid;
				cin.ignore(1);
				cout << "Final score : ";
				cin >> Score[0].final;
				cin.ignore(1);
				cout << "Total score : ";
				cin >> Score[0].total;
				cin.ignore(1);
				cout << "Bonus : ";
				cin >> Score[0].bonus;
				cin.ignore(1);
				ViewStudentScoreBoard(Score,year,semester,course);
				cout << "\nDo you want to edit again ?" << endl;
				cout << "(1) Yes " << endl << "(2) No" << endl;
				cout << "Your choice: ";
				cin >> choice1;
				cin.ignore(1);
				while (choice1 != 1 && choice1 != 2 || cin.fail()) {
					cin.clear();
					cout << "Error , try again" << endl;
					cout << "Your choice : ";
					cin >> choice1;
				}
			}
		} while (choice1 == 1);
		SaveFileScore(studentfile, Score[0]);
		fin1.close();
	}
	fin.close();
}
void SaveFileScore(string outputpath, tt::score &student) {
	ofstream fout;
	fout.open(outputpath);
	if (!fout.is_open()) {
		cout << "Can't open file to save" << endl;
	}
	else {
		fout << student.cls << endl;
		fout << student.studentName << endl;
		fout << student.mid << " " << student.final << " " << student.total << " " << student.bonus << endl;
		for (int i = 0; i < student.chkIn.size(); i++) {
			fout << student.chkIn[i].cDate.y << " " << student.chkIn[i].cDate.m << " " << student.chkIn[i].cDate.d << " " <<
				student.chkIn[i].cTime.h << " " << student.chkIn[i].cTime.m << " " << student.chkIn[i].cTime.s << endl;
		}
	}
	fout.close();
}
int ChangeDayToNumber(string line) {
	if (line == "MON") {
		return 0;
	}else if (line == "TUE") {
		return 1;
	}
	else if (line == "WED") {
		return 2;
	}
	else if (line == "THU") {
		return 3;
	}
	else if (line == "FRI") {
		return 4;
	}
	else if (line == "SAT") {
		return 5;
	}
	else if(line == "SUN") {
		return 6;
	}
}
void SaveScoreFromImport(tt::vector<tt::score> &B,string year,string semester,string course) {
	string inputpath;
	tt::score temp;
	for (int i = 0; i < B.size(); i++) {
		inputpath = "./data/course/" + year + "/" + semester + "/" + course + "/" + to_string(B[i].id) + ".dat";
		LoadScoreFile(temp, inputpath);
		B[i].chkIn = temp.chkIn;
		SaveFileScore(inputpath, B[i]);
		temp.chkIn.clear();
	}
}