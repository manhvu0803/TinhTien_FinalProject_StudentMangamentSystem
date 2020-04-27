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
	cout << "*" << setfill('-') << setw(25) << "MAIN MENU" << setfill('-') << setw(24) << "*" << endl;
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
						/*
						List.insert(List.end(), moreList.begin(), moreList.end());
						sortList(List);
						*/
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
				if (temp.No != -1)
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
					cout << "Input the course No: "; cin >> n;
					int listSize = List.size();
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
					cout << "Input the course No: "; cin >> n;
					int listSize = List.size();
					if (n <= 0 || n > listSize)
					{
						cout << "Error!!!No available course!!!" << endl;
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
					cout << "Input the course No: "; cin >> n;
					int listSize = List.size();
					if (n <= 0 || n > listSize)
					{
						cout << "Error!!!No available course!!!" << endl;
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
		vector <string> notFound;
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
				temp.No = stoi(token);
				getline(check, token, ',');
				temp.Id = token;
				getline(check, token, ',');
				temp.Name = token;
				getline(check, token, ',');
				temp.Class = token;
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
						temp.studentId.push_back(studentList[i].id);
					}
				}
				else
				{
					temp.No = -1;
					notFound.push_back(token);
				}
				classFile.close();
				getline(check, token, ',');
				temp.lecturerAccount = token;
				getline(check, token, ',');
				temp.lecturerName = token;
				getline(check, token, ',');
				temp.lecturerDegree = token;
				getline(check, token, ',');
				temp.lecturerGender = token;
				getline(check, token, '/');
				temp.startDate.month = stoi(token);
				getline(check, token, '/');
				temp.startDate.day = stoi(token);
				getline(check, token, ',');
				temp.startDate.year = stoi(token);
				getline(check, token, '/');
				temp.endDate.month = stoi(token);
				getline(check, token, '/');
				temp.endDate.day = stoi(token);
				getline(check, token, ',');
				temp.endDate.year = stoi(token);
				getline(check, token, ',');
				temp.DoW = token;
				getline(check, token, ',');
				temp.startHour.hour = stoi(token);
				getline(check, token, ',');
				temp.startHour.min = stoi(token);
				getline(check, token, ',');
				temp.endHour.hour = stoi(token);
				getline(check, token, ',');
				temp.endHour.min = stoi(token);
				getline(check, token);
				temp.room = token;
				if (temp.No != -1)
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
			cout << " not found!" << endl;
			notFound.clear();
			notFound.shrink_to_fit();
			sortList(list);
		}
	}
	else
	{
		cout << "File not found" << endl;
	}
	csvFile.close();
}
void loadDatFile(vector<course>& list, string filePath)
{
	ifstream myFile(filePath + "courses.dat");
	string line;
	course temp;
	int No;
	if (myFile.is_open())
	{
		while (myFile >> No)
		{
			temp.clear();
			temp.No = No;
			myFile.ignore(1);
			getline(myFile, temp.Id);
			getline(myFile, temp.Name);
			getline(myFile, temp.Class);
			loadCourseStudentFile(temp, filePath);
			getline(myFile, temp.lecturerAccount);
			myFile >> temp.startDate.year;
			myFile >> temp.startDate.month;
			myFile >> temp.startDate.day;
			myFile >> temp.endDate.year;
			myFile >> temp.endDate.month;
			myFile >> temp.endDate.day;
			myFile.ignore(1);
			getline(myFile, temp.DoW);
			myFile >> temp.startHour.hour;
			myFile >> temp.startHour.min;
			myFile >> temp.endHour.hour;
			myFile >> temp.endHour.min;
			myFile.ignore(1);
			getline(myFile, temp.room);
			list.push_back(temp);
		}

	}
	else
	{
		cout << "courses.dat Not found" << endl;
		return;
	}
	myFile.close();
	sortList(list);
}
void loadCourseStudentFile(course& Course, string filePath)
{
	ifstream myFile(filePath + Course.Class + ".dat");
	if (myFile.is_open())
	{
		int id;
		while (myFile >> id)
		{
			Course.studentId.push_back(id);
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
			dataFile << list[i].No << endl;
			dataFile << list[i].Id << endl;
			dataFile << list[i].Name << endl;
			dataFile << list[i].Class << endl;
			saveCourseStudentFile(list[i], filePath);
			dataFile << list[i].lecturerName << endl;
			dataFile << list[i].startDate.year << " ";
			dataFile << list[i].startDate.month << " ";
			dataFile << list[i].startDate.day << endl;
			dataFile << list[i].endDate.year << " ";
			dataFile << list[i].endDate.month << " ";
			dataFile << list[i].endDate.day << endl;
			dataFile << list[i].DoW << endl;
			dataFile << list[i].startHour.hour << " ";
			dataFile << list[i].startHour.min << endl;
			dataFile << list[i].endHour.hour << " ";
			dataFile << list[i].endHour.min << endl;
			dataFile << list[i].room << endl;
		}
	}
	else
	{
		cout << "courses.dat Not found" << endl;
	}
	dataFile.close();
}
void saveCourseStudentFile(course Course, string filePath)
{
	ofstream myFile(filePath + Course.Class + ".dat");
	if (myFile.is_open())
	{
		int n = Course.studentId.size();
		for (int i = 0; i < n; i++)
		{
			myFile << Course.studentId[i] << endl;
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
	cout << endl << setw(3) << Course.No << " - " << setw(35) << Course.Name << "(" << setw(7) << Course.Id << ") - Student: " << setw(4) << Course.studentId.size() << endl;
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
	cout << " No            : " << Course.No << endl;
	cout << " Id            : " << Course.Id << endl;
	cout << " Name          : " << Course.Name << endl;
	cout << " Class         : " << Course.Class << endl;;
	cout << " Lecturer Name : " << Course.lecturerName << endl;
	cout << " Start Date    : " << setfill('0') << setw(2) << Course.startDate.day << "/"
		<< setfill('0') << setw(2) << Course.startDate.month << "/"
		<< Course.startDate.year << endl;
	cout << " End Date      : " << setfill('0') << setw(2) << Course.endDate.day << "/"
		<< setfill('0') << setw(2) << Course.endDate.month << "/"
		<< Course.endDate.year << endl;
	cout << " Study day     : " << Course.DoW << endl;
	cout << " Start hour    : " << setfill('0') << setw(2) << Course.startHour.hour << ":"
		<< setfill('0') << setw(2) << Course.startHour.min << endl;
	cout << " End hour      : " << setfill('0') << setw(2) << Course.endHour.hour << ":"
		<< setfill('0') << setw(2) << Course.endHour.min << endl;
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
int  inputTime(courseTime& time)
{
	courseTime temp;
	int check = -1;
	while (true)
	{
		cout << "	Input hour: ";
		cin >> temp.hour;
		if (temp.hour >= 7 && temp.hour <= 19)
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
		time.hour = 0;
		time.min = 0;
		return 0;
	}
	while (true)
	{
		cout << "	Input minute: ";
		cin >> temp.min;
		if (temp.min >= 0 && temp.min <= 59)
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
		time.hour = 0;
		time.min = 0;
		return 0;
	}
	time = temp;
	return 1;
}
int  inputDate(date& Date)
{
	int check = -1;
	date temp;
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	while (true)
	{
		cout << "	Input day  :   "; cin >> temp.day;
		if ((temp.day > maxdayinmonth(temp.month, temp.year)) || (temp.day < 1))
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
		cout << "	Input month:   "; cin >> temp.month;
		if (temp.month < 1 && temp.month>12)
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
		cout << "	Input year :   "; cin >> temp.year;

		if (((ltm.tm_year + 1900) - temp.year > 20) || ((ltm.tm_year + 1900) - temp.year < -5))
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
void inputLecturer(course& Course)
{
	string username, name, degree, gender;
	cout << " Lecturer username : "; getline(cin, username);
	cout << " Lecturer name     : "; getline(cin, name);
	cout << " Lecturer degree   : "; getline(cin, degree);
	cout << " Lecturer gender  : "; getline(cin, gender);
	Course.lecturerAccount = username;
	Course.lecturerName = name;
	Course.lecturerDegree = degree;
}
void input1Course(course& newCourse)
{
	int check;
	cout << " Id                : "; getline(cin, newCourse.Id);
	cout << " Name              : "; getline(cin, newCourse.Name);
	cout << " Class             : "; getline(cin, newCourse.Class);
	inputLecturer(newCourse);
	cout << " Start date        : \n"; check = inputDate(newCourse.startDate);
	if (check == 0)
	{
		newCourse.No = -1;
		return;
	}
	cout << " End date          : \n"; check = inputDate(newCourse.endDate);
	if (check == 0)
	{
		newCourse.No = -1;
		return;
	}
	while (true)
	{
		cout << " Dow(DDD)          : "; getline(cin, newCourse.DoW);
		putchar(toupper(newCourse.DoW[0]));
		int n = newCourse.DoW.size();
		for (int i = 1; i < n; ++i)
			putchar(tolower(newCourse.DoW[i]));
		if (newCourse.DoW == "Sun" || newCourse.DoW == "Mon" || newCourse.DoW == "Tue" || newCourse.DoW == "Wed" || newCourse.DoW == "Thu" || newCourse.DoW == "Fri" || newCourse.DoW == "Sat")
		{
			break;
		}
		else
		{
			cout << "Error!!! Please check your in put. " << endl;
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
		newCourse.No = -1;
		return;
	}
	cout << " Start hour        : \n"; check = inputTime(newCourse.startHour);
	if (check == 0)
	{
		newCourse.No = -1;
		return;
	}
	cout << " End hour         : \n"; check = inputTime(newCourse.endHour);
	if (check == 0)
	{
		newCourse.No = -1;
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
		if (temp.No != -1)
			list.push_back(temp);
	}
	saveCourseList(list, filePath);
	outputCourseList(list);
}
void editCourse(vector<course>& list, string filePath)
{
	int n, check;
	while (true)
	{
		cout << "Input the course No: "; cin >> n;
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
		cout << " Id: "; getline(cin, list[n - 1].Id);
		break;
	}
	case 2:
	{
		cout << " Name: "; getline(cin, list[n - 1].Name);
		break;
	}
	case 3:
	{
		string oldFileName(filePath + list[n - 1].Name + ".dat");
		cout << " Class: "; getline(cin, list[n - 1].Class);
		string newFileName(filePath + list[n - 1].Name + ".dat");
		rename(oldFileName.c_str(), newFileName.c_str());
		break;
	}
	case 4:
	{
		inputLecturer(list[n - 1]);
		break;
	}
	case 5:
	{
		string temp;
		while (true)
		{
			cout << " Dow(DDD)          : "; getline(cin, temp);
			int sizeDoW = temp.size();
			if (sizeDoW == 3)
			{
				putchar(toupper(temp[0]));
				int sizeDoW = temp.size();
				for (int i = 1; i < sizeDoW; ++i)
					putchar(tolower(temp[i]));
				if (temp == "Sun" || temp == "Mon" || temp == "Tue" || temp == "Wed" || temp == "Thu" || temp == "Fri" || temp == "Sat")
				{
					list[n - 1].DoW = temp;
					break;
				}
				else
				{
					cout << "Error!!! Please check your in put. " << endl;
					cout << "Input (0) to break or (1) to continue: ";
					cin >> check;
					if (check == 0)
					{
						break;
					}
				}
			}
			else
			{
				cout << "Error!!! Please check your in put. " << endl;
				cout << "Input (0) to break or (1) to continue: ";
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
		cout << " Start hour        : \n"; inputTime(list[n - 1].startHour);
		break;
	}
	case 10:
	{
		cout << " End hour         : \n"; inputTime(list[n - 1].endHour);
		break;
	}
	case 11:
	{
		course newCourse;
		input1Course(newCourse);
		if (newCourse.No != -1)
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
		cout << "Input the course No: "; cin >> n;
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
	list[n - 1].studentId.clear();
	list[n - 1].studentId.shrink_to_fit();
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
		cout << "Input the studnet No: "; cin >> n;
		int studentSize = Course.studentId.size();
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
	Course.studentId.erase(Course.studentId.begin() + n - 1);
	Course.studentId.shrink_to_fit();
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
			n = Course.studentId.size();
			for (int i = 0; i < n; ++i)
			{
				if (Course.studentId[i] == Id)
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
				Course.studentId.push_back(Id);
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
void viewStudentList(course courseName)// Đợi file class của Nhật
{
	int n = courseName.studentId.size();
	if (n == 0)
	{
		cout << "There is no student in this course yet!" << endl;
	}
	else
	{
		int check;
		vector<student> stL;
		for (int i = 0; i < n; ++i)
		{
			check = 0;
			//findstudentinexistingclasses(stL,courseName.studentId[i],check,)
		}
	}
}
void sortList(vector<course>& List)
{
	sort(List.begin(), List.end(), [](const course& lhs, const course& rhs)
		{
			return lhs.Id < rhs.Id;
		});
	sort(List.begin(), List.end(), [](const course& lhs, const course& rhs)
		{
			return lhs.Name < rhs.Name;
		});
	int n = List.size();
	for (int i = 0; i < n; ++i)
	{
		List[i].No = i + 1;
	}
}
course searchCourse(string filePath, string Id)
{
	vector<course>List;
	loadDatFile(List, filePath);
	int listSize = List.size();
	for (int i = 0; i < listSize; ++i)
	{
		if (List[i].Id == Id)
			return List[i];
	}
	course Error;
	Error.No = -1;
	return Error;
}
void course::clear()
{
	No = NULL;
	Name.clear();
	Id.clear();
	Class.clear();
	lecturerAccount.clear();
	lecturerName.clear();
	lecturerDegree.clear();
	lecturerGender.clear();
	DoW.clear();
	room.clear();
	startDate.day = NULL;
	startDate.month = NULL;
	startDate.year = NULL;
	endDate.day = NULL;
	endDate.month = NULL;
	endDate.year = NULL;
	studentId.clear();
	studentId.shrink_to_fit();
	startHour.clear();
	endHour.clear();
}
void courseTime::clear()
{
	hour = NULL;
	min = NULL;
}