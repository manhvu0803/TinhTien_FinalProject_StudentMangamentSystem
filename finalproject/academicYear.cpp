#include "academicYear.h"
#define _CRT_SECURE_NO_WARNINGS
void academicYearMenu(int mode)
{
	int check = -1;
	string filePath = ("data/course/year.dat");
	int cont = 1;
	int choice = -1;
	tt::vector<string> year;
	scanYear(filePath, year);
	if (mode == 1)
	{
		while (cont != 0)
		{
			if (check != 0)
			{
				cout << setfill('=') << setw(50) << "=" << endl;
				cout << "*" << right << setfill('-') << setw(34) << "ACADEMIC YEAR MENU" << setfill('-') << setw(15) << "*" << endl;
				cout << setfill('=') << setw(50) << "=" << endl;
				check = 0;
			}
			cout << "\n";
			outputYear(year);
			if (year.size() == 0)
			{
				cout << "\nNothing to do here!\nPress Etner to return...";
				getchar();
				tt::clearConsole();
				cont = 0;
			}
			else
			{
				while (choice != 0)
				{
					cout << "\nEnter 0: To exit\n";
					cout << "Enter 1: Access semester in academic year\n";
					cout << "Enter your choice: ";
					cin >> choice;
					tt::clearConsole();
					if (choice >= 0 && choice <= 1)
					{
						break;
					}
					else
					{
						cout << "Error!!! Choose agian!" << endl;
						getchar();
						getchar();
						tt::clearConsole();
					}
					cout << setfill('=') << setw(50) << "=" << endl;
					cout << "*" << right << setfill('-') << setw(34) << "ACADEMIC YEAR MENU" << setfill('-') << setw(15) << "*" << endl;
					cout << setfill('=') << setw(50) << "=" << endl;
					cout << "\n";
					outputYear(year);
				}
				switch (choice)
				{
				default:
					cont = 0;
					break;
				case 1:
					changeToSemester(year, mode);
					check = 1;
					break;
				}
			}
		}
	}
	else
		while (cont != 0)
		{
			if (check != 0)
			{
				cout << setfill('=') << setw(50) << "=" << endl;
				cout << "*" << right << setfill('-') << setw(34) << "ACADEMIC YEAR MENU" << setfill('-') << setw(15) << "*" << endl;
				cout << setfill('=') << setw(50) << "=" << endl;
				check = 0;
			}
			while (choice != 0)
			{
				cout << "\n";
				outputYear(year);
				if (year.size() == 0)
				{
					cout << "\nEnter 0: To exit\n";
					cout << "Enter 1: Create new academic year\n";
					cout << "Enter your choice: ";
					cin >> choice;
					tt::clearConsole();
					if (choice >= 0 && choice <= 1)
					{
						break;
					}
					else
					{
						cout << "Error!!! Choose agian!" << endl;
						getchar();
						getchar();
						tt::clearConsole();
					}
				}
				else
				{
					cout << "\nEnter 0: To exit\n";
					cout << "Enter 1: Create new academic year\n";
					cout << "Enter 2: Delete 1 academic year\n";
					cout << "Enter 3: Access semester in academic year\n";
					cout << "Enter your choice: ";
					cin >> choice;
					tt::clearConsole();
					if (choice >= 0 && choice <= 3)
					{
						break;
					}
					else
					{
						cout << "Error!!! Choose agian!" << endl;
						getchar();
						getchar();
						tt::clearConsole();
					}
				}
				cout << setfill('=') << setw(50) << "=" << endl;
				cout << "*" << right << setfill('-') << setw(34) << "ACADEMIC YEAR MENU" << setfill('-') << setw(15) << "*" << endl;
				cout << setfill('=') << setw(50) << "=" << endl;

			}
			switch (choice)
			{
			default:
				cont = 0;
				break;
			case 1:
				createYear(filePath, year);
				check = 1;
				break;
			case 2:
				deleteYear(filePath, year);
				saveYear(filePath, year);
				break;
			case 3:
				changeToSemester(year, mode);
				check = 1;
				break;
			}
		}
	year.clear();
	tt::clearConsole();
}
void outputYear(tt::vector<string>& year)
{
	cout << "*" << right << setfill('-') << setw(30) << "Year List:" << setfill('-') << setw(20) << "*\n";
	if (year.size() == 0)
	{
		cout << "No data yet!\n";
	}
	int n = year.size();
	for (int i = 0; i < n; ++i)
	{
		cout << "(" << i + 1 << ")	" << year[i] << endl;
	}
	cout << "*" << setfill('-') << setw(50) << "*\n";
}
void scanYear(string filePath, tt::vector<string>& year)
{
	ifstream myFile(filePath);
	string temp;
	while (getline(myFile, temp))
	{
		temp[4] = '-';
		year.push_back(temp);
	}
	myFile.close();
	sortYear(year);
}
void changeToSemester(tt::vector<string>& year, int mode)
{
	cout << setfill('=') << setw(50) << "=" << endl;
	outputYear(year);
	cout << setfill('=') << setw(50) << "=" << endl;
	int decide;
	while (true)
	{
		cout << "Input the year No. :	"; cin >> decide;
		tt::clearConsole();
		if (decide >= 1 && decide <= year.size())
		{
			break;
		}
		else
		{
			cout << "Error!!!No available year!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> decide;
			tt::clearConsole();
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
		semesterMenu(atoi(newString), mode);
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
		getchar();
		tt::clearConsole();
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
	string temp;
	int input;
	int decide = -1;
	bool seen = false, wrong = false;
	char year1[5], year2[5];
	while (true)
	{
		seen = false;
		wrong = false;
		cout << "Input started year: "; cin >> input;
		if (input <= 2000 || input > 3000)
		{
			tt::clearConsole();
			cout << "Your input " << input << " is wrong" << endl;
			if (input <= 2000)cout << "It is too small" << endl;
			else cout << "It is too big" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			wrong = true;
			cin >> decide;
			tt::clearConsole();
			if (decide == 0)
			{
				return;
			}
		}
		else
		{
			_itoa_s(input, year1, 10);
			_itoa_s(input + 1, year2, 10);
			temp += year1;
			temp += '-';
			temp += year2;
			for (string a : year)
			{
				if (a == temp)
				{
					tt::clearConsole();
					cout << "Error!!!This year is already created!!!" << endl;
					cout << "Input (0) to break or (1) to continue: ";
					cin >> decide;
					seen = true;
					tt::clearConsole();
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
		}
		if (!seen && !wrong)
		{
			break;
		}
	}
	tt::clearConsole();
	string path = "./data/course/" + temp;
	tt::makeDir(path + "/HK1");
	tt::makeDir(path + "/HK2");
	tt::makeDir(path + "/HK3");
	ofstream myFile("data/course/" + temp + "/semester.dat");
	myFile.close();
	year.push_back(temp);
	saveYear(filePath, year);
	cout << "Academic year: " << temp << " has been created!!\n";
	cout << "Press Enter to continue... ";
	getchar();
	getchar();
	tt::clearConsole();
}
void deleteYear(string filePath, tt::vector<string>& year)
{
	int choice;
	cout << "(" << 0 << "): Exit\n";
	outputYear(year);
	while (true)
	{
		cout << "\nEnter year No. : "; cin >> choice;
		tt::clearConsole();
		if (choice >= 0 && choice <= year.size())
		{
			break;
		}
		else
		{
			cout << "Error!!!No available year!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			cin >> choice;
			tt::clearConsole();
			if (choice == 0)
			{
				break;
			}
		}
		cout << "(" << 0 << "): Exit\n";
		outputYear(year);
	}
	if (choice != 0)
	{
		cout << "Academic year: " << year[choice - 1] << " has been delete!";
		year.erase(choice - 1);
		getchar();
		getchar();
		tt::clearConsole();
	}
}