﻿#include "course.h"

void courseMenu(int year, string semester)
{
	string filePath = ("data/course/");
	filePath.append(to_string(year));
	filePath.append("-");
	filePath.append(to_string(year + 1));
	filePath.append("/");
	filePath.append(semester);
	filePath.append("/");
	bool First = true;
	int cont = 1;
	int choice = -1;
	tt::vector<tt::course> List;
	tt::vector<tt::vector<int>> students;
	cout << setfill('=') << setw(50) << "=" << endl;
	cout << "*" << setfill('-') << setw(24) << "COURSE MENU" << setfill('-') << setw(23) << "*" << endl;
	cout << setfill('=') << setw(50) << "=" << endl;
	while (cont != 0)
	{
		while (choice != 0)
		{
			cout << " Enter 0: To exit" << endl;
			cout << " Enter 1: Import course" << endl;
			cout << " Enter 2: Add new course" << endl;
			cout << " Enter 3: Edit course" << endl;
			cout << " Enter 4: Remove a course" << endl;
			cout << " Enter 5: View course list" << endl;
			cout << " Enter 6: Add a student to a course" << endl;
			cout << " Enter 7: Remove a student" << endl;
			cout << " Enter 8: View student list" << endl;
			cout << " Enter your choice: ";
			cin >> choice;
			if (choice >= 0 && choice <= 8)
			{
				break;
			}
			else
			{
				cout << "Error! Choose agian:" << endl;
			}

		}
		switch (choice)
		{
		case 0:
		{
			cont = choice;
		}
		case 1:
		{
			if (First)
			{
				importCsvFile(List, students, filePath);
				sortList(List, students);
				outputCourseList(List, students);
				saveCourseList(List, students, filePath + "courses.dat");
				First = false;
			}
			else
			{
				tt::vector<tt::course> moreList;
				importCsvFile(moreList, students, filePath);
				if (moreList != List)
				{
					int newSize = moreList.size() + List.size();
					for (int i = List.size(); i < newSize; ++i)
					{
						List.push_back(moreList[newSize - i - 1]);
					}
					sortList(List, students);
					saveCourseList(List, students, filePath + "courses.dat");
					moreList.clear();
					moreList.shrink_to_fit();
				}
			}
			break;
		}
		case 2:
		{
			if (!First)
			{
				loadDatFile(List, students, filePath);
			}
			tt::course temp;
			tt::vector<int>classStudents;
			input1Course(temp, classStudents);
			if (temp.number != -1)
			{
				List.push_back(temp);
				students.push_back(classStudents);
				saveCourseList(List, students, filePath + "courses.dat");
			}
			classStudents.clear();
			break;
		}
		case 3:
		{
			if (!First)
			{
				loadDatFile(List, students, filePath);
			}
			outputCourseList(List, students);
			editCourse(List, students, filePath);
			saveCourseList(List, students, filePath + "courses.dat");
			break;
		}
		case 4:
		{
			if (!First)
			{
				loadDatFile(List, students, filePath);
			}
			deleteCourse(List, students, filePath);
			break;
		}
		case 5:
		{
			if (!First)
			{
				loadDatFile(List, students, filePath);
			}
			outputSchedule(List);
			break;
		}
		case 6:
		{
			if (!First)
			{
				loadDatFile(List, students, filePath);
			}
			int n, check;
			outputCourseList(List, students);
			while (true)
			{
				cout << "Input the course no: "; cin >> n;
				int listSize = List.size();
				if (n <= 0 || n > listSize)
				{
					cout << "Error!!!No available course!!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					cin >> cont;
					if (cont == 0)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			if (cont != 0)
			{
				tt::vector<int> classStudent;
				add1Student(List[n - 1], classStudent);
				students.push_back(classStudent);
				saveCourseList(List, students, filePath + "courses.dat");
			}
			break;
		}
		case 7:
		{
			if (!First)
			{
				loadDatFile(List, students, filePath);
			}
			int n, check;
			outputCourseList(List, students);
			while (true)
			{
				check = -1;
				cout << "Input the course no: "; cin >> n;
				int listSize = List.size();
				if (n <= 0 || n > listSize)
				{
					cout << "Error!!!No available course!!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					cin >> cont;
					if (cont == 0)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			if (check == -1)
			{
				remove1Student(students[n - 1]);
				saveCourseList(List, students, filePath + "courses.dat");
			}
			break;
		}
		case 8:
		{
			if (!First)
			{
				loadDatFile(List, students, filePath);
			}
			int n, check;
			outputCourseList(List, students);
			while (true)
			{
				check = -1;
				cout << "Input the course no: "; cin >> n;
				int listSize = List.size();
				if (n <= 0 || n > listSize)
				{
					cout << "Error!!!No available course!!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					cin >> cont;
					if (cont == 0)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			if (check == -1)
			{
				tt::vector<int>classStudents;
				for (int i = 0; i < students[n - 1].size(); ++i)
				{
					classStudents.push_back(students[n - 1][i]);
				}
				viewStudentList(classStudents);
			}
			break;
		}
		}
	}
	List.clear();
	students.clear();
}
void upperCase(string& name)
{
	int n = name.size();
	for (int i = 0; i < n; ++i)
	{
		if (97 <= name[i] && name[i] <= 122)
			name[i] -= 32;
	}
}
void loadCsvFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	if (filePath.compare(filePath.size() - 4, 4, ".csv") != 0)
	{
		if (filePath[filePath.size() - 6] == '.' || filePath[filePath.size() - 5] == '.')
		{
			cout << "Wrong data file";
			return;
		}
		else
			filePath.append(".csv");
	}
	int n = filePath.size();
	for (int i = 0; i < n; ++i)
	{
		if (filePath[i] == '\\')
			filePath[i] = '/';
	}
	ifstream csvFile(filePath);
	if (csvFile.is_open())
	{
		string line;
		string token;
		getline(csvFile, line);
		tt::vector<tt::student> studentList;
		tt::vector <string> notFound;
		tt::vector<int>classStudents;
		while (!csvFile.eof())
		{
			tt::course temp;
			if (line[0] == 'N')
			{
			}
			else
			{
				stringstream check(line);
				string classFilePath("data/classes/");
				getline(check, token, ',');
				temp.number = stoi(token);
				getline(check, token, ',');
				temp.id = token;
				getline(check, token, ',');
				temp.name = token;
				getline(check, token, ',');
				temp.className = token;
				upperCase(token);
				classFilePath.append(token);
				classFilePath.append(".csv");
				ifstream classFile(classFilePath);
				if (classFile.is_open())
				{
					loadfromdatfile(classFile, studentList);
					int n = studentList.size();
					for (int i = 0; i < n; ++i)
					{
						classStudents.push_back(studentList[i].id);
					}
					students.push_back(classStudents);
					classStudents.clear();
				}
				else
				{
					temp.number = -1;
					notFound.push_back(token);
				}
				classFile.close();
				getline(check, token, ',');
				getline(check, token, ',');
				temp.lecturer = token;
				getline(check, token, ',');
				getline(check, token, ',');
				getline(check, token, '/');
				temp.startDate.m = stoi(token);
				getline(check, token, '/');
				temp.startDate.d = stoi(token);
				getline(check, token, ',');
				temp.startDate.y = stoi(token);
				getline(check, token, '/');
				temp.endDate.m = stoi(token);
				getline(check, token, '/');
				temp.endDate.d = stoi(token);
				getline(check, token, ',');
				temp.endDate.y = stoi(token);
				getline(check, token, ',');
				upperCase(token);
				if (token == "MON" || token == "MONDAY")
				{
					temp.DoW = 0;
				}
				else
				{
					if (token == "TUE" || token == "TUESDAY")
					{
						temp.DoW = 1;
					}
					else
					{
						if (token == "WED" || token == "WEDNESDAY")
						{
							temp.DoW = 2;
						}
						else
						{
							if (token == "THU" || token == "THURSDAY")
							{
								temp.DoW = 3;
							}
							else
							{
								if (token == "FRI" || token == "FRIDAY")
								{
									temp.DoW = 4;
								}
								else
								{
									if (token == "SAT" || token == "SATURDAY")
									{
										temp.DoW = 5;
									}
									else
									{
										temp.DoW = 6;
									}
								}
							}
						}
					}
				}
				getline(check, token, ',');
				temp.startTime.h = stoi(token);
				getline(check, token, ',');
				temp.startTime.m = stoi(token);
				temp.startTime.s = 0;
				getline(check, token, ',');
				temp.endTime.h = stoi(token);
				getline(check, token, ',');
				temp.endTime.m = stoi(token);
				temp.endTime.s = 0;
				getline(check, token);
				temp.room = token;
				if (temp.number != -1)
					list.push_back(temp);
			}
			getline(csvFile, line);
		}
		int n = notFound.size();
		if (n != 0)
		{
			cout << "Class: ";
			for (int i = 0; i < n; ++i)
			{
				if (i == 0)
				{
					cout << notFound[i];
				}
				else
				{
					cout << ", " << notFound[i];
				}
			}
			cout << " Not found!" << endl;
			notFound.clear();
			notFound.shrink_to_fit();
			sortList(list, students);
		}
	}
	else
	{
		cout << "File not found" << endl;
	}
	csvFile.close();
}
void loadDatFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	ifstream myFile(filePath + "courses.dat");
	string line;
	tt::course temp;
	tt::vector<int>classStudents;
	int no;
	if (myFile.is_open())
	{
		while (myFile >> no)
		{
			temp.number = no;
			myFile.ignore(1);
			getline(myFile, temp.id);
			getline(myFile, temp.name);
			getline(myFile, temp.className);
			loadCourseStudentFile(temp, classStudents, filePath);
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
	sortList(list, students);
}
void loadCourseStudentFile(tt::course& Course, tt::vector<int>& classStudents, string filePath)
{
	ifstream myFile(filePath + Course.className + ".dat");
	if (myFile.is_open())
	{
		int id;
		while (myFile >> id)
		{
			classStudents.push_back(id);
		}
	}
	else
	{
		Course.number = -1;
	}
	myFile.close();
}
void saveCourseList(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	int n = list.size();
	ofstream dataFile(filePath);
	if (dataFile.is_open())
	{
		for (int i = 0; i < n; ++i)
		{
			dataFile << list[i].number << endl;
			dataFile << list[i].id << endl;
			dataFile << list[i].name << endl;
			dataFile << list[i].className << endl;
			saveCourseStudentFile(list[i], students[i], filePath);
			dataFile << list[i].lecturer << endl;
			dataFile << list[i].startDate.y << " ";
			dataFile << list[i].startDate.m << " ";
			dataFile << list[i].startDate.d << endl;
			dataFile << list[i].endDate.y << " ";
			dataFile << list[i].endDate.m << " ";
			dataFile << list[i].endDate.d << endl;
			dataFile << list[i].DoW << endl;
			dataFile << list[i].startTime.h << " ";
			dataFile << list[i].startTime.m << endl;
			dataFile << list[i].endTime.h << " ";
			dataFile << list[i].endTime.m << endl;
			dataFile << list[i].room << endl;
		}
	}
	else
	{
		cout << "courses.dat not found" << endl;
	}
	dataFile.close();
}
void saveCourseStudentFile(tt::course& Course, tt::vector<int>& classStudent, string filePath)
{
	ofstream myFile(filePath + Course.className + ".dat");
	if (myFile.is_open())
	{
		int n = classStudent.size();
		for (int i = 0; i < n; i++)
		{
			myFile << classStudent[i] << endl;
		}
	}
	myFile.close();
}
void importCsvFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	int option;
	string newPath;
	cout << "Please choose an option: \n";
	cout << "Enter 1: Link your file address to system\n";
	cout << "Enter 2: Open existing file  \n";
	while (true)
	{
		cout << "Input: "; cin >> option;
		if (option < 0 || option>2)
		{
			cout << "Error!! Please input again or (0) to break";
		}
		else
		{
			break;
		}
	}
	switch (option)
	{
	default:
		cout << "Break!!!\n";
		return;
	case 1:
	{
		cout << "Input your file address: ";

		cin >> newPath;
		loadCsvFile(list, students, newPath);
		break;
	}
	case 2:
	{
		loadDatFile(list, students, filePath);
		break;
	}
	}
	if (list.size() != 0)
		outputCourseList(list, students);
}
void output1Course(tt::course& Course, tt::vector<int>& classStudent)
{
	cout << endl << setw(3) << Course.number << " - " << setw(35) << Course.name << "(" << setw(7) << Course.id << ") - Student: " << setw(4) << classStudent.size() << endl;
}
void outputCourseList(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students)
{
	cout << "Course: ";
	int n = list.size();
	cout << endl << setfill('=') << setw(49) << "=" << endl;
	for (int i = 0; i < n; ++i)
	{
		output1Course(list[i], students[i]);
		cout << endl << setfill('=') << setw(49) << "=" << endl;
	}
}
void output1CourseData(tt::course& Course)
{
	cout << " No            : " << Course.number << endl;
	cout << " Id            : " << Course.id << endl;
	cout << " Name          : " << Course.name << endl;
	cout << " Class         : " << Course.className << endl;;
	cout << " Lecturer Name : " << Course.lecturer << endl;
	cout << " Start Date    : " << setfill('0') << setw(2) << Course.startDate.d << "/"
		<< setfill('0') << setw(2) << Course.startDate.m << "/"
		<< Course.startDate.y << endl;
	cout << " End Date      : " << setfill('0') << setw(2) << Course.endDate.d << "/"
		<< setfill('0') << setw(2) << Course.endDate.m << "/"
		<< Course.endDate.y << endl;
	switch (Course.DoW)
	{
	case 0:
	{
		cout << " Study day     : Monday";
		break;
	}
	case 1:
	{
		cout << " Study day     : Tuesday";
		break;
	}
	case 2:
	{
		cout << " Study day     : Wednesday";
		break;
	}
	case 3:
	{
		cout << " Study day     : Thursday";
		break;
	}
	case 4:
	{
		cout << " Study day     : Friday";
		break;
	}
	case 5:
	{
		cout << " Study day     : Satday";
		break;
	}
	case 6:
	{
		cout << " Study day     : Sunday";
		break;
	}
	}
	cout << " Start hour    : " << setfill('0') << setw(2) << Course.startTime.h << ":"
		<< setfill('0') << setw(2) << Course.startTime.m << endl;
	cout << " End hour      : " << setfill('0') << setw(2) << Course.endTime.h << ":"
		<< setfill('0') << setw(2) << Course.endTime.m << endl;
	cout << " Room          :" << Course.room;

}
void outputSchedule(tt::vector<tt::course>& list)
{
	cout << "Schedule:  " << endl;
	int n = list.size();
	cout << endl << setfill('=') << setw(49) << "=" << endl;
	for (int i = 0; i < n; ++i)
	{
		output1CourseData(list[i]);
		cout << endl << setfill('=') << setw(49) << "=" << endl;
	}
}
int  inputTime(tt::time& courseTime)
{
	tt::time temp;
	int check = -1;
	while (true)
	{
		cout << "	Input hour: ";
		cin >> temp.h;
		if (temp.h >= 7 && temp.h <= 19)
		{
			break;
		}
		else
		{
			cout << "Error!! Not available time!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				break;
			}
		}
	}
	if (check == 0)
	{
		courseTime.h = 0;
		courseTime.m = 0;
		courseTime.s = 0;
		return 0;
	}
	while (true)
	{
		cout << "	Input minute: ";
		cin >> temp.m;
		if (temp.m >= 0 && temp.m <= 59)
		{
			break;
		}
		else
		{
			cout << "Error!! Please check your input again." << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				break;
			}
		}
	}
	if (check == 0)
	{
		courseTime.h = 0;
		courseTime.m = 0;
		return 0;
	}
	temp.s = 0;
	courseTime = temp;
	return 1;
}
int  inputDate(tt::date& Date)
{
	int check = -1;
	tt::date temp;
	time_t now = std::time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	//while (true)
	//{
	//	cout << "	Input day  :   "; cin >> temp.d;
	//	if ((temp.d > maxdayinmonth(temp.m, temp.y)) || (temp.d < 1))
	//	{
	cout << "Error!! Please check your input again." << endl;
	cout << "Input (0) to break or (1) to continue: ";
	cin >> check;
	//		if (check == 0)
	//		{
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
	if (check == 0)
	{
		Date = { 0 };
		return 0;
	}

	while (true)
	{
		cout << "	Input month:   "; cin >> temp.m;
		if (temp.m < 1 && temp.m>12)
		{
			cout << "Error!! Please check your input again." << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	if (check == 0)
	{
		Date = { 0 };
		return 0;
	}

	while (true)
	{
		cout << "	Input year :   "; cin >> temp.y;

		if (((ltm.tm_year + 1900) - temp.y > 20) || ((ltm.tm_year + 1900) - temp.y < -5))
		{
			cout << "Error!! Please check your input again." << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	if (check == 0)
	{
		Date = { 0 };
		return 0;
	}
	Date = temp;
	return 1;
}
void input1Course(tt::course& newCourse, tt::vector<int>& classStudents)
{
	int check;
	cout << " Id                : "; getline(cin, newCourse.id);
	cout << " Name              : "; getline(cin, newCourse.name);
	cout << " Class             : "; getline(cin, newCourse.className);
	cout << " Lecturer name     : "; getline(cin, newCourse.lecturer);
	cout << " Start date        : \n"; check = inputDate(newCourse.startDate);
	if (check == 0)
	{
		newCourse.number = -1;
		return;
	}
	cout << " End date          : \n"; check = inputDate(newCourse.endDate);
	if (check == 0)
	{
		newCourse.number = -1;
		return;
	}
	while (true)
	{
		cout << " (0): Monday" << endl;
		cout << " (1): Tuesday" << endl;
		cout << " (2): Wednesday" << endl;
		cout << " (3): Thursday" << endl;
		cout << " (4): Friday" << endl;
		cout << " (5): Satday" << endl;
		cout << " (6): Sunday" << endl;
		cout << " Dow          : "; cin >> newCourse.DoW;
		if (newCourse.DoW >= 0 && newCourse.DoW <= 6)
		{
			break;
		}
		else
		{
			cout << "Error!!!Please check your input" << endl;
			cout << "Enter (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				break;
			}
		}
	}
	if (check == 0)
	{
		newCourse.number = -1;
		return;
	}
	cout << " Start hour        : \n"; check = inputTime(newCourse.startTime);
	if (check == 0)
	{
		newCourse.number = -1;
		return;
	}
	cout << " End hour         : \n"; check = inputTime(newCourse.endTime);
	if (check == 0)
	{
		newCourse.number = -1;
		return;
	}
	cout << " Room            : \n"; getline(cin, newCourse.room);
	addStudent(newCourse, classStudents);
}
void inputCourse(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	int n;
	cout << "Numbers of new course: ";
	cin >> n;
	tt::vector<int>classStudents;
	tt::course temp;
	for (int i = 0; i < n; ++i)
	{
		input1Course(temp, classStudents);
		if (temp.number != -1)
		{
			list.push_back(temp);
			students.push_back(classStudents);
			classStudents.clear();
		}
	}
	saveCourseList(list, students, filePath);
	outputCourseList(list, students);
}
void editCourse(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	int n, check;
	while (true)
	{
		cout << "Input the course no: "; cin >> n;
		int listSize = list.size();
		if (n <= 0 || n > listSize)
		{
			cout << "Error!!!No available course!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				return;
			}
		}
		else
		{
			break;
		}
	}
	int choice;
	cout << "Please enter your decision: " << endl;
	cout << "Enter (1) : Name" << endl;
	cout << "Enter (2) : Id " << endl;
	cout << "Enter (3) : Class" << endl;
	cout << "Enter (4) : Lecturer" << endl;
	cout << "Enter (5) : Day of Week" << endl;
	cout << "Enter (6) : Room" << endl;
	cout << "Enter (7) : Start date" << endl;
	cout << "Enter (8) : End date" << endl;
	cout << "Enter (9) : Start Hour" << endl;
	cout << "Enter (10): End Hour" << endl;
	cout << "Enter (11):  Whole course" << endl;
	while (true)
	{
		cout << "Input: "; cin >> choice;
		if (choice <= 0 || choice > 11)
		{
			cout << "Error!!!No choice available!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				return;
			}
		}
		else
		{
			break;
		}
	}
	switch (choice)
	{
	case 1:
	{
		cout << " Id: "; getline(cin, list[n - 1].id);
		break;
	}
	case 2:
	{
		cout << " Name: "; getline(cin, list[n - 1].name);
		break;
	}
	case 3:
	{
		string oldFileName(filePath + list[n - 1].className + ".dat");
		cout << " Class: "; getline(cin, list[n - 1].className);
		string newFileName(filePath + list[n - 1].className + ".dat");
		rename(oldFileName.c_str(), newFileName.c_str());
		break;
	}
	case 4:
	{
		cout << " Lecturer name     : "; getline(cin, list[n - 1].lecturer);
		break;
	}
	case 5:
	{
		int DoW;
		while (true)
		{
			cout << " (0): Monday" << endl;
			cout << " (1): Tuesday" << endl;
			cout << " (2): Wednesday" << endl;
			cout << " (3): Thursday" << endl;
			cout << " (4): Friday" << endl;
			cout << " (5): Satday" << endl;
			cout << " (6): Sunday" << endl;
			cout << " Dow          : "; cin >> DoW;
			if (DoW >= 0 && DoW <= 6)
			{
				break;
			}
			else
			{
				cout << "Error!!!Please check your input" << endl;
				cout << "Enter (0) to break or (1) to continue: ";
				cin >> check;
				if (check == 0)
				{
					break;
				}
			}
		}
		break;
	}
	case 6:
	{
		cout << " Room            : \n"; getline(cin, list[n - 1].room);
		break;
	}
	case 7:
	{
		cout << " Start date: \n"; inputDate(list[n - 1].startDate);
		break;
	}
	case 8:
	{
		cout << " End date: \n"; inputDate(list[n - 1].endDate);
		break;
	}
	case 9:
	{
		cout << " Start hour        : \n"; inputTime(list[n - 1].startTime);
		break;
	}
	case 10:
	{
		cout << " End hour         : \n"; inputTime(list[n - 1].endTime);
		break;
	}
	case 11:
	{
		tt::course newCourse;
		tt::vector<int> classStudent;
		input1Course(newCourse, classStudent);
		if (newCourse.number != -1)
		{
			students.push_back(classStudent);
			list[n - 1] = newCourse;
		}
		classStudent.clear();
		break;
	}
	}
	output1CourseData(list[n - 1]);
	sortList(list, students);
}
void deleteCourse(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	int n, check;
	outputCourseList(list, students);
	while (true)
	{
		cout << "Input the course no: "; cin >> n;
		int listSize = list.size();
		if (n <= 0 || n > listSize)
		{
			cout << "Error!!!No available course!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				return;
			}
		}
		else
		{
			break;
		}
	}
	string path = filePath;
	path += "/";
	path += list[n - 1].className.c_str();
	path += ".dat";
	remove(path.c_str());
	students[n - 1].clear();
	students.shrink_to_fit();
	list.erase(n - 1);
	list.shrink_to_fit();
	saveCourseList(list, students, filePath + ".dat");
}
void remove1Student(tt::vector<int>& classStudent)
{
	viewStudentList(classStudent);
	int n, check;
	while (true)
	{
		cout << "Input the studnet no: "; cin >> n;
		int studentSize = classStudent.size();
		if (n <= 0 || n > studentSize)
		{
			cout << "Error!!!No student at that position!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				return;
			}
		}
		else
		{
			break;
		}
	}
	classStudent.erase(n - 1);
	classStudent.shrink_to_fit();
}
void add1Student(tt::course& Course, tt::vector<int>& classStudents)
{
	int Id, check;
	int n;
	while (true)
	{
		check = -1;
		cout << "Student id: "; cin >> Id;
		if (log10(Id) + 1 == 7 || log10(Id) + 1 == 8)
		{
			n = classStudents.size();
			for (int i = 0; i < n; ++i)
			{
				if (classStudents[i] == Id)
				{
					cout << "Student have already been here!!" << endl;
				}
				cout << "Input (0) to break or (1) to continue: ";
				cin >> check;
				if (check == 0)
				{
					return;
				}
			}
			if (check == -1)
			{
				classStudents.push_back(Id);
				break;
			}
		}
		else
		{
			cout << "Wrong Id!!! Please input again!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> check;
			if (check == 0)
			{
				return;
			}
		}
	}
}
void addStudent(tt::course& Course, tt::vector<int>& classStudents)
{
	int num;
	cout << "Numbers of new student: "; cin >> num;
	for (int i = 0; i < num; ++i)
	{
		add1Student(Course, classStudents);
	}
}
tt::student searchStudent(int id)
{
	ifstream fload;
	string flname;
	tt::student Student;
	string classname;
	tt::vector<tt::student>stL;
	fload.open("data/classes/allclassname.txt");
	int check = 0;
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
		Student.number = -2;
		return Student;
	}
	else
	{
		while (fload >> classname)
		{
			stL.clear();
			flname = "data/classes/" + classname + "/" + classname + ".dat";
			importtoprogram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (id == stL[i].id)
				{
					check = 1;
					Student = stL[i];
					cout << endl;
					break;
				}
			}
		}
		fload.close();
	}
	if (check == 1)
	{
		return Student;
	}
	else
	{
		Student.number = -1;
		return Student;
	}
}
void viewStudentList(tt::vector<int>& classStudent)// Đợi file class của Nhật
{
	int n = classStudent.size();
	sort(classStudent.begin(), classStudent.end(), [](const int& lhs, const int& rhs)
		{
			return lhs < rhs;
		});
	if (n == 0)
	{
		cout << "There is no student in this course yet!" << endl;
	}
	else
	{
		tt::student Student;
		tt::vector<int> Drop;
		for (int i = 0; i < n; ++i)
		{
			Student = searchStudent(classStudent[i]);
			if (Student.id == -2)//allclassname.txt is missing
			{
				cout << "Error!!! No student id found!\n";
				classStudent.clear();
				classStudent.shrink_to_fit();
				break;
			}
			if (Student.id == -1)
			{
				Drop.push_back(classStudent[i]);
				classStudent.erase(i);
				classStudent.shrink_to_fit();
				n--;
				i--;
			}
			else
			{
				Student.number = i + 1;
				display1studentline(Student);
			}
		}
		if (Drop.size() != 0)
		{
			int dropStudent = Drop.size();
			for (int i = 0; i < dropStudent; ++i)
			{
				if (i == 0)
				{
					cout << Drop[i];
				}
				else
				{
					cout << ", " << Drop[i];
				}
			}
			cout << " dropped.";
		}
	}
}
void sortList(tt::vector<tt::course>& List, tt::vector<tt::vector<int>>& students)
{
	sort(List.begin(), List.end(), [](const tt::course& lhs, const tt::course& rhs)
		{
			return lhs.id < rhs.id;
		});
	sort(List.begin(), List.end(), [](const tt::course& lhs, const tt::course& rhs)
		{
			return lhs.name < rhs.name;
		});

	int n = List.size();
	for (int i = 0; i < n; ++i)
	{
		swap(students[i], students[List[i].number - 1]);
	}
	for (int i = 0; i < n; ++i)
	{
		List[i].number = i + 1;
	}
}
void swap(tt::vector<int>& list1, tt::vector<int>& list2)
{
	tt::vector<int>temp;
	for (int i = 0; i < list1.size(); ++i)
	{
		temp.push_back(list1[i]);
	}
	list1.clear();
	for (int i = 0; i < list2.size(); ++i)
	{
		list1.push_back(list2[i]);
	}
	list1.shrink_to_fit();
	list2.clear();
	for (int i = 0; i < temp.size(); ++i)
	{
		list2.push_back(temp[i]);
	}
	list2.shrink_to_fit();
	temp.clear();
	temp.shrink_to_fit();
}
tt::course searchCourse(string filePath, string Id)
{
	tt::vector<tt::course>List;
	tt::course Course;
	tt::vector<tt::vector<int>>students;
	loadDatFile(List, students, filePath);
	int listSize = List.size();
	for (int i = 0; i < listSize; ++i)
	{
		if (List[i].id == Id)
		{
			Course = List[i];
			return Course;

		}
	}
	Course.number = -1;
	students.clear();
	return Course;
}