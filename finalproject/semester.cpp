#include "semester.h"
#include <string>
#include <fstream>
#include <direct.h>
#include <iomanip>

void semesterMenu(int year, int mode)
{
	bool checkInput = true;
	int check = -1;
	string filePath = ("data/course/");
	filePath.append(to_string(year));
	filePath.append("-");
	filePath.append(to_string(year + 1));
	int cont = 1;
	int choice = -1;
	tt::vector<string> semester;
	scanSemester(filePath, semester);
	if (mode == 0)
	{
		while (cont != 0)
		{
			if (check != 0)
			{
				cout << setfill('=') << setw(50) << "=" << endl;
				cout << "*" << setfill('-') << setw(30) << "SEMESTER MENU" << setfill('-') << setw(19) << "*" << endl;
				cout << setfill('=') << setw(50) << "=" << endl;
				check = 0;
			}
			cout << "\n";
			outputSemester(semester);
			if (semester.size() == 0)
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
					cout << "\nEnter 0: Exit\n";
					cout << "Enter 1: Access course in academic year\n";
					cout << "Enter your choice: ";
					checkInput = tt::cinIg(cin, choice);
					tt::clearConsole();
					if (choice >= 0 && choice <= 1 && checkInput)
					{
						break;
					}
					else
					{
						cout << "Error!!! Choose agian!" << endl;
						getchar();
						choice = 2;
						tt::clearConsole();
					}
					cout << setfill('=') << setw(50) << "=" << endl;
					cout << "*" << setfill('-') << setw(30) << "SEMESTER MENU" << setfill('-') << setw(19) << "*" << endl;
					cout << setfill('=') << setw(50) << "=" << endl;
					cout << "\n";
					outputSemester(semester);
				}
				switch (choice)
				{
				default:
					cont = 0;
					break;
				case 1:
					changeToCourse(year, semester, mode);
					check = 1;
					break;
				case 2:
					check = 1;
					break;
				}
			}
		}
	}
	else
		while (cont != 0)
		{
			cont = 1;
			if (check != 0)
			{
				cout << setfill('=') << setw(50) << "=" << endl;
				cout << "*" << setfill('-') << setw(30) << "SEMESTER MENU" << setfill('-') << setw(19) << "*" << endl;
				cout << setfill('=') << setw(50) << "=" << endl;
				check = 0;
			}
			while (choice != 0)
			{
				cout << "\n";
				outputSemester(semester);
				if (semester.size() == 0)
				{
					cout << "\nEnter 0: Exit\n";
					cout << "Enter 1: Create new semester\n";
					cout << "Enter your choice: "; checkInput = tt::cinIg(cin, choice);
					tt::clearConsole();
					if (choice >= 0 && choice <= 1 && checkInput)
					{
						break;
					}
					else
					{
						cout << "Error! Choose agian!" << endl;
						getchar();
						tt::clearConsole();
						choice = 4;
					}
				}
				else
				{
					cout << "\nEnter 0: Exit\n";
					cout << "Enter 1: Create new semester\n";
					cout << "Enter 2: Delete 1 semester\n";
					cout << "Enter 3: Access courses in semester\n";
					cout << "Enter your choice: "; checkInput = tt::cinIg(cin, choice);
					tt::clearConsole();
					if (choice >= 0 && choice <= 3 && checkInput)
					{
						break;
					}
					else
					{
						cout << "Error! Choose agian!" << endl;
						getchar();
						tt::clearConsole();
						choice = 4;
					}
				}
				cout << setfill('=') << setw(50) << "=" << endl;
				cout << "*" << setfill('-') << setw(30) << "SEMESTER MENU" << setfill('-') << setw(19) << "*" << endl;
				cout << setfill('=') << setw(50) << "=" << endl;
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
				deleteSemester(filePath, semester);
				check = 1;
				break;
			case 3:
				changeToCourse(year, semester, mode);
				check = -1;
				break;
			case 4:
				check = 1;
				break;
			}
		}
	semester.clear();
	tt::clearConsole();
}
void changeToCourse(int year, tt::vector<string>& semester, int mode)
{
	bool checkInput = true;
	cout << setfill('=') << setw(50) << "=" << endl;
	outputSemester(semester);
	cout << setfill('=') << setw(50) << "=" << endl;
	int decide;
	while (true)
	{
		cout << "Input the semester No. :"; checkInput = tt::cinIg(cin, decide);
		tt::clearConsole();
		if (decide >= 1 && decide <= semester.size() && checkInput)
		{
			break;
		}
		else
		{
			cout << "Error!!!No available semester!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			checkInput = tt::cinIg(cin, decide);
			if (!checkInput)decide = 0;
			tt::clearConsole();
			if (decide == 0)
			{
				break;
			}
		}
	}
	if (decide != 0)
	{
		courseMenu(year, semester[decide - 1], mode);
	}

}
void outputSemester(tt::vector<string>& semester)
{
	int size = semester.size();
	cout << "*" << right << setfill('-') << setw(30) << "Semesters:" << setfill('-') << setw(20) << "*\n";
	if (size == 0)
	{
		cout << "No data yet!\n";
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		cout << "(" << i + 1 << ")	" << semester[i] << endl;
	}
	cout << "*" << setfill('-') << setw(50) << "*\n";
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
	bool checkInput = true;
	int size = semester.size();
	int choice = -1;
	string path = "./";
	path += filePath + '/';
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
			cout << "Enter your choice: "; checkInput = tt::cinIg(cin, choice);
			tt::clearConsole();
			if (choice < 0 || choice>5)
			{
				cout << "Error!!!Your choice is not available!!!\n";
				cout << "Please input again!!!";
				tt::clearConsole();
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
				cout << "HK1 has been created\n";
				ofstream myFile(filePath + "/HK1" + "/course.dat");
				tt::makeDir(path + "HK1");
				myFile.close();
			}
			if (choice == 2)
			{
				semester.push_back("HK2");
				cout << "HK2 has been created\n";
				tt::makeDir(path + "HK2");
				ofstream myFile(filePath + "/HK2" + "/course.dat");
				myFile.close();
			}
			if (choice == 3)
			{
				semester.push_back("HK3");
				cout << "HK3 has been created\n";
				tt::makeDir(path + "HK3");
				ofstream myFile(filePath + "/HK3" + "/course.dat");
				myFile.close();
			}
			if (choice == 4)
			{
				semester.push_back("HK1");
				semester.push_back("HK2");
				semester.push_back("HK3");
				tt::makeDir(path + "HK1");
				tt::makeDir(path + "HK2");
				tt::makeDir(path + "HK3");
				ofstream myFile(filePath + "/HK1" + "/course.dat");
				myFile.close();
				myFile.open(filePath + "/HK2" + "/course.dat");
				myFile.close();
				myFile.open(filePath + "/HK3" + "/course.dat");
				myFile.close();
				cout << "3 semesters have been created\n";
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
				cout << "Enter your choice: "; checkInput = tt::cinIg(cin, choice);
				tt::clearConsole();
				if (!checkInput)choice = 0;
				if (choice < 0 || choice>4)
				{
					cout << "Error!!!Your choice is not available!!!\n";
					cout << "Please input again!!!";
					tt::clearConsole();
					choice = -1;
				}
			}
			if (semester[0][2] == '2')
			{
				cout << "Enter (1): HK1\n";
				cout << "Enter (2): HK3\n";
				cout << "Enter (3): All\n";
				cout << "Enter your choice: "; checkInput = tt::cinIg(cin, choice);
				tt::clearConsole();
				if (!checkInput)choice = 0;
				if (choice != 0)
				{
					choice += 3;
				}
				if (choice < 0 || choice>4)
				{
					cout << "Error!!!Your choice is not available!!!\n";
					cout << "Please input again!!!";
					tt::clearConsole();
					choice = -1;
				}
			}
			if (semester[0][2] == '3')
			{
				cout << "Enter (1): HK1\n";
				cout << "Enter (2): HK2\n";
				cout << "Enter (3): All\n";
				cout << "Enter your choice: "; checkInput = tt::cinIg(cin, choice);
				tt::clearConsole();
				if (!checkInput)choice = 0;
				if (choice != 0)
				{
					choice += 6;
				}
				if (choice < 0 || choice>4)
				{
					cout << "Error!!!Your choice is not available!!!\n";
					cout << "Please input again!!!";
					tt::clearConsole();
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
			cout << "HK2 has been created\n";
			tt::makeDir(path + "HK2");
			ofstream myFile(filePath + "/HK2" + "/course.dat");
			myFile.close();
		}
		if (choice == 2)
		{
			semester.push_back("HK3");
			cout << "HK3 has been created\n";
			tt::makeDir(path + "HK3");
			ofstream myFile(filePath + "/HK3" + "/course.dat");
			myFile.close();
		}
		if (choice == 3)
		{
			semester.push_back("HK2");
			semester.push_back("HK3");
			cout << "HK2 and HK3 have been created\n";
			tt::makeDir(path + "HK2");
			tt::makeDir(path + "HK3");
			ofstream myFile(filePath + "/HK2" + "/course.dat");
			myFile.close();
			myFile.open(filePath + "/HK3" + "/course.dat");
			myFile.close();
		}
		if (choice == 4)
		{
			semester.push_back("HK1");
			tt::makeDir(path + "HK1");
			cout << "HK1 has been created\n";
			ofstream myFile(filePath + "/HK1" + "/course.dat");
			myFile.close();
		}
		if (choice == 5)
		{
			semester.push_back("HK3");
			tt::makeDir(path + "HK3");
			cout << "HK3 has been created\n";
			ofstream myFile(filePath + "/HK3" + "/course.dat");
			myFile.close();
		}
		if (choice == 6)
		{
			semester.push_back("HK1");
			semester.push_back("HK3");
			tt::makeDir(path + "HK1");
			tt::makeDir(path + "HK3");
			cout << "HK1 and HK3 have been created\n";
			ofstream myFile(filePath + "/HK1" + "/course.dat");
			myFile.close();
			myFile.open(filePath + "/HK1" + "/course.dat");
			myFile.close();
		}
		if (choice == 7)
		{
			semester.push_back("HK1");
			tt::makeDir(path + "HK1");
			cout << "HK1 has been created\n";
			ofstream myFile(filePath + "/HK1" + "/course.dat");
			myFile.close();
		}
		if (choice == 8)
		{
			semester.push_back("HK2");
			tt::makeDir(path + "HK2");
			cout << "HK2 has been created\n";
			ofstream myFile(filePath + "/HK2" + "/course.dat");
			myFile.close();
		}
		if (choice == 9)
		{
			semester.push_back("HK1");
			semester.push_back("HK2");
			tt::makeDir(path + "HK1");
			tt::makeDir(path + "HK2");
			cout << "HK1 and HK2 has been created\n";
			ofstream myFile(filePath + "/HK1" + "/course.dat");
			myFile.close();
			myFile.open(filePath + "/HK2" + "/course.dat");
			myFile.close();
		}
		break;
	case 2:
		if (semester[0][2] == '1' && semester[1][2] == '2')
		{
			cout << "HK3 has been created\n";
			tt::makeDir(path + "HK3");
			ofstream myFile(filePath + "/HK3" + "/course.dat");
			myFile.close();
			semester.push_back("HK3");
		}
		if (semester[0][2] == '1' && semester[1][2] == '3')
		{
			cout << "HK2 has been created\n";
			tt::makeDir(path + "HK2");
			semester.push_back("HK2");
			ofstream myFile(filePath + "/HK2" + "/course.dat");
			myFile.close();
		}
		if (semester[0][2] == '2' && semester[1][2] == '3')
		{
			cout << "HK1 has been created\n";
			tt::makeDir(path + "HK1");
			ofstream myFile(filePath + "/HK1" + "/course.dat");
			myFile.close();
			semester.push_back("HK1");
		}
		break;
	case 3:
		cout << "This year is full\n";
		break;
	}
	if (choice != 0)
	{
		getchar();
	}
	tt::clearConsole();
	saveSemester(filePath, semester);
}
void deleteSemester(string filePath, tt::vector<string>& semester)
{
	int choice;
	bool checkInput = true;
	cout << "(" << 0 << "): Exit\n";
	outputSemester(semester);
	while (true)
	{
		cout << "\nEnter semester No. : "; checkInput = tt::cinIg(cin, choice);
		tt::clearConsole();
		if (choice >= 0 && choice <= semester.size() && checkInput)
		{
			break;
		}
		else
		{
			cout << "Error!!!No available semester!!!" << endl;
			cout << "Input (0) to break or (1) to continue: ";
			checkInput = tt::cinIg(cin, choice);
			if (!checkInput)choice = 0;
			tt::clearConsole();
			if (choice == 0)
			{
				break;
			}
		}
		cout << "(" << 0 << "): Exit\n";
		outputSemester(semester);
	}
	if (choice != 0)
	{
		cout << "Semester: " << semester[choice - 1] << " has been delete!";
		semester.erase(choice - 1);
		getchar();
		tt::clearConsole();
	}
}