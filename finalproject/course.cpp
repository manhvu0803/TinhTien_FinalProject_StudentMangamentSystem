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
	myFile << "'No," << "Id," << "Name," << "Class,"
		<< "Account," << "startDate," << "endDate,"
		<< "DoW," << "startHour," << "endHour," << "Room" << endl;
	for (int i = 0; i < List.size(); i++)
	{
		myFile << List[i].No << List[i].Id << "," << List[i].Name << ","
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
	for (int i = 0; i < n; i++)
	{
		cout << "         No : " << i + 1 << endl;
		List[i].No = i;
		input1Course(List);
	}
}
void outputCourse(vector<Course> List)
{
	cout << "No" << setw(8) << "Id" << setw(17) << "Name" << setw(19) << "Class"
		<< setw(21) << "Lecturer Account" << setw(15) << "Start date" << setw(15)
		<< "End date" << setw(15) << "Day of Week" << setw(15) << "Start hour"
		<< setw(10) << "End hour" << setw(10) << "Room" << endl;
	for (int i = 0; i < List.size(); i++)
	{
		cout << List[i].No
			<< setw(10) << List[i].Id
			<< setw(25) << List[i].Name
			<< setw(10) << List[i].Class
			<< setw(15) << List[i].Account
			<< setw(20) << List[i].startDate
			<< setw(17) << List[i].endDate
			<< setw(10) << List[i].DoW
			<< setw(15) << List[i].startHour
			<< setw(12) << List[i].endHour
			<< setw(12) << List[i].Room
			<< endl;
	}
}