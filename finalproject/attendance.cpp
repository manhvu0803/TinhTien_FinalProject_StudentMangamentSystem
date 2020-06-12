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
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
			result = result + 366;
		}
		else {
			result = result + 365;
		}
	}
	for (int i = 1; i < before.m; i++) {
		switch (i) {
		case 2: {
			if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
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
			if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
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
void FindStudent(tt::student& A, int ID , string &course , int &check) {
	ifstream fin;
	string inputpath;
	string classname;
	string choose;
	tt::vector<tt::student> list;
	tt::vector<string> courses;
	int choice;
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
				inputpath = "./data/classes/" + classname + "/" + to_string(A.id) + ".dat";
				LoadFile(inputpath, courses);
				cout << "The course(s) you are in :" << endl;
				for (int i = 0; i < courses.size(); i++) {
					cout << "(" << i << ") : " << courses[i] << endl;
				}
				cout << "Which course you want to choose? : ";
				cin >> choice;
				while (choice < 0 || choice >= courses.size() || cin.fail()) {
					cin.clear();
					cin.ignore(256, '\n');
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
void CheckIn(int id) {
	int choice, same = 0, return1 = 0 , check = 0;
	string inputpath;
	tt::vector<string> linkcourse;
	string studentcourse;
	tt::student A;
	tt::checkIn studenttime;
	tt::score student;
	tt::vector<tt::course> coursestudent;
	do{
		tt::clearConsole();
		FindStudent(A, id, studentcourse,check);
		FindStudentCourse(id, studentcourse, linkcourse, coursestudent);
		if (linkcourse.size() > 1) {
			cout << "We have " << linkcourse.size() << "course(s)" << endl;
			for (int i = 0; i < linkcourse.size(); i++) {
				cout << "(" << i << "): " << linkcourse[i] << endl;
			}
			cout << "Your choice: ";
			cin >> choice;
			while (choice < 0 || choice >= linkcourse.size() || cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error , try again" << endl;
				cout << "Choose a course: ";
				cin >> choice;
			}
			inputpath = linkcourse[choice] + "/" + to_string(id) + ".dat";
			LoadScoreFile(student, inputpath);
				SaveCheckInTime(studenttime);
				if (isInTime(studenttime, coursestudent[choice])) {
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
					cout << "This course is from " << coursestudent[choice].startTime.h << ':' << coursestudent[choice].startTime.h;
					cout << " to " << coursestudent[choice].endTime.h << ':' << coursestudent[choice].endTime.h << '\n';
				}
		}
		else {
			inputpath = linkcourse[0] + "/" + to_string(id) + ".dat";
			LoadScoreFile(student, inputpath);
				SaveCheckInTime(studenttime);
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
		student.chkIn.clear();
		linkcourse.clear();
		coursestudent.clear();
		check = 0;
		cout << "Press (-1) to return or (0) to exit " << endl;
		cout << "Your choice : ";
		cin >> return1;
		while (return1 < -1 || return1 > 0 || cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error , try again" << endl;
			cout << "Your choice : ";
			cin >> return1;
		}
	} while (return1 == -1);
}
void ViewAttendanceList(tt::vector<tt::score>& A , string course) {
	tt::clearConsole();
	cout << "\n\n\t\t=====YOUR ATTENDANCE LIST=====\n";
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
			<< left << setw(8) << course << left << setw(11) << to_string(A[i].chkIn[0].cDate.y) + "/" + to_string(A[i].chkIn[0].cDate.m) + "/" + to_string(A[i].chkIn[0].cDate.d)
			<< left << setw(13) << to_string(A[i].chkIn[0].cTime.h) + ":" + to_string(A[i].chkIn[0].cTime.m) + ":" + to_string(A[i].chkIn[0].cTime.s) << endl;
		for (int i = 0; i < 79; i++) {
			cout << "-";
		}
		cout << endl;
	}
}
void FindStudentCourse(int id, string coursename , tt::vector<string>& rightcourse, tt::vector<tt::course> &coursestudent) {
	ifstream fin,fin1, fin2, fin3, fin4;
	string year, semester, inputpath,tmp;
	tt::vector<tt::course> courses;

	bool check;
	inputpath = "./data/course/year.dat";
	fin.open(inputpath);
	if (fin.is_open()) {
		while (getline(fin, year)) {
			inputpath = "./data/course/" + year + "/semester.dat";
			fin1.open(inputpath);
			if (fin1.is_open()) {
				while (getline(fin1, semester)) {
					inputpath = "./data/course/" + year + "/" + semester + "/course.dat";
					LoadCourseFile(courses, inputpath);
					for (int i = 0; i < courses.size(); i++) {
						if (courses[i].id == coursename) {
							inputpath = "./data/course/" + year + "/" + semester + "/" + courses[i].id + ".dat";
							check = CheckStudentExist(id, inputpath);
							if (check) {
								coursestudent.push_back(courses[i]);
								tmp = "./data/course/" + year + "/" + semester + "/" + courses[i].id;
								rightcourse.push_back(tmp);
								break;
							}
						}
					}
					courses.clear();

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
void CheckAttendance(string year,string semester,string course , tt::date Date,tt::vector<tt::score> &A , int& check) {
	ifstream fin,fin1;
	int id,same = 0;
	string inputpath;
	tt::score student;
	tt::score addstudent;
	inputpath = "./data/course/" + year + "/" + semester + "/" + course + ".dat";
	fin.open(inputpath);
	if (fin.is_open()) {
		while (fin >> id) {
			same = 0;
			inputpath = "./data/course/" + year + "/" + semester + "/" + course + "/" + to_string(id) + ".dat";
			LoadScoreFile(student, inputpath);
			for (int i = 0; i < student.chkIn.size(); i++) {
				if (Date.y == student.chkIn[i].cDate.y &&
					Date.m == student.chkIn[i].cDate.m &&
					Date.d == student.chkIn[i].cDate.d) {
					same = 1;
					check++;
					addstudent.chkIn.push_back(student.chkIn[i]);
					break;
				}
			}
			if (same == 1) {
				addstudent.id = id;
				addstudent.studentName = student.studentName;
				addstudent.cls = student.cls;
				A.push_back(addstudent);
				addstudent.chkIn.clear();
			}
			student.chkIn.clear();
		}
		if (check == 0) {
			cout << "There are no student found in this day" << endl;
		}
	}
	else {
		cout << "Can't open file to check attendance" << endl;
	}
}
void ExportAttendance(tt::vector<tt::score> &Att, string course) {
	ofstream fout;
	string inputpath;
	inputpath = "./export/" + course + "-Attedance.csv";
	fout.open(inputpath);
	if (fout.is_open()) {
		fout << "ID," << "Class," << "StudentName," << "Date," << "CheckinTime"<< endl;
		for (int i = 0; i < Att.size(); i++) {
			fout << Att[i].id << "," << Att[i].cls << "," << Att[i].studentName << "," << Att[i].chkIn[0].cDate.y << "-" << Att[i].chkIn[0].cDate.m << "-" << Att[i].chkIn[0].cDate.d << ","
				<< Att[i].chkIn[0].cTime.h << ":" << Att[i].chkIn[0].cTime.m << ":" << Att[i].chkIn[0].cTime.s << endl;
		}
		fout.close();
	}
	else {
		cout << "Can't export file attendance" << endl;
	}
}
void ViewCheckinList(tt::score& A, string course , int id) {
	tt::clearConsole();
	cout << "\n\n\t\t=====YOUR CHECK-IN=====\n";
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
	for (int i = 0; i < A.chkIn.size(); i++) {
		cout << left << setw(10) << id << left << setw(7) << A.cls << left << setw(30) << A.studentName
			<< left << setw(8) << course << left << setw(11) << to_string(A.chkIn[i].cDate.y) + "/" + to_string(A.chkIn[i].cDate.m) + "/" + to_string(A.chkIn[i].cDate.d)
			<< left << setw(13) << to_string(A.chkIn[i].cTime.h) + ":" + to_string(A.chkIn[i].cTime.m) + ":" + to_string(A.chkIn[i].cTime.s) << endl;
		for (int i = 0; i < 79; i++) {
			cout << "-";
		}
		cout << endl;
	}
}
void EditAttendance(string year, string semester, string course, tt::vector<tt::score> &A , tt::date Date) {
	int choice,number,choice1;
	ifstream fin;
	ofstream fout;
	string inputpath;
	tt::vector<string> students;
	tt::score temp,student;
	tt::checkIn check;
	tt::time tempt;

	cout << "Do you want to add or remove ? :" << endl;
	cout << "(0) Add " << endl << "(1) Remove" << endl;
	cout << "Your choice : ";
	cin >> choice;
	while (choice < 0 || choice >= year.size() || cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Error , try again" << endl;
		cout << "Your choice : ";
		cin >> choice;
	}
	if (choice == 0) {
		inputpath = "./data/course/" + year + "/" + semester + "/" + course + ".dat";
		LoadStudentCourse(fin, students, inputpath);
		cout << "These are the students in this course" << endl;
		for (int i = 0; i < students.size(); i++) {
			cout << "(" << i << ") : " << students[i] << endl;
		}
		do {
			cout << "Enter the ordinal number of the student you want to add : ";
			cin >> number;

			inputpath = "./data/course/" + year + "/" + semester + "/" + course + "/" + students[number] + ".dat";
			LoadScoreFile(temp, inputpath);
			cout << "Enter the time student check in : " << endl;
			cout << "Hour : ";
			cin >> tempt.h;
			cin.ignore();
			cout << "Minute : ";
			cin >> tempt.m;
			cin.ignore();
			cout << "Second : ";
			cin >> tempt.s;
			cin.ignore();
			check.cDate = Date;
			check.cTime = tempt;
			temp.chkIn.push_back(check);
			SaveFileScore(inputpath, temp);
			student.id = stoi(students[number]);
			student.studentName = temp.studentName;
			student.chkIn.push_back(check);
			student.cls = temp.cls;
			A.push_back(student);
			cout << "Do you want to add any one else ?" << endl;
			cout << "(1) Yes " << endl << "(0) No " << endl;
			cin >> choice1;
			while (choice1 != 0 && choice1 != 1 || cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error , try again" << endl;
				cout << "Your choice : ";
				cin >> choice1;
			}
			student.chkIn.clear();
			temp.chkIn.clear();

		} while (choice1 != 0);
	}
	else {
		cout << "These are the students attended in this course" << endl;
		for (int i = 0; i < A.size(); i++) {
			cout << "(" << i << ") : " << A[i].id << endl;
		}
		do {
			cout << "Enter the ordinal number of the student you want to remove : ";
			cin >> number;
			while (number < 0 || number >= A.size() || cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error , try again" << endl;
				cout << "Your choice : ";
				cin >> number;
			}
			inputpath = "./data/course/" + year + "/" + semester + "/" + course + "/" + to_string(A[choice].id) + ".dat";
			LoadScoreFile(temp, inputpath);
			for (int i = 0; i < temp.chkIn.size(); i++) {
				if (Date.y == temp.chkIn[i].cDate.y &&
					Date.m == temp.chkIn[i].cDate.m &&
					Date.d == temp.chkIn[i].cDate.d) {
					temp.chkIn.erase(i);
					break;
				}
			}
			SaveFileScore(inputpath, temp);
			A.erase(number);
			cout << "Do you want to remove any one else ?" << endl;
			cout << "(1) Yes " << endl << "(0) No " << endl;
			cin >> choice1;
			while (choice1 != 0 && choice1 != 1 || cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error , try again" << endl;
				cout << "Your choice : ";
				cin >> choice1;
			}

		} while (choice1 != 0);
	}
}
void ViewCheckIn(int id) {
	int  choice, choice1, check = 0, return1 = 0;
	string inputpath;
	tt::vector<string> linkcourse;
	string studentcourse;
	tt::student A;
	tt::checkIn studenttime;
	tt::score student;
	tt::vector<tt::course> coursestudent;
	do {
		tt::clearConsole();
		FindStudent(A, id, studentcourse, check);
		FindStudentCourse(id, studentcourse, linkcourse, coursestudent);
		if (linkcourse.size() > 1) {
			cout << "We have " << linkcourse.size() << "course(s)" << endl;
			for (int i = 0; i < linkcourse.size(); i++) {
				cout << "(" << i << "): " << linkcourse[i] << endl;
			}
			cout << "Your choice: ";
			cin >> choice;
			while (choice < 0 || choice >= linkcourse.size() || cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Error , try again" << endl;
				cout << "Your choice : ";
				cin >> choice;
			}
			inputpath = linkcourse[choice] + "/" + to_string(id) + ".dat";
			LoadScoreFile(student, inputpath);
			ViewCheckinList(student, coursestudent[choice].id, id);
		}
		else {
			inputpath = linkcourse[0] + "/" + to_string(id) + ".dat";
			LoadScoreFile(student, inputpath);
			ViewCheckinList(student, coursestudent[0].id, id);
		}
		cout << "Press (-1) to return or (0) to exit " << endl;
		cout << "Your choice : ";
		cin >> return1;
		while (return1 != -1 || return1 != 0 || cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error , try again" << endl;
			cout << "Your choice : ";
			cin >> return1;
		}
		linkcourse.clear();
		coursestudent.clear();
		check = 0;
		student.chkIn.clear();

	} while (return1 == -1);
}
bool LecturerAllow(string year, string semester , string course , string lecturer) {
	string inputpath = "./data/course/" + year + "/" + semester + "/course.dat";
	ifstream fin;
	tt::vector<tt::course> teacher;
	LoadCourseFile(teacher, inputpath);
	for (int i = 0; i < teacher.size(); i++) {
		if (teacher[i].id == course && teacher[i].lecturer == lecturer) {
			break;
		}
	}
	return true;
}
