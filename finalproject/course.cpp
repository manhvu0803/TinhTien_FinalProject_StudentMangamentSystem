#include "course.h"

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
	int cont = 0;
	int choice = -1;
	vector<course> List;
	cout << setfill('=') << setw(50) << "=" << endl;
	cout << "*" << setfill('-') << setw(24) << "COURSE MENU" << setfill('-') << setw(23) << "*" << endl;
	cout << setfill('=') << setw(50) << "=" << endl;
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
		if (choice != 0 && (choice >= 1 && choice <= 8))
			switch (choice)
			{
			case 1:
			{
				if (First)
				{
					importCsvFile(List, filePath);
					sortList(List);
					outputCourseList(List);
					saveCourseList(List, filePath + "courses.dat");
					First = false;
				}
				else
				{
					vector<course> moreList;
					importCsvFile(moreList, filePath);
					if (moreList != List)
					{
						int newSize = moreList.size() + List.size();
						for (int i = List.size(); i < newSize; ++i)
						{
							List.push_back(moreList[newSize - i - 1]);
						}
						sortList(List);
						saveCourseList(List, filePath + "courses.dat");
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
					loadDatFile(List, filePath);
				}
				course temp;
				input1Course(temp);
				if (temp.number != -1)
				{
					List.push_back(temp);
					saveCourseList(List, filePath + "courses.dat");
				}
				break;
			}
			case 3:
			{
				if (!First)
				{
					loadDatFile(List, filePath);
				}
				outputCourseList(List);
				editCourse(List, filePath);
				saveCourseList(List, filePath + "courses.dat");
				break;
			}
			case 4:
			{
				if (!First)
				{
					loadDatFile(List, filePath);
				}
				deleteCourse(List, filePath + "courses.dat");
				break;
			}
			case 5:
			{
				if (!First)
				{
					loadDatFile(List, filePath);
				}
				outputSchedule(List);
				break;
			}
			case 6:
			{
				if (!First)
				{
					loadDatFile(List, filePath);
				}
				int n, check;
				outputCourseList(List);
				while (true)
				{
					cout << "Input the course number: "; cin >> n;
					int listSize = List.size();
					if (n <= 0 || n > listSize)
					{
						cout << "Error!!!number available course!!!" << endl;
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
				add1Student(List[n - 1]);
				saveCourseList(List, filePath + "courses.dat");
				break;
			}
			case 7:
			{
				if (!First)
				{
					loadDatFile(List, filePath);
				}
				int n, check;
				outputCourseList(List);
				while (true)
				{
					check = -1;
					cout << "Input the course number: "; cin >> n;
					int listSize = List.size();
					if (n <= 0 || n > listSize)
					{
						cout << "Error!!!number available course!!!" << endl;
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
				if (check == -1)
				{
					remove1Student(List[n - 1]);
					saveCourseList(List, filePath + "courses.dat");
				}
				break;
			}
			case 8:
			{
				if (!First)
				{
					loadDatFile(List, filePath);
				}
				int n, check;
				outputCourseList(List);
				while (true)
				{
					check = -1;
					cout << "Input the course number: "; cin >> n;
					int listSize = List.size();
					if (n <= 0 || n > listSize)
					{
						cout << "Error!!!number available course!!!" << endl;
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
				if (check == -1)
					viewStudentList(List[n - 1]);
				break;
			}
			}
	}

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
void loadCsvFile(vector<course>& list, string filePath)
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
		vector<student> studentList;
		vector <string> numbertFound;
		while (!csvFile.eof())
		{
			course temp;
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
						temp.students.push_back(studentList[i].id);
					}
				}
				else
				{
					temp.number = -1;
					numbertFound.push_back(token);
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
		int n = numbertFound.size();
		if (n != 0)
		{
			cout << "Class: ";
			for (int i = 0; i < n; ++i)
			{
				if (i == 0)
				{
					cout << numbertFound[i];
				}
				else
				{
					cout << ", " << numbertFound[i];
				}
			}
			cout << " numbert found!" << endl;
			numbertFound.clear();
			numbertFound.shrink_to_fit();
			sortList(list);
		}
	}
	else
	{
		cout << "File numbert found" << endl;
	}
	csvFile.close();
}
void loadDatFile(vector<course>& list, string filePath)
{
	ifstream myFile(filePath + "courses.dat");
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
			loadCourseStudentFile(temp, filePath);
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
			temp.endTime.s=0;
			myFile.ignore(1);
			getline(myFile, temp.room);
			list.push_back(temp);
		}

	}
	else
	{
		cout << "courses.dat numbert found" << endl;
		return;
	}
	myFile.close();
	sortList(list);
}
void loadCourseStudentFile(course& Course, string filePath)
{
	ifstream myFile(filePath + Course.className + ".dat");
	if (myFile.is_open())
	{
		int id;
		while (myFile >> id)
		{
			Course.students.push_back(id);
		}
	}
	myFile.close();
}
void saveCourseList(vector<course> list, string filePath)
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
			saveCourseStudentFile(list[i], filePath);
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
		cout << "courses.dat numbert found" << endl;
	}
	dataFile.close();
}
void saveCourseStudentFile(course Course, string filePath)
{
	ofstream myFile(filePath + Course.className + ".dat");
	if (myFile.is_open())
	{
		int n = Course.students.size();
		for (int i = 0; i < n; i++)
		{
			myFile << Course.students[i] << endl;
		}
	}
	myFile.close();
}
void importCsvFile(vector<course>& list, string filePath)
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
		loadCsvFile(list, newPath);
		break;
	}
	case 2:
	{
		loadDatFile(list, filePath);
		break;
	}
	}
	if (list.size() != 0)
		outputCourseList(list);
}
void output1Course(course Course)
{
	cout << endl << setw(3) << Course.number << " - " << setw(35) << Course.name << "(" << setw(7) << Course.id << ") - Student: " << setw(4) << Course.students.size() << endl;
}
void outputCourseList(vector<course> list)
{
	cout << "Course: ";
	int n = list.size();
	cout << endl << setfill('=') << setw(49) << "=" << endl;
	for (int i = 0; i < n; ++i)
	{
		output1Course(list[i]);
		cout << endl << setfill('=') << setw(49) << "=" << endl;
	}
}
void output1CourseData(course Course)
{
	cout << " number            : " << Course.number << endl;
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
void outputSchedule(vector<course> list)
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
int  inputTime(Time& courseTime)
{
	Time temp;
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
			cout << "Error!! numbert available time!!!" << endl;
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
	courseTime = temp;
	return 1;
}
int  inputDate(date& Date)
{
	int check = -1;
	date temp;
	time_t numberw = time(0);
	tm ltm;
	localtime_s(&ltm, &numberw);
	while (true)
	{
		cout << "	Input day  :   "; cin >> temp.d;
		if ((temp.d > maxdayinmonth(temp.m, temp.y)) || (temp.d < 1))
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
void input1Course(course& newCourse)
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
	addStudent(newCourse);
}
void inputCourse(vector<course>& list, string filePath)
{
	int n;
	cout << "Numbers of new course: ";
	cin >> n;

	course temp;
	for (int i = 0; i < n; ++i)
	{
		input1Course(temp);
		if (temp.number != -1)
		{
			list.push_back(temp);
		}
	}
	saveCourseList(list, filePath);
	outputCourseList(list);
}
void editCourse(vector<course>& list, string filePath)
{
	int n, check;
	while (true)
	{
		cout << "Input the course number: "; cin >> n;
		int listSize = list.size();
		if (n <= 0 || n > listSize)
		{
			cout << "Error!!!number available course!!!" << endl;
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
			cout << "Error!!!number choice available!!!" << endl;
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
		course newCourse;
		input1Course(newCourse);
		if (newCourse.number != -1)
			list[n - 1] = newCourse;
		break;
	}
	}
	output1CourseData(list[n - 1]);
	sortList(list);
}
void deleteCourse(vector<course>& list, string filePath)
{
	int n, check;
	outputCourseList(list);
	while (true)
	{
		cout << "Input the course number: "; cin >> n;
		int listSize = list.size();
		if (n <= 0 || n > listSize)
		{
			cout << "Error!!!number available course!!!" << endl;
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
	list[n - 1].students.clear();
	list[n - 1].students.shrink_to_fit();
	list.erase(list.begin() + n - 1);
	list.shrink_to_fit();
	saveCourseList(list, filePath);
}
void remove1Student(course& Course)
{
	viewStudentList(Course);
	int n, check;
	while (true)
	{
		cout << "Input the studnet number: "; cin >> n;
		int studentSize = Course.students.size();
		if (n <= 0 || n > studentSize)
		{
			cout << "Error!!!number student at that position!!!" << endl;
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
	Course.students.erase(Course.students.begin() + n - 1);
	Course.students.shrink_to_fit();
}
void add1Student(course& Course)
{
	int Id, check;
	int n;
	while (true)
	{
		check = -1;
		cout << "Student id: "; cin >> Id;
		if (log10(Id) + 1 == 7 || log10(Id) + 1 == 8)
		{
			n = Course.students.size();
			for (int i = 0; i < n; ++i)
			{
				if (Course.students[i] == Id)
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
				Course.students.push_back(Id);
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
void addStudent(course& Course)
{
	int num;
	cout << "Number of new student: "; cin >> num;
	for (int i = 0; i < num; ++i)
	{
		add1Student(Course);
	}
}
student searchStudent(int id)
{
	ifstream fload;
	string flname;
	student Student;
	string classname;
	vector<student>stL;
	fload.open("data/classes/allclassname.txt");
	int check = 0;
	if (!fload.is_open())
	{
		cout << "Can numbert open file." << endl;
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
void viewStudentList(course courseName)// Đợi file class của Nhật
{
	int n = courseName.students.size();
	if (n == 0)
	{
		cout << "There is number student in this course yet!" << endl;
	}
	else
	{
		student Student;
		vector<int> Drop;
		for (int i = 0; i < n; ++i)
		{
			Student = searchStudent(courseName.students[i]);
			if (Student.id == -2)//allclassname.txt is missing
			{
				cout << "Error!!! number student id found!\n";
				courseName.students.clear();
				courseName.students.shrink_to_fit();
				break;
			}
			if (Student.id == -1)
			{
				Drop.push_back(courseName.students[i]);
				courseName.students.erase(courseName.students.begin() + i);
				courseName.students.shrink_to_fit();
				n--;
				i--;
			}
			else
			{
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
void sortList(vector<course>& List)
{
	sort(List.begin(), List.end(), [](const course& lhs, const course& rhs)
		{
			return lhs.id < rhs.id;
		});
	sort(List.begin(), List.end(), [](const course& lhs, const course& rhs)
		{
			return lhs.name < rhs.name;
		});
	int n = List.size();
	for (int i = 0; i < n; ++i)
	{
		List[i].number = i + 1;
	}
}
course searchCourse(string filePath, string Id)
{
	vector<course>List;
	loadDatFile(List, filePath);
	int listSize = List.size();
	for (int i = 0; i < listSize; ++i)
	{
		if (List[i].id == Id)
			return List[i];
	}
	course Error;
	Error.number = -1;
	return Error;
}