#include "course.h"
#define _CRT_SECURE_NO_WARNINGS

tt::vector<tt::course> emptyVec;
tt::vector<tt::vector<int>>emptyStudents;
void courseMenu(int year, string semester, int mode)
{
	bool checkInput = true;
	string filePath = ("data/course/");
	filePath.append(to_string(year));
	filePath.append("-");
	filePath.append(to_string(year + 1));
	filePath.append("/");
	filePath.append(semester);
	filePath.append("/");
	int cont = 1;
	int choice = -1, title = -1, check;
	tt::vector<tt::course> List;
	tt::vector<tt::vector<int>> students;
	titleName(year, semester);
	title = 0;
	loadDatFile(List, students, filePath);
	while (cont != 0)
	{
		if (title != 0)
		{
			titleName(year, semester);
			title = 0;
		}
		if (mode == 1)
		{
			if (List.size() == 0)
			{
				tt::clearConsole();
				titleName(year, semester);
				cout << "\nNothing to do here!\nPress Etner to return...";
				getchar();
				tt::clearConsole();
				cont = 0;
			}
			else
				while (choice != 0)
				{
					checkInput = true;
					cout << " Enter 0: To exit" << endl;
					cout << " Enter 1: View course list" << endl;
					cout << " Enter 2: View student list" << endl;
					cout << " Enter your choice: ";
					checkInput = tt::cinIg(cin, choice, true);
					tt::clearConsole();
					if (choice >= 0 && choice <= 2 && checkInput)
					{
						if (choice == 1) choice += 4;
						if (choice == 2) choice += 6;
						break;
					}
					else
					{
						cout << "Error! Choose agian:" << endl;
						getchar();
						tt::clearConsole();
					}
					titleName(year, semester);
				}
		}
		else
		{
			while (choice != 0)
			{
				checkInput = true;
				if (List.size() == 0)
				{
					cout << " Enter 0: To exit" << endl;
					cout << " Enter 1: Import courses" << endl;
					cout << " Enter your choice: ";
					checkInput = tt::cinIg(cin, choice, true);
					tt::clearConsole();
					if ((choice == 0 || choice == 1) && checkInput)
					{
						break;
					}
					else
					{
						cout << "Error! Choose agian:" << endl;
						getchar();
						tt::clearConsole();
					}
				}
				else
				{
					cout << " Enter 0: To exit" << endl;
					cout << " Enter 1: Import courses" << endl;
					cout << " Enter 2: Add new course" << endl;
					cout << " Enter 3: Edit course" << endl;
					cout << " Enter 4: Remove a course" << endl;
					cout << " Enter 5: View course list" << endl;
					cout << " Enter 6: Add a student to a course" << endl;
					cout << " Enter 7: Remove a student" << endl;
					cout << " Enter 8: View student list" << endl;
					cout << " Enter your choice: ";
					checkInput = tt::cinIg(cin, choice, true);
					tt::clearConsole();
					if ((choice >= 0 && choice <= 8) && checkInput)
					{
						break;
					}
					else
					{
						cout << "Error! Choose agian:" << endl;
						getchar();
						tt::clearConsole();
					}
				}
				titleName(year, semester);
			}
		}
		switch (choice)
		{
		case 0:
		{
			cont = 0;
			break;
		}
		case 1:
		{
			tt::vector<tt::course> moreList;
			importCsvFile(moreList, students, filePath);
			int newSize = moreList.size() + List.size();
			for (int i = List.size(); i < newSize; ++i)
			{
				List.push_back(moreList[newSize - i - 1]);
			}
			saveCourseList(List, students, filePath);
			moreList.clear();
			moreList.shrink_to_fit();
			title = 1;
			break;
		}
		case 2:
		{
			tt::course temp;
			tt::vector<int>classStudents;
			cout << "New course: \n";
			input1Course(temp, classStudents, List.size());
			if (temp.number != -1)
			{
				List.push_back(temp);
				students.push_back(classStudents);
				saveCourseList(List, students, filePath);
			}
			classStudents.clear();
			title = 1;
			break;
		}
		case 3:
		{
			outputCourseList(List, students);
			editCourse(List, students, filePath);
			saveCourseList(List, students, filePath);
			title = 1;
			break;
		}
		case 4:
		{
			deleteCourse(List, students, filePath);
			title = 1;
			break;
		}
		case 5:
		{
			outputSchedule(List);
			title = 1;
			break;
		}
		case 6:
		{
			int n;
			outputCourseList(List, students);
			title = 1;
			while (true)
			{
				checkInput = true;
				check = -1;
				cout << "\nInput the course no: "; checkInput = tt::cinIg(cin, n, true);
				tt::clearConsole();
				int listSize = List.size();
				if ((n <= 0 || n > listSize) && !checkInput)
				{
					cout << "Error!!!No available course!!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					cin >> check;
					tt::clearConsole();
					if (check == 0)
					{
						break;
					}
				}
				else
				{
					break;
				}
				outputCourseList(List, students);
			}
			if (check != 0)
			{
				int id = 0;
				output1Course(List[n - 1], students[n - 1]);
				int studentSize6 = students[n - 1].size();
				add1Student(List[n - 1], students[n - 1]);
				if (studentSize6 < students[n - 1].size())
				{
					char name[10];
					_itoa_s(students[n - 1][studentSize6], name, 10);
					ofstream myFile(filePath + List[n - 1].id + "/" + name + ".dat");
					myFile.close();
				}
				saveCourseList(List, students, filePath);
			}
			title = 1;
			break;
		}
		case 7:
		{
			int n;
			outputCourseList(List, students);
			while (true)
			{
				checkInput = true;
				check = -1;
				cout << "Input the course no: "; checkInput = tt::cinIg(cin, n, true);
				tt::clearConsole();
				int listSize = List.size();
				if (n <= 0 || n > listSize || !checkInput)
				{
					cout << "Error!!!No available course!!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					checkInput = tt::cinIg(cin, check, true);
					tt::clearConsole();
					if (!checkInput)check = 0;
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
				remove1Student(students[n - 1]);
				saveCourseList(List, students, filePath);
			}
			title = 1;
			break;
		}
		case 8:
		{
			int n, check;
			outputCourseList(List, students);
			if (List.size() != 0)
			{
				while (true)
				{
					check = -1;
					cout << "\nInput the course no: "; checkInput = tt::cinIg(cin, n, true);
					tt::clearConsole();
					int listSize = List.size();
					if (n <= 0 || n > listSize || !checkInput)
					{
						check = 0;
						cout << "Error!!!No available course!!!" << endl;
						cout << "Input (0) to break or (1) to continue: ";
						checkInput = tt::cinIg(cin, check, true);
						tt::clearConsole();
						if (!checkInput)check = 0;
						if (check == 0)
						{
							break;
						}
					}
					else
					{
						break;
					}
					outputCourseList(List, students);
				}
				if (check == -1)
				{
					tt::vector<int>classStudents;
					for (int i = 0; i < students[n - 1].size(); ++i)
					{
						classStudents.push_back(students[n - 1][i]);
					}
					cout << "Course: " << List[n - 1].name << "(" << List[n - 1].id << ") \n\n";
					viewStudentList(classStudents);
				}
			}
			cout << "Press Enter to continue... ";
			getchar();
			tt::clearConsole();
			title = 1;
			break;
		}
		}
	}
	makeCourseData(List, students, filePath);
	List.clear();
	students.clear();
	tt::clearConsole();
}
void makeCourseData(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	string path = "./";
	path.append(filePath);
	char name[10];
	for (int i = 0; i < list.size(); ++i)
	{
		tt::makeDir(path + list[i].id);
		for (int j = 0; j < students[i].size(); ++j)
		{
			_itoa_s(students[i][j], name, 10);
			ofstream myFile(filePath + list[i].id + "/" + name + ".dat");
			myFile.close();
		}
	}
}
void loadCsvFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	clss theClass;
	int count = 1;
	if (filePath.compare(filePath.size() - 4, 4, ".csv") != 0)
	{
		cout << "Wrong data file";
		getchar();
		list = emptyVec;
		students = emptyStudents;
		tt::clearConsole();
		return;
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
				getline(check, token, ',');
				temp.number = stoi(token);
				getline(check, token, ',');
				temp.id = token;
				getline(check, token, ',');
				temp.name = token;
				getline(check, token, ',');
				token = tt::capitalize(token);
				temp.className = token;
				studentList = theClass.getClass(temp.className);
				int n = studentList.size();
				for (int i = 0; i < n; ++i)
				{
					classStudents.push_back(studentList[i].id);
				}
				students.push_back(classStudents);
				classStudents.clear();
				if (studentList.size() == 0)
				{
					temp.number = -1;
					notFound.push_back(token);
				}
				getline(check, token, ',');
				getline(check, token, ',');
				temp.lecturer = token;
				getline(check, token, ',');
				getline(check, token, ',');
				getline(check, token, ',');
				temp.startDate = getDate(token);
				getline(check, token, ',');
				temp.endDate = getDate(token);
				getline(check, token, ',');
				token = tt::capitalize(token);
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
				{
					temp.number = count;
					list.push_back(temp);
					count++;
				}
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
			getchar();
			tt::clearConsole();
			notFound.clear();
			notFound.shrink_to_fit();
		}
	}
	else
	{
		cout << "File not found" << endl;
		getchar();
		tt::clearConsole();
	}
	csvFile.close();
}
tt::date getDate(string dato)
{
	int _case;
	tt::date theDate;
	stringstream check(dato);
	string temp;
	if (dato.find('-') == string::npos) _case = 1;
	else _case = 0;
	switch (_case)
	{
	default:
		getline(check, temp, '-');
		theDate.m = stoi(temp);
		getline(check, temp, '-');
		theDate.d = stoi(temp);
		getline(check, temp);
		theDate.y = stoi(temp);
		break;
	case 1:
		getline(check, temp, '/');
		theDate.m = stoi(temp);
		getline(check, temp, '/');
		theDate.d = stoi(temp);
		getline(check, temp);
		theDate.y = stoi(temp);
		break;
	}
	return theDate;
}
void loadDatFile(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	ifstream myFile(filePath + "course.dat");
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
			students.push_back(classStudents);
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
			classStudents.clear();
		}
		for (int i = 0; i < list.size(); ++i)
		{
			list[i].number = i + 1;
		}
	}
	else
	{
		cout << "course.dat not found" << endl;
		getchar();
		tt::clearConsole();
		return;
	}
	myFile.close();
}
void loadCourseStudentFile(tt::course& Course, tt::vector<int>& classStudents, string filePath)
{
	ifstream myFile(filePath + Course.id + ".dat");
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
	ofstream dataFile(filePath + "course.dat");
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
		cout << "\n course.dat not found" << endl;
	}
	dataFile.close();
}
void saveCourseStudentFile(tt::course& Course, tt::vector<int>& classStudent, string filePath)
{
	ofstream myFile(filePath + Course.id + ".dat");
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
	bool checkInput = true;
	string newPath;
	int choice = -1;
	while (true)
	{
		cout << "Input your file address: ";
		cin >> newPath;
		tt::clearConsole();
		if (newPath.size() < 5)
		{
			cout << "Error!!Please input full file name and type\n";
			cout << "Input (0) to break or (1) to continue: ";
			checkInput = tt::cinIg(cin, choice, true);
			tt::clearConsole();
			if (!checkInput)choice = 0;
		}
		else
		{
			break;
		}
		if (choice == 0)break;
	}
	if (choice != 0)
	{
		loadCsvFile(list, students, newPath);
		outputCourseList(list, students);
		cout << "\nPress Enter to continue...	";
		if (list.size() != 0)
			getchar();
		getchar();
		tt::clearConsole();
	}

}
void output1Course(tt::course& Course, tt::vector<int>& classStudent)
{
	cout << endl << setfill(' ') << setw(3) << Course.number << " - " << setw(35) << left << Course.name << "(" << Course.id << ") - Students: " << setw(4) << classStudent.size() << right << endl;
}
void outputCourseList(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students)
{
	cout << "Course:\n";
	int n = list.size();
	if (n == 0)
	{
		cout << "No data!!\n";
	}
	else
		for (int i = 0; i < n; ++i)
		{
			list[i].number = i + 1;
			output1Course(list[i], students[i]);
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
		cout << " Study day     : Saturday";
		break;
	}
	case 6:
	{
		cout << " Study day     : Sunday";
		break;
	}
	}
	cout << "\n Start hour    : " << setfill('0') << setw(2) << Course.startTime.h << ":"
		<< setfill('0') << setw(2) << Course.startTime.m << endl;
	cout << " End hour      : " << setfill('0') << setw(2) << Course.endTime.h << ":"
		<< setfill('0') << setw(2) << Course.endTime.m << endl;
	cout << " Room          : " << Course.room;

}
void outputSchedule(tt::vector<tt::course>& list)
{
	cout << "Schedule:  " << endl;
	int n = list.size();
	if (n == 0)
	{
		cout << "No data" << endl;
	}
	cout << endl << setfill('=') << setw(49) << "=" << endl;
	for (int i = 0; i < n; ++i)
	{
		output1CourseData(list[i]);
		cout << endl << setfill('=') << setw(49) << "=" << endl;
	}
	cout << "\nPress Enter to return.... ";
	getchar();
	tt::clearConsole();
}
int  inputTime(tt::time& courseTime)
{
	bool checkInput = true;
	tt::time temp;
	int check = -1;
	while (true)
	{
		checkInput = true;
		cout << "	  Input hour: ";
		checkInput = tt::cinIg(cin, temp.h, true);
		if (temp.h >= 7 && temp.h <= 19 && checkInput)
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
		checkInput = true;
		cout << "	Input minute: ";
		checkInput = tt::cinIg(cin, temp.m, true);
		if (temp.m >= 0 && temp.m <= 59 && checkInput)
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
	bool checkInput = true;

	int check = -1;
	tt::date temp;
	time_t now = std::time(0);
	tm ltm;
	localtime_s(&ltm, &now);

	while (true)
	{
		checkInput = true;
		cout << "	Input month:   "; checkInput = tt::cinIg(cin, temp.m, true);
		if (temp.m < 1 && temp.m>12 || !checkInput)
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
		checkInput = true;
		cout << "	Input year :   "; checkInput = tt::cinIg(cin, temp.y, true);;

		if (((ltm.tm_year + 1900) - temp.y > 20) || ((ltm.tm_year + 1900) - temp.y < -5) || !checkInput)
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
		checkInput = true;
		cout << "	Input day  :   "; checkInput = tt::cinIg(cin, temp.d, true);
		if ((temp.d > maxdayinmonth(temp.m, temp.y)) || (temp.d < 1) || !checkInput)
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
void input1Course(tt::course& newCourse, tt::vector<int>& classStudents, int num)
{
	bool checkInput = true;
	int check;
	newCourse.number = num;
	cout << " Id                : "; getline(cin, newCourse.id);
	cout << " Name              : "; getline(cin, newCourse.name);
	cout << " Class             : "; getline(cin, newCourse.className);
	cout << " Lecturer name     : "; getline(cin, newCourse.lecturer);
	cout << " Start date        : \n"; check = inputDate(newCourse.startDate);
	if (check == 0)
	{
		newCourse.number = -1;
		tt::clearConsole();
		return;
	}
	cout << "\n";
	cout << " End date          : \n"; check = inputDate(newCourse.endDate);
	if (check == 0)
	{
		tt::clearConsole();
		newCourse.number = -1;
		return;
	}
	cout << "\n";
	while (true)
	{
		check = 1;
		cout << "Enter (0): Monday" << endl;
		cout << "Enter (1): Tuesday" << endl;
		cout << "Enter (2): Wednesday" << endl;
		cout << "Enter (3): Thursday" << endl;
		cout << "Enter (4): Friday" << endl;
		cout << "Enter (5): Saturday" << endl;
		cout << "Enter (6): Sunday" << endl;
		cout << " Dow     : "; check = tt::cinIg(cin, newCourse.DoW, true);
		if (newCourse.DoW >= 0 && newCourse.DoW <= 6 || !check)
		{
			break;
		}
		else
		{
			cout << "Error!!!Please check your input" << endl;
			cout << "Enter (0) to break or (1) to continue: ";
			cin >> check;
			tt::clearConsole();
			if (check == 0)
			{
				break;
			}
		}
	}
	if (check == 0)
	{
		newCourse.number = -1;
		tt::clearConsole();
		return;
	}
	cout << "\n";
	cout << " Start hour         : \n"; check = inputTime(newCourse.startTime);
	if (check == 0)
	{
		newCourse.number = -1;
		tt::clearConsole();
		return;
	}
	cout << "\n";
	cout << " End hour           : \n"; check = inputTime(newCourse.endTime);
	if (check == 0)
	{
		newCourse.number = -1;
		tt::clearConsole();
		return;
	}
	cout << "\n";
	cin.ignore(1);
	cout << " Room: "; getline(cin, newCourse.room);

	tt::vector<tt::student> Student;
	clss theClass;
	Student = theClass.getClass(newCourse.id);
	if (Student.size() != 0)
	{
		int n = Student.size();
		for (int i = 0; i < n; ++i)
		{
			classStudents.push_back(Student[i].id);
		}
		tt::clearConsole();
		cout << "New course has been created!";
		getchar();
		tt::clearConsole();
	}
	else
	{
		newCourse.number = -1;
		tt::clearConsole();
		cout << "Class not found!\n";
		cout << "Press Enter to return! ";
		getchar();
		tt::clearConsole();
	}

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
		input1Course(temp, classStudents, list.size());
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
	bool checkInput = true;
	int n, check = -1;
	while (true)
	{
		cout << "Input the course no: "; checkInput = tt::cinIg(cin, n);
		tt::clearConsole();
		int listSize = list.size();
		if (n <= 0 || n > listSize || !checkInput)
		{
			cout << "Error!!!No available course!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			checkInput = tt::cinIg(cin, check);
			if (!checkInput)check = 0;
			tt::clearConsole();
			if (check == 0)
			{
				return;
			}
		}
		else
		{
			break;
		}
		outputCourseList(list, students);
	}
	int choice;
	output1Course(list[n - 1], students[n - 1]);
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
		cout << "Input: "; checkInput = tt::cinIg(cin, choice);
		tt::clearConsole();
		if (choice <= 0 || choice > 11 || !checkInput)
		{
			cout << "Error!!!No choice available!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			checkInput = tt::cinIg(cin, check);
			if (!checkInput)check = 0;
			if (check == 0)
			{
				return;
			}
		}
		else
		{
			break;
		}
		output1Course(list[n - 1], students[n - 1]);
		cout << "Please enter your decision: " << endl;
		cout << "Enter (1) : Id" << endl;
		cout << "Enter (2) : Name " << endl;
		cout << "Enter (3) : Class" << endl;
		cout << "Enter (4) : Lecturer" << endl;
		cout << "Enter (5) : Day of Week" << endl;
		cout << "Enter (6) : Room" << endl;
		cout << "Enter (7) : Start date" << endl;
		cout << "Enter (8) : End date" << endl;
		cout << "Enter (9) : Start Hour" << endl;
		cout << "Enter (10): End Hour" << endl;
		cout << "Enter (11):  Whole course" << endl;
	}
	cin.ignore(1);
	switch (choice)
	{
	case 1:
	{
		string oldFileName(filePath + list[n - 1].id + ".dat");
		cout << " Id: "; getline(cin, list[n - 1].id);
		string newFileName(filePath + list[n - 1].id + ".dat");
		rename(oldFileName.c_str(), newFileName.c_str());
		break;
	}
	case 2:
	{
		cout << " Name: "; getline(cin, list[n - 1].name);

		break;
	}
	case 3:
	{
		cout << " Class: "; getline(cin, list[n - 1].className);

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
			cout << " (5): Saturday" << endl;
			cout << " (6): Sunday" << endl;
			cout << " Dow          : "; checkInput = tt::cinIg(cin, DoW);
			if (DoW >= 0 && DoW <= 6 && checkInput)
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
		input1Course(newCourse, classStudent, n);
		if (newCourse.number != -1)
		{
			students.erase(n - 1);
			students.push_back(classStudent);
			list[n - 1] = newCourse;
		}
		classStudent.clear();
		break;
	}
	}
	tt::clearConsole();
	cout << "After edit: \n";
	output1CourseData(list[n - 1]);
	cout << "\nPress Enter to continue... ";
	getchar();
	tt::clearConsole();
}
void deleteCourse(tt::vector<tt::course>& list, tt::vector<tt::vector<int>>& students, string filePath)
{
	bool checkInput = true;
	int n, check;
	outputCourseList(list, students);
	while (true)
	{
		cout << "\nInput the course no: "; checkInput = tt::cinIg(cin, n);
		tt::clearConsole();
		int listSize = list.size();
		if (n <= 0 || n > listSize || !checkInput)
		{
			cout << "Error!!!No available course!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			checkInput = tt::cinIg(cin, check);
			if (!checkInput)check = 0;
			tt::clearConsole();
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
	path += list[n - 1].id;
	path += ".dat";
	remove(path.c_str());
	if (students.size() != 1)
	{
		students.erase(n - 1);
		students.shrink_to_fit();
	}
	else
	{
		students = emptyStudents;
	}
	cout << "Course: " << list[n - 1].name << " is deleted.\n";

	if (list.size() != 1)
	{
		list.erase(n - 1);
		list.shrink_to_fit();
		for (int i = 0; i < list.size(); ++i)
		{
			list[i].number = i + 1;
		}
	}
	else
	{
		list = emptyVec;
	}
	saveCourseList(list, students, filePath);
	getchar();
	tt::clearConsole();
}
void remove1Student(tt::vector<int>& classStudent)
{
	bool checkInput = true;
	int n, check;
	while (true)
	{
		viewStudentList(classStudent);
		cout << "Input the studnet no: "; cin >> n;
		tt::clearConsole();
		int studentSize = classStudent.size();
		if (n <= 0 || n > studentSize)
		{
			cout << "Error!!!No student at that position!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			checkInput = tt::cinIg(cin, check);
			tt::clearConsole();
			if (check == 0 || !checkInput)
			{
				return;
			}
		}
		else
		{
			break;
		}
	}
	cout << "Student: " << classStudent[n - 1] << " is deleted!!!\n";
	cout << "Press Enter to continune... ";
	getchar();
	tt::clearConsole();
	classStudent.erase(n - 1);
	classStudent.shrink_to_fit();
}
void add1Student(tt::course& Course, tt::vector<int>& classStudents)
{
	bool checkInput = true;
	int Id, check;
	int n;
	viewStudentList(classStudents);
	while (true)
	{
		checkInput = true;
		check = -1;
		cout << "Student id: "; checkInput = tt::cinIg(cin, Id, true);
		clss theClass;
		tt::student hi = theClass.getStudent(Id);
		if (hi.number == -1)Id = 0;
		tt::clearConsole();
		if (((int)log10(Id) + 1 == 7 || (int)log10(Id) + 1 == 8) && checkInput)
		{
			n = classStudents.size();
			for (int i = 0; i < n; ++i)
			{
				if (classStudents[i] == Id)
				{
					cout << "Student have already been here!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					checkInput = tt::cinIg(cin, check, true);
					tt::clearConsole();
					if (!checkInput)check = 0;
					if (check == 0)
					{
						break;
					}
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
			checkInput = tt::cinIg(cin, check, true);
			tt::clearConsole();
			if (!checkInput)check = 0;
			if (check == 0)
			{
				break;
			}
		}
		viewStudentList(classStudents);
	}
	if (check != 0)
	{
		cout << "Student " << Id << " has been added!";
		getchar();
		tt::clearConsole();

	}
}
void addStudent(tt::course& Course, tt::vector<int>& classStudents)// Optional
{
	int num;
	cout << "Numbers of new student: "; cin >> num;
	for (int i = 0; i < num; ++i)
	{
		add1Student(Course, classStudents);
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
		clss theClass;
		tt::student temp;
		tt::vector<tt::student> _class;
		tt::vector<int> Drop;
		for (int i = 0; i < n; ++i)
		{
			temp = theClass.getStudent(classStudent[i]);
			if (temp.id == -1)
			{
				Drop.push_back(classStudent[i]);
				classStudent.erase(i);
				classStudent.shrink_to_fit();
				n--;
				i--;
			}
			else
			{
				temp.number = i + 1;
				_class.push_back(temp);
			}
		}
		if (_class.size() != 0)
			theClass.showClass(_class);
		else
		{
			cout << "No student found!\n\n";
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
int maxdayinmonth(int month, int year)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		return 31;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return 30;
	}
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return 29;
	}
	return 28;
}
void titleName(int year, string semester)
{
	cout << setfill('=') << setw(50) << "=" << endl;
	cout << "*" << right << setfill('-') << setw(29) << "COURSE MENU" << setfill('-') << setw(20) << "*" << endl;
	cout << "*" << setfill('-') << setw(20) << year << "-" << year + 1 << ": " << semester << setfill('-') << setw(19) << "*" << endl;
	cout << setfill('=') << setw(50) << "=" << endl;
}
