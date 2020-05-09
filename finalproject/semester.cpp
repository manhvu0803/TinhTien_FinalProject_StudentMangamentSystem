#include "semester.h"
#include <string>
#include <fstream>
#include <direct.h>
#include <iomanip>
void semesterMenu(int year)
{
	string filePath = ("data/course/");
	filePath.append(to_string(year));
	filePath.append("-");
	filePath.append(to_string(year + 1));
	cout << setfill('=') << setw(50) << "=" << endl;
	cout << "*" << setfill('-') << setw(27) << "SEMESTER MENU" << setfill('-') << setw(22) << "*" << endl;
	cout << setfill('=') << setw(50) << "=" << endl;
	int cont=1;
	int choice = -1;
	tt::vector<string> semester;
	scanSemester(filePath, semester);
	while (cont != 0)
	{
		cont = 1;
		while (choice != 0)
		{
			outputSemester(semester);
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
			changeToCourse(year, semester);
			break;
		}
		}
	semester.clear();
}
void changeToCourse(int year, tt::vector<string> semester)
{
	/*cout << "/n/n/";
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
	}*/
	cout << "HI" << endl;
}
void outputSemester( tt::vector<string> semester)
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
		cout <<"("<<i+1<<")	"<<semester[i] << endl;
	}
}

void scanSemester(string filePath, tt::vector<string>& semester)
{
	ifstream myFile(filePath + "/semester.dat");
	string temp;
	while (myFile>> temp)
	{
		semester.push_back(temp);
	}
	myFile.close();
}