#include "semester.h"
#include <string>
#include <fstream>
#include <direct.h>
#include <iomanip>
void semesterMenu(int year)
{
	int check = -1;
	string filePath = ("data/course/");
	filePath.append(to_string(year));
	filePath.append("-");
	filePath.append(to_string(year + 1));

	int cont = 1;
	int choice = -1;
	tt::vector<string> semester;
	scanSemester(filePath, semester);
	while (cont != 0)
	{
		cont = 1;
		if (check != 0)
		{
			cout << setfill('=') << setw(50) << "=" << endl;
			cout << "*" << setfill('-') << setw(27) << "SEMESTER MENU" << setfill('-') << setw(22) << "*" << endl;
			cout << setfill('=') << setw(50) << "=" << endl;
			check = 0;
		}
		while (choice != 0)
		{
			outputSemester(semester);
			cout << "\nEnter 0: To exit\n";
			cout << "Enter 1: To create new semester\n";
			cout << "Enter 2: To change course in semester\n";
			cout << "Enter your choice: "; cin >> choice;
			if (choice >= 0 && choice <= 2)
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
			createSemester(filePath, semester);
			check = -1;
			break;
		case 2:
			changeToCourse(year, semester);

			check = -1;
			break;
		}
	}
	semester.clear();
}
void changeToCourse(int year, tt::vector<string>& semester)
{
	cout << "\n\n\n";
	outputSemester(semester);
	int decide;
	while (true)
	{
		cout << "Input the semester no. :"; cin >> decide;
		if (decide >= 1 && decide <= semester.size())
		{
			break;
		}
		else
		{
			cout << "Error!!!No available semester!!!" << endl;
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
		courseMenu(year, semester[decide - 1]);
	}
	cout << "\n\n\n\n\n";
}
void outputSemester(tt::vector<string>& semester)
{
	int size = semester.size();
	cout << "Your semester: " << endl;
	if (size == 0)
	{
		cout << "No data yet!\n";
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		cout << "(" << i + 1 << ")	" << semester[i] << endl;
	}
}

void scanSemester(string filePath, tt::vector<string>& semester)
{
	ifstream myFile(filePath + "/semester.dat");
	string temp;
	while (myFile >> temp)
	{
		semester.push_back(temp);
	}
	myFile.close();
}
void saveSemester(string filePath, tt::vector<string>& semester)
{
	ofstream myFile(filePath + "/semester.dat");
	string temp;
	for (string a : semester)
	{
		myFile << a << endl;
	}
	myFile.close();
}
void createSemester(string filePath, tt::vector<string>& semester)
{
	int size = semester.size();
	cout << "\n\n\n\n";
	int choice = -1;
	switch (size)
	{
	case 0:
		while (true)
		{
			cout << "Enter (0): Break\n";
			cout << "Enter (1): HK1\n";
			cout << "Enter (2): HK2\n";
			cout << "Enter (3): HK3\n";
			cout << "Enter (4): All\n";
			cout << "Enter your choice: "; cin >> choice;
			if (choice < 0 || choice>5)
			{
				cout << "Error!!!Your choice is not available!!!\n";
				cout << "Please input again!!!\n\n\n\n";
			}
			else
			{
				break;
			}
		}
		if (choice != 0)
		{
			if (choice == 1)
			{
				semester.push_back("HK1");
			}
			if (choice == 2)
			{
				semester.push_back("HK2");
			}
			if (choice == 3)
			{
				semester.push_back("HK3");
			}
			if (choice == 4)
			{
				semester.push_back("HK1");
				semester.push_back("HK2");
				semester.push_back("HK3");
			}
		}
		break;
	case 1:
		while (true)
		{
			cout << "Enter (0): Break\n";
			if (semester[0][2] == '1')
			{
				cout << "Enter (1): HK2\n";
				cout << "Enter (2): HK3\n";
				cout << "Enter (3): All\n";
				cout << "Enter your choice: "; cin >> choice;
				if (choice < 0 || choice>4)
				{
					cout << "Error!!!Your choice is not available!!!\n";
					cout << "Please input again!!!\n\n\n\n";
					choice = -1;
				}
			}
			if (semester[0][2] == '2')
			{
				cout << "Enter (1): HK1\n";
				cout << "Enter (2): HK3\n";
				cout << "Enter (3): All\n";
				cout << "Enter your choice: "; cin >> choice;
				if (choice != 0)
				{
					choice += 3;
				}
				if (choice < 0 || choice>4)
				{
					cout << "Error!!!Your choice is not available!!!\n";
					cout << "Please input again!!!\n\n\n\n";
					choice = -1;
				}
			}
			if (semester[0][2] == '3')
			{
				cout << "Enter (1): HK1\n";
				cout << "Enter (2): HK2\n";
				cout << "Enter (3): All\n";
				cout << "Enter your choice: "; cin >> choice;
				if (choice != 0)
				{
					choice += 6;
				}
				if (choice < 0 || choice>4)
				{
					cout << "Error!!!Your choice is not available!!!\n";
					cout << "Please input again!!!\n\n\n\n";
					choice = -1;
				}
			}
			if (choice != -1)
			{
				break;
			}
		}
		if (choice == 1)
		{
			semester.push_back("HK2");
		}
		if (choice == 2)
		{
			semester.push_back("HK3");
		}
		if (choice == 3)
		{
			semester.push_back("HK2");
			semester.push_back("HK3");
		}
		if (choice == 4)
		{
			semester.push_back("HK1");
		}
		if (choice == 5)
		{
			semester.push_back("HK3");
		}
		if (choice == 6)
		{
			semester.push_back("HK1");
			semester.push_back("HK3");
		}
		if (choice == 7)
		{
			semester.push_back("HK1");
		}
		if (choice == 8)
		{
			semester.push_back("HK2");
		}
		if (choice == 9)
		{
			semester.push_back("HK1");
			semester.push_back("HK2");
		}
		break;
	case 2:
		if (semester[0][2] == '1' && semester[1][2] == '2')
		{
			cout << "HK3 has been created\n";
			semester.push_back("HK3");
		}
		if (semester[0][2] == '1' && semester[1][2] == '3')
		{
			cout << "HK2 has been created\n";
			semester.push_back("HK2");
		}
		if (semester[0][2] == '2' && semester[1][2] == '3')
		{
			cout << "HK1 has been created\n";
			semester.push_back("HK1");
		}
		break;
	case 3:
		cout << "This year is full\n";
		break;
	}
	cout << "\n\n\n\n\n";
	saveSemester(filePath, semester);
}