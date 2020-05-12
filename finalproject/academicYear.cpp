#include "academicYear.h"

void academicYearMenu()
{
	int check = -1;
	string filePath = ("data/course/year.dat");

	int cont = 1;
	int choice = -1;
	tt::vector<string> year;
	scanYear(filePath, year);
	while (cont != 0)
	{
		if (check != 0)
		{
			cout << setfill('=') << setw(50) << "=" << endl;
			cout << "*" << setfill('-') << setw(34) << "ACADEMIC YEAR MENU" << setfill('-') << setw(15) << "*" << endl;
			cout << setfill('=') << setw(50) << "=" << endl;
			check = 0;
		}
		cont = 1;
		while (choice != 0)
		{
			outputYear(year);
			cout << "\nEnter 0: To exit\n";
			cout << "Enter 1: Create new academic year\n";
			cout << "Enter 2: To change semester in academic year\n";
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice >= 0 && choice <= 2)
			{
				break;
			}
			else
			{
				cout << "Error!!! Choose agian:" << endl;
			}
		}
		switch (choice)
		{
		default:
			cont = 0;
			break;
		case 1:
			createYear(filePath, year);
			cout << "\n\n\n\n\n";
			check = -1;
			break;
		case 2:
			changeToSemester(year);
			check = 1;
			cout << "\n\n\n\n\n";
			break;
		}
	}
	year.clear();
}
void outputYear(tt::vector<string>& year)
{
	cout << "Year:\n";
	if (year.size() == 0)
	{
		cout << "No data yet!\n";
	}
	int n = year.size();
	for (int i = 0; i < n; ++i)
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
	sortYear(year);
}
void changeToSemester(tt::vector<string>& year)
{
	cout << "\n\n";
	outputYear(year);
	int decide;
	while (true)
	{
		cout << "Input the year No. :	"; cin >> decide;
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
		year[decide - 1].copy(newString, 4, 0);
		cout << "\n\n\n\n\n";
		semesterMenu(atoi(newString));
	}
}
void sortYear(tt::vector<string>& year) {
	sort(year.begin(), year.end(), [](const string& lhs, const string& rhs)
		{
			return lhs < rhs;
		});

}
void saveYear(string filePath, tt::vector<string>& year)
{
	ofstream myFile(filePath);
	if (!myFile.is_open())
	{
		cout << "year.dat file is missing!";
	}
	else
	{
		for (string temp : year)
		{
			myFile << temp << endl;
		}
	}
	myFile.close();
}
void createYear(string filePath, tt::vector<string>& year)
{
	string input;
	int decide = -1;
	bool seen = false;
	cout << "Input: 20XX-20XX\n";
	while (true)
	{
		cout << "Input your academic year: "; cin >> input;
		input[4] = '-';
		if (input.size() != 9)
		{
			cout << "Your input " << input << " is wrong" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> decide;
			if (decide == 0)
			{
				return;
			}
		}
		else
			for (string a : year)
			{
				if (a == input)
				{
					cout << "Error!!!This year is already created!!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					cin >> decide;
					seen = true;
					if (decide == 0)
					{
						return;
					}
					else
					{
						break;
					}

				}
			}
		if (!seen)
		{
			break;
		}
	}
	string path = "./data/course/" + input;
	tt::makeDir(path + "/HK1");
	tt::makeDir(path + "/HK2");
	tt::makeDir(path + "/HK3");
	ofstream myFile("data/course/" + input + "/semester.dat");
	myFile.close();
	year.push_back(input);
	saveYear(filePath, year);
}