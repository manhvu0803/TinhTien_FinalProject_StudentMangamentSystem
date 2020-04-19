#include "course.h"

void scanCourse(vector<Course>& List)
{
	ifstream myFile("course/courseList.csv");
	if (myFile.is_open())
	{
		string line;
		string token;
		Course temp;
		getline(myFile, line);
		while (!myFile.eof())
		{
			if (line[0] == 'N')
			{			}
			else
			{
				string filePath("course/courseClass/");
				stringstream check(line);
				getline(check, token, ',');
				temp.No = stoi(token);
				getline(check, token, ',');
				temp.Id = token;
				getline(check, token, ',');
				temp.Name = token;
				getline(check, token, ',');
				temp.Class = token;
/*Lay danh sach hoc sinh*/filePath.append(token);
/*Lay danh sach hoc sinh*/filePath.append(".csv");
				getline(check, token, ',');
				temp.Account = token;
				getline(check, token, ',');
				temp.startDate = token;
				getline(check, token, ',');
				temp.endDate = token;
				getline(check, token, ',');
				temp.DoWTheory = token;
				getline(check, token, ',');
				temp.startHourTheory = token;
				getline(check, token, ',');
				temp.endHourTheory = token;
				getline(check, token, ',');
				temp.DoWExcercise = token;
				getline(check, token, ',');
				temp.startHourExcercise = token;
				getline(check, token, ',');
				temp.endHourExcercise = token;
				getline(check, token);
				temp.Room = token;
				List.push_back(temp);
			}
			getline(myFile, line);
		}
	}
	myFile.close();
}
void saveCourse( vector<Course>List)
{
	ofstream myFile("course/courseList.csv");
	if (myFile.is_open())
	{
		myFile << "No," << "Id," << "Name," << "Class,"
			<< "Account," << "startDate," << "endDate,"
			<< "DoWTheory," << "startHourTheory," << "endHourTheory," << "DoWExcercise," << "startHourExcercise," << "endHourExcercise," << "Room" << endl;
		for (int i = 0; i < List.size(); ++i)
		{
			myFile << List[i].No << "," << List[i].Id << "," << List[i].Name << ","
				<< List[i].Class << "," << List[i].Account << "," << List[i].startDate
				<< "," << List[i].endDate << "," << List[i].DoWTheory << "," << List[i].startHourTheory
				<< "," << List[i].endHourTheory << "," << List[i].DoWExcercise << "," << List[i].startHourExcercise
				<< "," << List[i].endHourExcercise << "," << List[i].Room << endl;
		}
	}
	myFile.close();
}
void input1Course(vector<Course>& List)
{
	Course temp;
	cout << " Id                    : "; getline(cin, temp.Id);
	cout << " Name                   : "; getline(cin, temp.Name);
	cout << " Class                  : "; getline(cin, temp.Class);
	cout << " Account                : "; getline(cin, temp.Account);
	cout << " Start date             : "; getline(cin, temp.startDate);
	cout << " End date               : "; getline(cin, temp.endDate);
	cout << " Day of week (Theory)   : "; getline(cin, temp.DoWTheory);
	cout << " Start hour theory      : "; getline(cin, temp.startHourTheory);
	cout << " End hour theory        : "; getline(cin, temp.endHourTheory);
	cout << " Day of week (Excercise): "; getline(cin, temp.DoWExcercise);
	cout << " Start hour Excercise   : "; getline(cin, temp.startHourExcercise);
	cout << " End hour Excercise     : "; getline(cin, temp.endHourExcercise);
	cout << " Room                   : "; getline(cin, temp.Room);
	List.push_back(temp);
}
void inputCourse(vector<Course>& List)
{
	int n;
	cout << "How many course: "; cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cout << "         No : " << i + 1 << endl;
		List[i].No = i;
		input1Course(List);
	}
	sortList(List);
}
void output1Course(Course course)
{
	cout << course.No
		<< setw(8) << course.Id
		<< setw(25) << course.Name
		<< setw(9) << course.Class
		<< setw(9) << course.Account
		<< setw(11) << course.startDate
		<< setw(11) << course.endDate
		<< setw(9) << course.DoWTheory
		<< setw(13) << course.startHourTheory
		<< setw(15) << course.endHourTheory
		<< setw(12) << course.DoWExcercise
		<< setw(18) << course.startHourExcercise
		<< setw(18) << course.endHourExcercise
		<< setw(12) << course.Room
		<< endl;
}
void outputCourse(vector<Course> List)
{
	cout << "No" << setw(6) << "Id" << setw(17) << "Name" << setw(18) << "Class"
		<< setw(10) << "Account" << setw(11) << "Start date" << setw(10)
		<< "End date" << setw(12) << "Theory day" << setw(15) << "Start: Theory"
		<< setw(15) << "End: Theory" << setw(15) << "Excercise day" << setw(17) << "Start: Excercise"
		<< setw(17) << "End: Excercise" << setw(6) << "Room" << endl;
	for (int i = 0; i < List.size(); ++i)
	{
		output1Course(List[i]);
	}
}
void outputCourseList(vector<Course> List)
{
	cout << "Course: " << endl;
	int n = List.size();
	for (int i = 0; i < n; ++i)
	{
		cout << List[i].No << " - " << List[i].Name << "(" << List[i].Id << ")"<<endl;
	}
}
void remove1Course(vector<Course>& List)
{
	int choice;
	cout << "Please choose No of Course to remove: " << endl;
	for (int i = 0; i < List.size(); ++i)
	{
		cout << "Enter " << i + 1 << ": " << List[i].Id << endl;
	}
	while (true)
	{
		cin >> choice;
		if (choice > 0 || choice <= List.size())
		{
			break;
		}
		else
		{
			cout << "Error!!!" << endl;
			cout << "Please choose again:" << endl;
		}
	}
	List[choice - 1].student.clear();
	List[choice - 1].student.shrink_to_fit();
	List.erase(List.begin() + choice - 1);
	List.shrink_to_fit();
	cout << "Course has been remove!" << endl;
}
bool realDate(date A)
{
	time_t rawtime;
	struct tm* info;
	time(&rawtime);
	info = gmtime(&rawtime);
	if (info->tm_year + 1900 - A.year <= 12 || info->tm_year + 100 - A.year >= 60)
	{
		return false;
	}
	if (A.month <= 0 || A.month > 12)
	{
		return false;
	}
	if (A.day <= 0 || A.day > maxdayinmonth(A.month, A.year));
}
date inputDate()
{
	date temp;
	do
	{
		cout << "Input Year : ";
		cin >> temp.year;
		cout << "Input month: ";
		cin >> temp.month;
		cout << "Input day :";
		cin >> temp.day;
	} while (realDate(temp));
	return temp;
}
void editCourse(vector<Course>& List)
{
	int n;
	while (true)
	{
		cout << "Choose No of course: ";
		cin >> n;
		if (n > 0 || n <= List.size() + 1)
		{
			break;
		}
		cout << "Error!" << endl;
	}
	output1Course(List[n]);
	int choice;
	cout << " (1) Id" << endl;
	cout << " (2) Name" << endl;
	cout << " (3) Class" << endl;
	cout << " (4) Account" << endl;
	cout << " (5) Start date" << endl;
	cout << " (6) End date" << endl;
	cout << " (7) Day of week (Theory)" << endl;
	cout << " (8) Start hour Theory" << endl;
	cout << " (9) End hour Theory" << endl;
	cout << " (10) Day of week (Excercise)" << endl;
	cout << " (11) Start hour Excercise" << endl;
	cout << " (12) End hour Excercise" << endl;
	cout << " (13) Room" << endl;
	while (true)
	{
		cout << " Change : ";
		cin >> choice;
		if (choice <= 13 && choice > 0)
		{
			break;
		}
		else
		{
			cout << "Error" << endl;
		}
	}
	cin.ignore(1);
	switch (choice)
	{
	case 1:
		cout << " Id : "; getline(cin, List[n].Id);
		break;
	case 2:
		cout << " Name :"; getline(cin, List[n].Name);
		break;
	case 3:
	{
		string filePath1 = "....", filePath2 = "...";
		filePath1.append(List[n].Class);
		filePath1.append(".csv");
		string temp;
		cout << " Class : "; getline(cin, temp);
		filePath2.append(temp);
		filePath2.append(".csv");
		rename(filePath1.c_str(), filePath2.c_str());
		List[n].Class = temp;
		break;
	}
	case 4:
		cout << " Account : "; getline(cin, List[n].Account);
		break;
	case 5:
		cout << " Start date : "; getline(cin, List[n].startDate);
		break;
	case 6:
		cout << " End date : "; getline(cin, List[n].endDate);
		break;
	case 7:
		cout << " Day of week (Theory): "; getline(cin, List[n].DoWTheory);
		break;
	case 8:
		cout << " Start hour Theory: "; getline(cin, List[n].startHourTheory);
		break;
	case 9:
		cout << " End hour  Theory : "; getline(cin, List[n].endHourTheory);
		break;
	case 10:
		cout << " Day of week (Excercise): "; getline(cin, List[n].DoWTheory);
		break;
	case 11:
		cout << " Start hour Excercise : "; getline(cin, List[n].startHourTheory);
		break;
	case 12:
		cout << " End hour Excercise : "; getline(cin, List[n].endHourTheory);
		break;
	case 13:
		cout << " Room        : "; getline(cin, List[n].Room);
		break;
	}
	saveCourse(List);
	cout << "After edit: " << endl;
	output1Course(List[n]);
	sortList(List);
}
void sortList(vector<Course>& List)
{
	sort(List.begin(), List.end(), [](const Course& lhs, const Course& rhs)
		{
			return lhs.Id < rhs.Id;
		});
	sort(List.begin(), List.end(), [](const Course& lhs, const Course& rhs)
		{
			return lhs.Name < rhs.Name;
		});
	for (int i = 0; i < List.size(); ++i)
	{
		List[i].No = i + 1;
	}
}
void viewStudentList(Course courseName)
{
	cout << "No" << "Id" << "Last name" << "First name" << "Day of birth";
	for (int i = 0; i < courseName.student.size(); ++i)
	{
		cout << courseName.student[i].id;
	}
}
void input1Student(student& newStudent)
{
	cout << "Id :"; cin >> newStudent.id;
	cin.ignore(1);
	cout << "Last name: "; getline(cin, newStudent.Lastname);
	cout << "First name: "; getline(cin, newStudent.Firstname);
	while (true)
	{
		cout << "Enter 0: Male " << endl;
		cout << "Enter 1: Female " << endl;
		cout << "Gender : "; cin >> newStudent.gender;
		if (newStudent.gender == '0' || newStudent.gender == '1')
		{
			break;
		}
		else
		{
			cout << "False";
		}
	}
	cout << "Day of birth : ";
	newStudent.DoB = inputDate();
}
void inputNewStudent(vector<Course>& List)
{
	scanCourse(List);
	if (List.size() == 0)
	{
		cout << "There is no course this semester!" << endl;
		return;
	}
	int course;
	cout << "Please choose No of Course to add student: " << endl;
	for (int i = 0; i < List.size(); ++i)
	{
		cout << "(" << i + 1 << "): " << List[i].Id << endl;
	}
	while (true)
	{
		cin >> course;
		if (course > 0 || course <= List.size())
		{
			break;
		}
		else
		{
			cout << "Error!!!" << endl;
			cout << "Please choose again:" << endl;
		}
	}
	student newStudent;
	input1Student(newStudent);
	for (int i = 0; i < List.size(); ++i)
	{
		if (newStudent.id == List[course - 1].student[i].id)
		{
			cout << "Student has already been attended!" << endl;
			return;
		}
	}
	List[course - 1].student.push_back(newStudent);
}