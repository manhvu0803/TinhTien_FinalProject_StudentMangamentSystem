#include "academicYear.h"

void academicYearMenu()
{
	string filePath = ("data/course/year.dat");
	cout << setfill('=') << setw(50) << "=" << endl;
	cout << "*" << setfill('-') << setw(27) << "ACADEMIC YEAR MENU" << setfill('-') << setw(22) << "*" << endl;
	cout << setfill('=') << setw(50) << "=" << endl;
	int cont = 1;
	int choice = -1;
	tt::vector<string> year;
	scanYear(filePath, year);
	while (cont != 0)
	{
		cont = 1;
		while (choice != 0)
		{
			outputYear(year);
			cout << "\nEnter 0: To exit\n";
			cout << "Enter 1: To change course in semester\n";
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice >= 0 && choice <= 1)
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
		default:
			cont = 0;
			break;
		case 1:
			changeToSemester(year);
			break;
		}
	}
	year.clear();
}
void outputYear(tt::vector<string> year)
{
	cout << "Year:\n";
	if (year.size() == 0)
	{
		cout << "No data yet!\n";
	}
	for (int i = 0; i < year.size(); ++i)
	{
		cout << "(" << i + 1 << ")	" << year[i] << endl;
	}
}
void scanYear(string filePath, tt::vector<string>& year)
{
	ifstream myFile(filePath);
	string temp;
	while (myFile >> temp)
	{
		temp[4] = '-';
		year.push_back(temp);
	}
	myFile.close();
}
void changeToSemester(tt::vector<string> year)
{
	cout << "/n/n/";
	outputYear(year);
	int decide;
	while (true)
	{
		cout << "Input the year no. :"; cin >> decide;
		if (decide >= 1 && decide <= year.size())
		{
			break;
		}
		else
		{
			cout << "Error!!!No available year!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> decide;
			if (decide == 0)
			{
				break;
			}
		}
	}
	if (decide != 0)
	{
		char newString[5];
		year[decide - 1].copy(newString,4,0);
		semesterMenu(atoi(newString));
	}
}