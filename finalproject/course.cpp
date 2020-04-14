#include "course.h"

void scanCourse(ifstream& myFile, vector<Course>& List)
{
	string line;
	string token;
	Course temp;
	getline(myFile, line);
	while (!myFile.eof())
	{
		if (line[0] == 'N')
		{

		}
		else
		{
			stringstream check(line);
			getline(check, token, ',');
			temp.No = stoi(token);
			getline(check, token, ',');
			temp.Id = token;
			getline(check, token, ',');
			temp.Name = token;
			getline(check, token, ',');
			temp.Class = token;
			getline(check, token, ',');
			temp.Account = token;
			getline(check, token, ',');
			temp.startDate = token;
			getline(check, token, ',');
			temp.endDate = token;
			getline(check, token, ',');
			temp.DoW = token;
			getline(check, token, ',');
			temp.startHour = token;
			getline(check, token, ',');
			temp.endHour = token;
			getline(check, token);
			temp.Room = token;
			List.push_back(temp);
		}
		getline(myFile, line);
	}
}
void saveCourse(ofstream& myFile, vector<Course>List)
{
	myFile << "No," << "Id," << "Name," << "Class,"
		<< "Account," << "startDate," << "endDate,"
		<< "DoW," << "startHour," << "endHour," << "Room" << endl;
	for (int i = 0; i < List.size(); ++i)
	{
		myFile <<  List[i].No<<","<<List[i].Id << "," << List[i].Name << ","
			   << List[i].Class << "," << List[i].Account << "," << List[i].startDate
		       << "," << List[i].endDate << "," << List[i].DoW << "," << List[i].startHour
			   << "," << List[i].endHour << "," << List[i].Room << endl;
	}
}
void input1Course(vector<Course>& List)
{
	Course temp;
	cout << " Id          : "; getline(cin, temp.Id);
	cout << " Name        : "; getline(cin, temp.Name);
	cout << " Class       : "; getline(cin, temp.Class);
	cout << " Account     : "; getline(cin, temp.Account);
	cout << " Start date  : "; getline(cin, temp.startDate);
	cout << " End date    : "; getline(cin, temp.endDate);
	cout << " Day of week : "; getline(cin, temp.DoW);
	cout << " Start hour  : "; getline(cin, temp.startHour);
	cout << " End hour    : "; getline(cin, temp.endHour);
	cout << " Room        : "; getline(cin, temp.Room);
	List.push_back(temp);
}
void inputCourse(vector<Course>& List, int& n)
{
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
		<< setw(10) << course.Id
		<< setw(25) << course.Name
		<< setw(10) << course.Class
		<< setw(15) << course.Account
		<< setw(20) << course.startDate
		<< setw(17) << course.endDate
		<< setw(10) << course.DoW
		<< setw(15) << course.startHour
		<< setw(12) << course.endHour
		<< setw(12) << course.Room
		<< endl;
}
void outputCourse(vector<Course> List)
{
	cout << "No" << setw(8) << "Id" << setw(17) << "Name" << setw(19) << "Class"
		<< setw(21) << "Lecturer Account" << setw(15) << "Start date" << setw(15)
		<< "End date" << setw(15) << "Day of Week" << setw(15) << "Start hour"
		<< setw(10) << "End hour" << setw(10) << "Room" << endl;
	for (int i = 0; i < List.size(); ++i)
	{
		output1Course(List[i]);
	}
}
void delete1Course(vector<Course>& List, int n)// n là No của course
{
	List.erase(List.begin() + n - 1);
}
void editCourse(vector<Course>& List, int n)// n là No của course
{
	int choice;
	cout << " (0) No" << endl;
	cout << " (1) Id" << endl;
	cout << " (2) Name" << endl;
	cout << " (3) Class" << endl;
	cout << " (4) Account" << endl;
	cout << " (5) Start date" << endl;
	cout << " (6) End date" << endl;
	cout << " (7) Day of week" << endl;
	cout << " (8) Start hour" << endl;
	cout << " (9) End hour" << endl;
	cout << " (10) Room" << endl;
	while (true)
	{
		cout << " Change : ";
		cin >> choice;
		if (choice <= 10 && choice >= 0)
		{
			break;
		}
		else
		{
			cout << "Error"<<endl;
		}
	}
	cin.ignore(1);
	switch (choice)
	{
	default:
		cout << " No : "; cin >> List[n].No;
	case 1:
		cout << " Id : "; getline(cin, List[n].Id);
		break;
	case 2:
		cout << " Name :"; getline(cin, List[n].Name);
		break;
	case 3:
		cout << " Class : "; getline(cin, List[n].Class);
		break;
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
		cout << " Day of week : "; getline(cin, List[n].DoW);
		break;
	case 8:
		cout << " Start hour : "; getline(cin, List[n].startHour);
		break;
	case 9:
		cout << " End hour    : "; getline(cin, List[n].endHour);
		break;
	case 10:
		cout << " Room        : "; getline(cin, List[n].Room);
		break;
	}
	ofstream myFile("course.csv");
	if (myFile.is_open())
	{
		cout << "After edit: " << endl;
		output1Course(List[n]);
		sortList(List);
		saveCourse(myFile, List);
	}
	else
	{
		cout << "Error saving edit";
	}
	myFile.close();
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