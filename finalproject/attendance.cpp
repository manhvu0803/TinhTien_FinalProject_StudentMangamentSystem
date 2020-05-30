#include <iostream>
#include <ctime>
#include "attendance.h"
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include "scoreboard.h"
//#include "scoreboard.h"

using namespace std;
int CompareDate(tt::date A, tt::date B) {
	if (A.y < B.y) {
		return 1;
	}
	else if (A.y > B.y) {
		return -1;
	}
	else {
		if (A.m < B.m) {
			return 1;
		}
		else if (A.m > B.m) {
			return -1;
		}
		else {
			if (A.d < B.d) {
				return 1;
			}
			else if (A.d > B.d) {
				return -1;
			}
			else {
				return 0;
			}
		}
	}
}
int SubtractDate(tt::date before, tt::date after) {
	int result = 0;
	for (int i = before.y; i < after.y; i++) {
		if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
			result = result + 366;
		}
		else {
			result = result + 365;
		}
	}
	for (int i = 1; i < before.m; i++) {
		switch (i) {
		case 2: {
			if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
				result = result - 29;
			}
			else {
				result = result - 28;
			}
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11: {
			result = result - 30;
			break;
		}
		default: {
			result = result - 31;
		}
		}
	}
	for (int i = 1; i < after.m; i++) {
		switch (i) {
		case 2: {
			if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) {
				result = result + 29;
			}
			else {
				result = result + 28;
			}
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11: {
			result = result + 30;
			break;
		}
		default: {
			result = result + 31;
		}
		}
	}
	result = result + after.d - before.d;
	return result;
}
int CompareTime(tt::time A,tt::time B) {
	if (A.h < B.h) {
		return 1;
	}
	else if (A.h > B.h) {
		return -1;
	}
	else if (A.m < B.m) {
		return 1;
	}
	else if (A.m > B.m) {
		return -1;
	}
	else if (A.s < B.s) {
		return 1;
	}
	else if (A.s > B.s) {
		return -1;
	}
	else {
		return 0;
	}
}
bool isInTime(tt::checkIn student,tt::course study) {
	if (CompareDate(student.cDate, study.startDate) == 1 || CompareDate(student.cDate, study.endDate) == -1) {
		return false;
	}
	else if (SubtractDate(student.cDate, study.startDate) % 7 != 0) {
		return false;
	}
	else if (CompareTime(student.cTime,study.startTime) == 1 || CompareTime(student.cTime,study.endTime) == -1) {
		return false;
	}
	else {
		return true;
	}
}
void SaveCheckInTime(tt::checkIn& student) {
	time_t now = time(0);
	tm* ltm = localtime(&now);

	student.cDate.y = 1900 + ltm->tm_year;
	student.cDate.m = 1 + ltm->tm_mon;
	student.cDate.d = ltm->tm_mday;
	student.cTime.h = ltm->tm_hour;
	student.cTime.m = ltm->tm_min;
	student.cTime.s = ltm->tm_sec;
}
void FindStudent(tt::student& A, int ID , string &course) {
	ifstream fin;
	string inputpath;
	string classname;
	string choose;
	tt::vector<tt::student> list;
	tt::vector<string> courses;
	int a,choice;
	int check = 0;
	fin.open("./data/classes/class.dat");
	if (!fin.is_open()) {
		cout << "Error" << endl;
	}
	else {
		while (fin >> classname) {
			list.clear();
			inputpath = "./data/classes/" + classname + ".dat";
			LoadClass(list, inputpath);
			for (int i = 0; i < list.size(); i++) {
				if (list[i].id == ID) {
					A = list[i];
					check = 1;
					break;
				}
			}
			if (check == 1) {
				inputpath = "./data/classes/" + classname + to_string(A.id) + ".dat";
				LoadFile(inputpath, courses);
				cout << "The course(s) you are in :" << endl;
				for (int i = 0; i < courses.size(); i++) {
					cout << "(" << i << ") : " << courses[i] << endl;
				}
				cout << "Which course you want to check in? : ";
				cin >> choice;
				while (choice < 0 || choice >= courses.size() || cin.fail()) {
					cin.clear();
					cout << "Error , try again" << endl;
					cout << "Choose a course: ";
					cin >> choice;
				}
				course = courses[choice];
				break;
			}
		}
		fin.close();
	}
	if (check == 0) {
		cout << "Student can't be found" << endl;
	}
}
void CheckIn() {
	int id,choice,same = 0;
	string inputpath;
	tt::vector<string> linkcourse;
	string studentcourse;
	tt::student A;
	tt::checkIn studenttime;
	tt::score student;
	tt::vector<tt::course> coursestudent;
	cout << "Enter your student's ID : ";
	cin >> id;
	FindStudent(A, id, studentcourse);
	FindStudentCourse(id, studentcourse, linkcourse, coursestudent);
	if (linkcourse.size() > 1) {
		cout << "We have " << linkcourse.size() << "course(s)" << endl;
		for (int i = 0; i < linkcourse.size(); i++) {
			cout << "(" << i << "): " << linkcourse[i] << endl;
		}
		cout << "Your choice: ";
		cin >> choice;
		inputpath = linkcourse[choice] + "/" + to_string(id) + ".dat";
		SaveCheckInTime(studenttime);
		LoadScoreFile(student, inputpath);
		if (isInTime(studenttime,coursestudent[choice])) {
			for (int i = 0; i < student.chkIn.size(); i++) {
				if (studenttime.cDate.y == student.chkIn[i].cDate.y && 
						studenttime.cDate.m == student.chkIn[i].cDate.m && 
							studenttime.cDate.d == student.chkIn[i].cDate.d) {
					same = 1;
					break;
				}
			}
			if (same == 0) {
				student.chkIn.push_back(studenttime);
				SaveFileScore(inputpath, student);
				cout << "Successfully check in" << endl;
			}
			else {
				cout << "You have checked in before" << endl;
			}
		}
		else {
			cout << "You can't check in " << endl;
		}
	}
	else {
		inputpath = linkcourse[0] + "/" + to_string(id) + ".dat";
		SaveCheckInTime(studenttime);
		LoadScoreFile(student, inputpath);
		if (isInTime(studenttime, coursestudent[0])) {
			for (int i = 0; i < student.chkIn.size(); i++) {
				if (studenttime.cDate.y == student.chkIn[i].cDate.y &&
					studenttime.cDate.m == student.chkIn[i].cDate.m &&
					studenttime.cDate.d == student.chkIn[i].cDate.d) {
					same = 1;
					break;
				}
			}
			if (same == 0) {
				student.chkIn.push_back(studenttime);
				SaveFileScore(inputpath, student);
				cout << "Successfully check in" << endl;
			}
			else {
				cout << "You have checked in before" << endl;
			}
		}
		else {
			cout << "You can't check in " << endl;
		}
	}
}
void ViewAttendanceList(tt::vector<tt::score>& A , string course) {
	tt::clearConsole();
	cout << "\n\n\t\t=====YOUR SCOREBOARD=====\n";
	for (int i = 0; i < 79; i++) {
		cout << "-";
	}
	cout << "\n";
	cout << left << setw(10) << "ID" << left << setw(7) << "Class" << left << setw(30) << "Name" << left << setw(8) << "Course" << left << setw(11) << "Date"
		<< left << setw(13) << "Check-in Time" << endl;
		;
	for (int i = 0; i < 79; i++) {
		cout << "-";
	}
	cout << "\n";
	for (int i = 0; i < A.size(); i++) {
		cout << left << setw(10) << A[i].id << left << setw(7) << A[i].cls << left << setw(30) << A[i].studentName
			<< left << setw(8) << course << left << setw(11) << A[i].chkIn[0].cDate.y << "/" << A[i].chkIn[0].cDate.m << "/" << A[i].chkIn[0].cDate.d 
			<< left << setw(13) << A[i].chkIn[0].cTime.h << ":" << A[i].chkIn[0].cTime.m << ":" << A[i].chkIn[0].cTime.s << endl;
		for (int i = 0; i < 79; i++) {
			cout << "-";
		}
		cout << endl;
	}
}
void FindStudentCourse(int id, string coursename , tt::vector<string>& rightcourse, tt::vector<tt::course> &coursestudent) {
	ifstream fin,fin1, fin2, fin3, fin4;
	string year, semester, course, inputpath;
	string year1, year2,tmp;
	tt::vector<tt::course> courses;
	
	bool check;
	inputpath = ".dat/course/year.dat";
	fin.open(inputpath);
	if (fin.is_open()) {
		while (getline(fin, year1, ' ')) {
			getline(fin, year2);
			year = year1 + '-' + year2;
			inputpath = ".dat/course/" + year + "/semester.dat";
			fin1.open(inputpath);
			if (fin1.is_open()) {
				while (getline(fin1, semester)) {
					inputpath = ".dat/course/" + year + "/" + semester + "/course.dat";
					LoadCourseFile(courses, inputpath);
					for (int i = 0; i < courses.size(); i++) {
						if (courses[i].id == course) {
							inputpath = ".dat/course/" + year + "/" + semester + "/" + course[i] + ".dat";
							check = CheckStudentExist(id, inputpath);
							if (check) {
								coursestudent.push_back(courses[i]);
								tmp = ".dat/course/" + year + "/" + semester + "/" + course;
								rightcourse.push_back(tmp);
							}
						}
					}
					
				}
				fin1.close();
			}
			else {
				cout << "Can't open file year" << endl;
			}
		}
		fin.close();
	}
	else {
		cout << "Can't open year.dat" << endl;
	}

}
bool CheckStudentExist(int id, string inputpath) {
	ifstream fin;
	int tmp;
	fin.open(inputpath);
	if (fin.is_open()) {
		while (fin >> tmp) {
			if (tmp == id) {
				return true;
			}
		}
		fin.close();
	}
	else {
		cout << "Can't open file course to check student" << endl;
	}
	return false;
}
void LoadScoreFile(tt::score &student, string inputpath) {
	ifstream fin;
	string line;
	tt::checkIn tmp1;
	fin.open(inputpath);
	if (fin.is_open()) {
		    getline(fin, line);
			student.cls = line;
			getline(fin, line);
			student.studentName = line;
			fin >> student.mid;
			fin.ignore(1);
			fin >> student.final;
			fin.ignore(1);
			fin >> student.total;
			fin.ignore(1);
			fin >> student.bonus;
			fin.ignore(1);
			while (fin >> tmp1.cDate.y) {
				fin.ignore(1);
				fin >> tmp1.cDate.m;
				fin.ignore(1);
				fin >> tmp1.cDate.d;
				fin.ignore(1);
				fin >> tmp1.cTime.h;
				fin.ignore(1);
				fin >> tmp1.cTime.m;
				fin.ignore(1);
				fin >> tmp1.cTime.s;
				fin.ignore(1);
				student.chkIn.push_back(tmp1);
			}
		    fin.close();
	} else {
		cout << "Can't open score file" << endl;
	}
}
void CheckAttendance(string year,string semester,string course , tt::date Date,tt::vector<tt::score> &A) {
	ifstream fin,fin1;
	int id,same = 0;
	string inputpath;
	tt::score student;
	inputpath = ".data/course/" + year + "/" + semester + "/" + course + ".dat";
	fin.open(inputpath);
	if (fin.is_open()) {
		while (fin >> id) {
			inputpath =  ".data/course/" + year + "/" + semester + "/" + course + "/" + to_string(id) + ".dat";
			LoadScoreFile(student, inputpath);
			for (int i = 0; i < student.chkIn.size(); i++) {
				if (Date.y == student.chkIn[i].cDate.y &&
					Date.m == student.chkIn[i].cDate.m &&
					Date.d == student.chkIn[i].cDate.d) {
					same = 1;
					break;
				}
			}
			if (same == 1) {
				A.push_back(student);
			}
		}
	}
	else {
		cout << "Can't open file to check attendance" << endl;
	}
}