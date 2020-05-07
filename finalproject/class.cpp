#include"class.h"

int MaxDayInMonth(int month, int year)
{
	int maxday = 31;
	if (month == 2)
	{
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			maxday = 29;
		}
		else
		{
			maxday = 28;
		}
	}
	else
	{
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			maxday = 30;
		}
	}
	return maxday;
}

void AddOneStudent(vector<student>& stL)
{
	string classname;
	student nst;
	int check = 0, count = 0, choice = -1;
	vector<student>stLtemp;
	int temp = 10 * 10 * 10 * 10 * 10 * 10 * 10;
	cout << "Please input the information of the new student" << endl;
	cout << "ID           : ";
	cin >> nst.id;
	while (cin.fail() || nst.id < temp)
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Please input the information of the new student (ID must be an integer with 8 digits)" << endl;
		cout << "ID          : ";
		cin >> nst.id;
	}
	FindStudentInAllClass(stLtemp, nst.id, check, nst, classname, count);
	while (check == 1)
	{
		cout << "Error: The ID " << nst.id << " has already been given to student name " << nst.lastName << " " << nst.firstName << " in class " << classname << "." << endl;
		cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
		cout << "Your choice: ";
		cin >> choice;
		while (cin.fail() || (choice != 1 && choice != 0))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Invalid choice." << endl;
			cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
			cout << "Your choice: ";
			cin >> choice;
		}
		if (choice == 1)
		{
			cout << "Please input the information of the new student" << endl;
			cout << "ID           : ";
			cin >> nst.id;
			while (cin.fail() || nst.id < temp)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Please input the information of the new student (ID must be an integer with 8 digits)" << endl;
				cout << "ID          : ";
				cin >> nst.id;
			}
			FindStudentInAllClass(stLtemp, nst.id, check, nst, classname, count);
		}
		else
		{
			return;
		}
	}
	cout << "So, please continue to input others information of this new student:" << endl;
	cout << "Lastname     : "; cin.ignore(1); getline(cin, nst.lastName);
	cout << "Firstname    : "; getline(cin, nst.firstName);
	cout << "Gender       : "; nst.gender = getchar();
	cout << "Date of birth: " << endl;
	cout << "Input year: ";
	cin >> nst.DoB.y;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Please input year: ";
		cin >> nst.DoB.y;
	}
	while (nst.DoB.y < 1900)
	{
		cout << "Invalid year." << endl;
		cout << "Enter the year again (Note: The year shouble be from 1900): ";
		cin >> nst.DoB.y;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Please input year: ";
			cin >> nst.DoB.y;
		}
	}
	cout << "Input month: ";
	cin >> nst.DoB.m;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Please input month: ";
		cin >> nst.DoB.m;
	}
	while (nst.DoB.m <= 0 || nst.DoB.m > 12)
	{
		cout << "Invalid month." << endl;
		cout << "Enter the month again (Note: The month shoul be from 1 to 12): ";
		cin >> nst.DoB.m;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Please input month: ";
			cin >> nst.DoB.m;
		}
	}
	cout << "Input day: ";
	cin >> nst.DoB.d;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Please input day: ";
		cin >> nst.DoB.d;
	}
	while (nst.DoB.d <= 0 || nst.DoB.d > MaxDayInMonth(nst.DoB.m, nst.DoB.y))
	{
		cout << "Invalid day." << endl;
		cout << "Enter the day again (Note: The day shoul be from 1 to " << MaxDayInMonth(nst.DoB.m, nst.DoB.y) << "): ";
		cin >> nst.DoB.d;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Please input day: ";
			cin >> nst.DoB.d;
		}
	}
	nst.number = stL.size() + 1;
	stL.push_back(nst);
}

void CreateNewClass(vector<student>& stL, int& n)
{
	for (int i = 0; i < n; i++)
	{
		AddOneStudent(stL);
	}
}

void LoadFromCSVFile(ifstream& fload, vector<student>& stL)
{
	string temp;
	string line;
	string temp2;
	student st;
	int count = 0;
	getline(fload, line);
	while (getline(fload, temp, ','))
	{
		st.number = stoi(temp);
		getline(fload, temp, ',');
		st.id = stoi(temp);
		getline(fload, temp, ',');
		st.lastName = temp;
		getline(fload, temp, ',');
		st.firstName = temp;
		getline(fload, temp, ',');
		st.gender = temp[0];
		getline(fload, temp, '/');
		st.DoB.d = stoi(temp);
		getline(fload, temp, '/');
		st.DoB.m = stoi(temp);
		getline(fload, temp);
		st.DoB.y = stoi(temp);
		st.number = stL.size() + 1;
		stL.push_back(st);
	}
}

void ImportToProgram(vector<student>&stL, string flname)
{
	ifstream fload;
	fload.open(flname);
	if (!fload.is_open())
	{
		cout << "Can not find any data of this class." << endl;
	}
	else
	{
		LoadFromCSVFile(fload, stL);
		fload.close();
	}
}

void DisPlay1Student(student st)
{
	int distance = st.lastName.size() + 4;
	int distance2 = (15 - (st.lastName.size() - 8)) + st.firstName.size();
	int distance3 = 8 - st.firstName.size() + 11;
	cout << setw(5) << st.number << setw(12) << st.id << setw(distance) << st.lastName << setw(distance2) << st.firstName
		<< setw(distance3) << st.gender;
	if (st.DoB.d < 10)
	{
		cout << setw(14) << "0" << st.DoB.d;
	}
	else
	{
		cout << setw(15) << st.DoB.d;
	}
	cout << "/";
	if (st.DoB.m < 10)
	{
		cout << "0" << st.DoB.m; 
	}
	else
	{
		cout << st.DoB.m;
	}
	cout << "/" << st.DoB.y << endl;
}

void DisPlay1StudentLine(student st)
{
	cout << endl;
	cout << "No: " << st.number << endl;
	cout << "ID: " << st.id << endl;
	cout << "Lastname: " << st.lastName << endl;
	cout << "Firstname: " << st.firstName << endl;
	cout << "Gender:" << st.gender << endl;
	cout << "Date of birth: ";
	if (st.DoB.d < 10)
	{
		cout << "0" << st.DoB.d;
	}
	else
	{
		cout << st.DoB.d;
	}
	cout << "/";
	if (st.DoB.m < 10)
	{
		cout << "0" << st.DoB.m;
	}
	else
	{
		cout << st.DoB.m;
	}
	cout << "/" << st.DoB.y << endl;
}

void DisPlayClass(vector<student> stL)
{
	int n = stL.size();
	cout << setw(5) << "No" << setw(6) << "ID" << setw(18) << "Lastname" << setw(24) << "Firstname" << setw(15) << "Gender"
		<< setw(21) << "Date of birth" << endl;
	for (int i = 0; i < n; i++)
	{
		DisPlay1Student(stL[i]);
	}
	cout << endl;
}

void DisPlayClassLine(vector<student> stL)
{
	int n = stL.size();
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		DisPlay1StudentLine(stL[i]);
	}
	cout << endl;
}

void DisPlayAllClass(vector<student>stL)
{
	ifstream fload;
	string classname, fclassname;
	string filepath = "data/classes/";
	//fload.open("allclassname.txt");
	fload.open("data/classes/allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (fload >> classname)
		{
			//fclassname = classname + "/" + classname + ".dat";
			fclassname = filepath + classname + ".dat";
			cout << "Class " << classname << ":" << endl;
			ImportToProgram2(stL, fclassname);
			DisPlayClass(stL);
			stL.clear();
		}
		fload.close();
	}
}

void DisPlayAllClassLine(vector<student>stL)
{
	ifstream fload;
	string classname, fclassname;
	string filepath = "data/classes/";
	//fload.open("allclassname.txt");
	fload.open("data/classes/allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (fload >> classname)
		{
			//fclassname = classname + "/" + classname + ".dat";
			fclassname = filepath + classname + ".dat";
			cout << "Class " << classname << ":" << endl;
			ImportToProgram2(stL, fclassname);
			DisPlayClassLine(stL);
			stL.clear();
		}
		fload.close();
	}
}

void Edit1Student(student &st)
{
	int choice = -1;
	int temp = 10 * 10 * 10 * 10 * 10 * 10 * 10;
	cout << "What do you want to edit from this student?" << endl;
	while (choice != 0)
	{
		cout << "(0).Exit" << endl;
		cout << "(1).ID." << endl;
		cout << "(2).Lastname and Firstname" << endl;
		cout << "(3).Gender." << endl;
		cout << "(4).Date of birth." << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		while (cin.fail() || choice < 0 || choice > 4)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Invalid choice." << endl;
			cout << "Enter your choice again: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			int idtemp, check = 0, count = 0;
			string classname;
			idtemp = st.id;
			vector<student>stLtemp;
			cout << "Input new ID: ";
			cin >> st.id;
			while (cin.fail() || st.id < temp)
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Please input new ID (ID must be an integer with 8 digits): ";
				cin >> st.id;
			}
			FindStudentInAllClass(stLtemp, st.id, check, st, classname, count);
			while (check == 1)
			{
				int choice1;
				cout << "Error: The ID " << st.id << " has already been given to another student in class " << classname << "." << endl;
				cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
				cout << "Your choice: ";
				cin >> choice1;
				while (cin.fail() || (choice1 != 1 && choice1 != 0))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
					cout << "Your choice: ";
					cin >> choice1;
				}
				if (choice1 == 1)
				{
					cout << "Please input the information of the new student" << endl;
					cout << "ID           : ";
					cin >> st.id;
					while (cin.fail() || st.id < temp)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please input new ID (ID must be an integer with 8 digits): ";
						cin >> st.id;
					}
					FindStudentInAllClass(stLtemp, st.id, check, st, classname, count);
				}
				else
				{
					break;
				}
			}
			break;
		}
		case 2:
		{
			cin.ignore(1);
			cout << "Input new name (Lastname and Firstname): " << endl;
			cout << "Lastname: ";
			getline(cin, st.lastName);
			cout << "Firstname: ";
			getline(cin, st.firstName);
			break;
		}
		case 3:
		{
			cin.ignore(1);
			cout << "Input new gender: ";
			st.gender = getchar();
			break;
		}
		case 4:
		{
			cout << "Input new Date of birth: " << endl;
			cout << "Input year: ";
			cin >> st.DoB.y;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Please input year: ";
				cin >> st.DoB.y;
			}
			while (st.DoB.y < 1900)
			{
				cout << "Invalid year." << endl;
				cout << "Enter the year again (Note: The year shouble be from 1900): ";
				cin >> st.DoB.y;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Please input year: ";
					cin >> st.DoB.y;
				}
			}
			cout << "Input month: ";
			cin >> st.DoB.m;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Please input month: ";
				cin >> st.DoB.m;
			}
			while (st.DoB.m <= 0 || st.DoB.m > 12)
			{
				cout << "Invalid month." << endl;
				cout << "Enter the month again (Note: The month shoul be from 1 to 12): ";
				cin >> st.DoB.m;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Please input month: ";
					cin >> st.DoB.m;
				}
			}
			cout << "Input day: ";
			cin >> st.DoB.d;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Please input day: ";
				cin >> st.DoB.d;
			}
			while (st.DoB.d <= 0 || st.DoB.d > MaxDayInMonth(st.DoB.m, st.DoB.y))
			{
				cout << "Invalid day." << endl;
				cout << "Enter the day again (Note: The day shoul be from 1 to " << MaxDayInMonth(st.DoB.m, st.DoB.y) << "): ";
				cin >> st.DoB.d;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Please input day: ";
					cin >> st.DoB.d;
				}
			}
			break;
		}
		}
		cout << endl << "Is there anythings else about this student that to want to edit?" << endl;
	}
	cout << endl << "The student information after edited:" << endl;
	DisPlay1StudentLine(st);
}

void UpateIn1Class(vector<student>& stL, int number, student st)
{
	int n = stL.size();
	int choice;
	for (int i = 0; i < n; i++)
	{
		if (stL[i].number == number)
		{
			cout << endl << "Are you sure you want to place an update on the student:" << endl;
			cout << "Enter 1 to continue or 0 to exit: ";
			cin >> choice;
			while (cin.fail() || (choice != 1 && choice != 0))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Invalid choice." << endl;
				cout << "Please enter 1 to continue or 0 to exit.";
				cin >> choice;
			}
			if (choice != 0)
			{
				stL[i] = st;
			}
		}
	}
	SortClassInAscendingOrderByID(stL);
	cout << "The class after updated data:" << endl;
	DisPlayClass(stL);
}

void UpateInAllClass(vector<student>& stL, int id, student st)
{
	ifstream fload;
	int choices, choice;
	string classname;
	string filepath = "data/classes/";
	//fload.open("allclassname.txt");
	fload.open("data/classes/allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Would you like to save all update to all the classes's files?" << endl;
		cout << "Enter 1 to save (for all classes that have the student has given ID) or 0 to update but the updation won't be save: ";
		cin >> choices;
		while (cin.fail() || (choices != 1 && choices != 0))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Invalid choice." << endl;
			cout << "Please enter 1 to save or 0 to not save anything: ";
			cin >> choices;
		}
		while (fload >> classname)
		{
			stL.clear();
			//string flname = classname + "/" + classname + ".dat";
			string flname = filepath + classname + ".dat";
			ImportToProgram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (stL[i].id == id)
				{
					cout << "Are you sure you want to place the update on this student?" << endl;
					cout << "Enter 1 to replace or 0 to exit: ";
					cin >> choice;
					while (cin.fail() || (choice != 1 && choice != 0))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid choice." << endl;
						cout << "Enter 1 to replace or 0 to exit: ";
						cin >> choice;
					}
					if (choice != 0)
					{
						cout << endl << "Class " << classname << ":" << endl;
						stL[i] = st;
						SortClassInAscendingOrderByID(stL);
					}
					cout << "The class " << classname << " after updated data:" << endl;
					DisPlayClass(stL);
					if (choices == 1)
					{
						string fsname = flname;
						ExportFromProgram2(stL, fsname);
					}
				}
			}
		}
		fload.close();
	}
}

void RemoveStudentFrom1Class(vector<student>& stL, int id, string classname)
{
	int n = stL.size();
	int choice;
	for (int i = 0; i < n; i++)
	{
		if (id == stL[i].id)
		{
			cout << endl << "Are you sure you want to delete this student?" << endl;
			DisPlay1StudentLine(stL[i]);
			cout << "Enter 1 to continue or 0 to exit: ";
			cin >> choice;
			while (cin.fail() || (choice != 0 && choice != 1))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Invalid choice." << endl;
				cout << "Please enter 1 to continue or 0 to exit: ";
				cin >> choice;
			}
			if (choice != 0)
			{
				for (int j = i + 1; j < n; j++)
				{
					stL[j].number = stL[j].number - 1;
				}
				stL.erase(stL.begin() + i);
				stL.shrink_to_fit();
				n = stL.size();
				i--;
			}
		}
	}
}

void RemoveStudentFromAllClass(vector<student>stL, int id)
{
	ifstream fload;
	string classname;
	int choices, choice = 1;
	string filepath = "data/classes/";
	//fload.open("allclassname.txt");
	fload.open("data/classes/allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Would you like to save all update to all the classes's files?" << endl;
		cout << "Enter 1 to save (for all classes that have the student has given ID) or 0 to update but the updation won't be save: ";
		cin >> choices;
		while (cin.fail() || (choices != 1 && choices != 0))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Invalid choice." << endl;
			cout << "Please enter 1 to save or 0 to exit: ";
			cin >> choices;
		}
		while (fload >> classname)
		{
			stL.clear();
			//string flname = classname + "/" + classname + ".dat";
			string flname = filepath + classname + ".dat";
			ImportToProgram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (stL[i].id == id)
				{
					cout << "Class " << classname << ":" << endl;
					RemoveStudentFrom1Class(stL, id, classname);
					n = stL.size();
					cout << "The class " << classname << " after deleted the student has ID " << id << ":" << endl;
					DisPlayClass(stL);
					if (choices == 1)
					{
						string fsname = flname;
						ExportFromProgram2(stL, fsname);
					}
				}
			}
		}
		fload.close();
	}
}

void ChangeStudentFromClassAToClassB(vector<student>& stLA, vector<student>& stLB, int number, int& check, int id)
{
	int nA = stLA.size();
	int nB = stLB.size();
	check = 0;
	for (int i = 0; i < nA; i++)
	{
		if (stLA[i].number == number)
		{
			for (int j = 0; j < nB; j++)
			{
				if (stLB[j].id == id)
				{
					check = 1;
				}
			}
			if (check != 1)
			{
				stLA[i].number = stLB.size() + 1;
				stLB.push_back(stLA[i]);
				nB = stLB.size();
				for (int j = i + 1; j < nA; j++)
				{
					stLA[j].number = stLA[j].number - 1;
				}
				stLA.erase(stLA.begin() + i);
				stLA.shrink_to_fit();
				nA = stLA.size();
				SortClassInAscendingOrderByID(stLA);
				SortClassInAscendingOrderByID(stLB);
			}
			break;
		}
	}
}

void FindStudentInAllClass(vector<student>& stL, int id, int& check, student& st, string& classname, int& count)
{
	ifstream fload;
	string flname;
	vector<string> clsL;
	check = 0;
	count = 0;
	int check2 = 0;
	string filepath = "data/classes/";
	//fload.open("allclassname.txt");
	fload.open("data/classes/allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		while (fload >> classname)
		{
			stL.clear();
			//flname = classname + "/" + classname + ".dat";
			flname = filepath + classname + ".dat";
			ImportToProgram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (id == stL[i].id)
				{
					check = 1;
					st = stL[i];
					cout << endl << "Here is his/her information:" << endl;
					DisPlay1StudentLine(st);
					if (clsL.size() > 0)
					{
						int n1 = clsL.size();
						for (int j = 0; j < n1; j++)
						{
							check2 = 0;
							if (classname == clsL[j])
							{
								check2 = 1;
								break;
							}
						}
					}
					if (check2 == 0)
					{
						count++;
						clsL.push_back(classname);
					}
					cout << endl;
				}
			}
		}
		fload.close();
		if (check == 0)
		{
			cout << "There is no student has the ID " << id << "in this cousrse" << endl;
		}
		else
		{
			string classnametemp = "0";
			cout << "And his/her class ("<<count<<" class(es)):" << endl;
			for (int i = 0; i < count; i++)
			{
				stL.clear();
				classnametemp = clsL[i];
				if (count == 1)
				{
					classname = classnametemp;
				}
				cout << classnametemp << ":" << endl;
				flname = filepath + classnametemp + ".dat";
				ImportToProgram2(stL, flname);
				DisPlayClass(stL);
			}
		}
	}
}

void ExportToCSVFile(ofstream& fsave, vector<student> stL)
{
	int size = stL.size();
	fsave << "No," << "ID," << "Lastname," << "Firstname," << "Gender," << "Date of birth" << endl;
	for (int i = 0; i < size; i++)
	{
		fsave << stL[i].number << "," << stL[i].id << "," << stL[i].lastName << "," << stL[i].firstName << "," << stL[i].gender << ","
			<< stL[i].DoB.d << "/" << stL[i].DoB.m << "/" << stL[i].DoB.y << endl;
	}
}

void ExportFromProgram(vector<student>stL, string fsname)
{
	ofstream fsave;
	int choice = -1;
	fsave.open(fsname);
	if (!fsave.is_open())
	{
		cout << "Can not create file." << endl;
	}
	else
	{
		cout << "Save successed." << endl;
		ExportToCSVFile(fsave, stL);
		fsave.close();
	}
}

void FindStudentIn1Class(vector<student> stL, int id, string classname, int& check, student& st, int& count)
{
	check = 0;
	count = 0;
	int n = stL.size();
	for (int i = 0; i < n; i++)
	{
		if (stL[i].id == id)
		{
			check = 1;
			st = stL[i];
			cout << "The student has the ID " << id << " is:" << endl;
			DisPlay1StudentLine(st);
			cout << endl;
			count++;
		}
	}
	if (check == 0)
	{
		cout << "There is no student has the ID " << id << " in class " << classname << "." << endl;
	}
}

void LoadFromDATFile(ifstream& fload, vector<student>& stL)
{
	student st;
	string temp, line;
	while(fload>>st.number)
	{
		fload >> st.id;
		getline(fload, st.lastName);
		getline(fload, st.lastName);
		getline(fload, st.firstName);
		getline(fload, temp);
		st.gender = temp[0];
		getline(fload, temp, ' ');
		st.DoB.y = stoi(temp);
		getline(fload, temp, ' ');
		st.DoB.m = stoi(temp);
		getline(fload, temp);
		st.DoB.d = stoi(temp);
		stL.push_back(st);
	}
}

void ImportToProgram2(vector<student>& stL, string flname)
{
	ifstream fload;
	fload.open(flname);
	if (!fload.is_open())
	{
		cout << "Can not find any data of this class." << endl;
	}
	else
	{
		LoadFromDATFile(fload, stL);
		fload.close();
	}
}

void SaveToDATFile(ofstream& fsave, vector<student> stL)
{
	int n = stL.size();
	for (int i = 0; i < n; i++)
	{
		fsave << stL[i].number << endl;
		fsave << stL[i].id << endl;
		fsave << stL[i].lastName << endl;
		fsave << stL[i].firstName << endl;
		fsave << stL[i].gender << endl;
		fsave << stL[i].DoB.y << " " << stL[i].DoB.m << " " << stL[i].DoB.d;
		if (i < n - 1)
		{
			fsave << endl;
		}
	}
}

void ExportFromProgram2(vector<student> stL, string fsname)
{
	ofstream fsave;
	fsave.open(fsname);
	if (!fsave.is_open())
	{
		cout << "Can not create file." << endl;
	}
	else
	{
		cout << "Save successed." << endl;
		SaveToDATFile(fsave, stL);
		fsave.close();
	}
}

void SortClassInAscendingOrderByID(vector<student>& stL)
{
	int Notemp;
	student sttemp;
	int n = stL.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (stL[i].id > stL[j].id)
			{
				Notemp = stL[i].number;
				stL[i].number = stL[j].number;
				stL[j].number = Notemp;
				sttemp = stL[i];
				stL[i] = stL[j];
				stL[j] = sttemp;
			}
		}
	}
}

int CheckClassnameSavedorNot(string classname)
{
	ifstream fload;
	string classnametemp;
	int check = 0;
	fload.open("data/classes/allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		while (fload >> classnametemp)
		{
			if (classnametemp == classname)
			{
				check = 1;
				break;
			}
		}
		fload.close();
	}
	return check;
}

void AddClassname(string classname)
{
	ofstream fsave;
	fsave.open("data/classes/allclassname.txt", ios::app);
	if (!fsave.is_open())
	{
		cout << "Can not save." << endl;
	}
	else
	{
		fsave << endl;
		fsave << classname;
		fsave.close();
	}
}


void ManageClassFunction()
{
	vector<student> stL;
	int choice = -1;
	int temp = 10 * 10 * 10 * 10 * 10 * 10 * 10;
	string filepath = "data/classes/";
	cout << "What do you want to do: "; cout << endl;
	while (choice != 0)
	{
		cout << endl;
		cout << "Enter 0 to exit the program.                                         " << endl;
		cout << "Enter 1 to import your data to program. (tran csv file to dat file)  " << endl;
		cout << "Enter 2 to add new student.                                          " << endl;
		cout << "Enter 3 to edit an existing student.                                 " << endl;
		cout << "Enter 4 to remove a student.                                         " << endl;
		cout << "Enter 5 to change student from class A to class B.                   " << endl;
		cout << "Enter 6 to view list of classes.                                     " << endl;
		cout << "Enter 7 to view list of students in a class.                         " << endl << endl;
		cout << "Your choice: ";
		cin >> choice;
		while (cin.fail() || (choice < 0 || choice > 7))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << endl << "Invalid choice." << endl;
			cout << "Please enter your choice again: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 0:
		{
			cout << endl << "=================================Thanks for using our program. Have a nice day!=========================================";
			break;
		}
		case 1:
		{
			stL.clear();
			ifstream fload;
			string flclassname1, classname1;
			int choice1 = 1;
			cout << endl << "Input name of the class you want to import its data: ";
			cin.ignore(1);
			getline(cin, classname1);
			flclassname1 = filepath + classname1 + ".csv";
			ImportToProgram(stL, flclassname1);
			while (stL.size() == 0)
			{
				cout << endl << "There nothing to import here." << endl;
				cout << "Enter 1 if you want to input name of the class you want to import its data." << endl;
				cout << "Enter 0 to exit." << endl;
				cout << "Your choice: ";
				cin >> choice1;
				while (cin.fail() || (choice1 != 1 && choice1 != 0))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << endl << "Invalid choice." << endl;
					cout << "Please enter 1 if you want to input name of the class you want to import its data." << endl;
					cout << "Or please enter 0 to exit." << endl;
					cout << "Your choice: ";
					cin >> choice1;
				}
				if (choice1 == 1)
				{
					cout << endl << "Input name of the class you want to import its data: ";
					cin.ignore(1);
					getline(cin, classname1);
					flclassname1 = filepath + classname1 + ".csv";
					ImportToProgram(stL, flclassname1);
				}
				else
				{
					break;
				}
			}
			if (choice1 != 0)
			{
				DisPlayClass(stL);
				SortClassInAscendingOrderByID(stL);
				string fsclassname1 = filepath + classname1 + ".dat";
				ExportFromProgram2(stL, fsclassname1);
				if (CheckClassnameSavedorNot(classname1) == 0);
				{
					AddClassname(classname1);
				}
			}
			break;
		}
		case 2:
		{
			stL.clear();
			int check2 = 0;
			int choice2 = 1, choice2s;
			cout << endl << "Which class do you want to add new student?" << endl;
			cout << "Class: ";
			string classname2, flclassname2, fsclassname2;
			cin.ignore(1);
			getline(cin, classname2);
			flclassname2 = filepath + classname2 + ".dat";
			ImportToProgram2(stL, flclassname2);
			while (stL.size() == 0)
			{
				cout << "Do you want to input the name of the class that you want to add new student again or create new class?" << endl;
				cout << "Enter 1 to input the name of the class again or 2 to create new class or 0 to exit: ";
				cin >> choice2;
				while (cin.fail() || (choice2 != 0 && choice2 != 1 && choice2 != 2))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << endl << "Invalid choice." << endl;
					cout << "Please enter 1 to continue to input the name of the class again or 2 to create new class or 0 to exit: ";
					cin >> choice2;
				}
				if (choice2 == 1)
				{
					cout << endl << "Which class do you want to add new student? " << endl;
					cout << "Class: ";
					cin.ignore(1);
					getline(cin, classname2);
					flclassname2 = filepath + classname2 + ".dat";
					ImportToProgram2(stL, flclassname2);
				}
				else
				{
					break;
				}
			}
			if (choice2 == 1)
			{
				DisPlayClass(stL);
				AddOneStudent(stL);
				SortClassInAscendingOrderByID(stL);
				cout << endl << "Addition is updated:" << endl;
				DisPlayClass(stL);
				cout << "Do you want to save what you have done to this class's file?" << endl;
				cout << "Enter 1 to save or 0 to exit: ";
				cin >> choice2s;
				while (cin.fail() || (choice2s != 1 && choice2s != 0))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << endl << "Invalid choice." << endl;
					cout << "Please enter 1 to save or 0 to exit: ";
					cin >> choice2s;
				}
				if (choice2s == 1)
				{
					fsclassname2 = filepath + classname2 + ".dat";
					ExportFromProgram2(stL, fsclassname2);
				}
			}
			if (choice2 == 2)
			{
				int n2 = -1;
				cout << endl << "Please input the number of the student in the class: ";
				cin >> n2;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << endl << "Please input the number of the student in the class: ";
					cin >> n2;
				}
				while (n2 <= 0)
				{
					cout << endl << "Error: The number of the student in the class must bigger than 0." << endl;
					cout << "Please enter 1 to input the number of the student in the class again or you can enter 0 to exit: ";
					cin >> choice2;
					while (cin.fail() || (choice2 != 1 && choice2 != 0))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << endl << "Invalid choice." << endl;
						cout << "Please enter 1 to input the number of the student in the class again or you can enter 0 to exit: ";
						cin >> choice2;
					}
					if (choice2 == 1)
					{
						cout << endl << "Please input the number of the student in the class: ";
						cin >> n2;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Please input the number of the student in the class: ";
							cin >> n2;
						}
					}
				}
				if (n2 > 0)
				{
					CreateNewClass(stL, n2);
					DisPlayClass(stL);
					cout << endl << "Do you want to save this new class?" << endl;
					cout << "Enter 1 to save or 0 to exit: ";
					cin >> choice2s;
					while (cin.fail() || (choice2s != 1 && choice2s != 0))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << endl << "Invalid choice." << endl;
						cout << "Please enter 1 to save or 0 to exit: ";
						cin >> choice2;
					}
					if (choice2s == 1)
					{
						fsclassname2 = filepath + classname2 + ".dat";
						ExportFromProgram2(stL, fsclassname2);
						if (CheckClassnameSavedorNot(classname2) == 0)
						{
							AddClassname(classname2);
						}
					};
				}
			}
			break;
		}
		case 3:
		{
			stL.clear();
			int check3 = 0, id3, count3 = 1, count32 = 0, n3, number3, n32;
			int choice32, choice3 = -1, choice3s;
			string classname3;
			string flclassname3;
			student st3;
			string fsclassname3;
			cout << endl << "Do you know the class or the ID of the student you want to edit?" << endl;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			cin >> choice32;
			while (cin.fail() || (choice32 != 1 && choice32 != 2 && choice32 != 0))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << endl << "Invalid choice." << endl;
				cout << "Do you know the class or the ID of the student you want to edit?" << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				cin >> choice32;
			}
			if (choice32 == 1)
			{
				cout << endl << "Input the name of the class you want to edit student: ";
				cin.ignore(1);
				getline(cin, classname3);
				flclassname3 = filepath + classname3 + ".dat";
				ImportToProgram2(stL, flclassname3);
				while (stL.size() == 0)
				{
					cout << endl << "There is nothing to edit here." << endl;
					cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
					cin >> choice3;
					while (cin.fail() || (choice3 != 0 && choice3 != 1))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << endl << "Invalid choice." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						cin >> choice3;
					}
					if (choice3 == 1)
					{
						cout << endl << "Input the name of the class you want to edit student: ";
						cin.ignore(1);
						getline(cin, classname3);
						flclassname3 = filepath + classname3 + ".dat";
						ImportToProgram2(stL, flclassname3);
					}
					else
					{
						break;
					}
				}
				if (choice3 != 0)
				{
					DisPlayClass(stL);
					cout << "Input the ID of the student you want to edit in this class (an integer with 8 digits): ";
					cin >> id3;
					while (cin.fail() || id3 < temp)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please in put the ID of the student you want to edit in this class (ID must be an integer with 8 digits): ";
						cin >> id3;
					}
					FindStudentIn1Class(stL, id3, classname3, check3, st3, count32);
					while (check3 == 0)
					{
						cout << endl << "Do you want to input the ID of the student you want to edit in this class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin >> choice3;
						while (cin.fail() || (choice3 != 1 && choice3 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Please enter 1 to input ID again or 0 to exit: ";
							cin >> choice3;
						}
						if (choice3 == 1)
						{
							cout << endl << "Input the ID of the student you want to edit in this class (ID must be an integer with 8 digits): ";
							cin >> id3;
							while (cin.fail() || id3 < temp)
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Please input the ID of the student you want to edit in this class (ID must be an integer with 8 digits): ";
								cin >> id3;
							}
							FindStudentIn1Class(stL, id3, classname3, check3, st3, count32);
						}
						else
						{
							break;
						}
					}
				}
			}
			else
			{
				if (choice32 == 2)
				{
					cout << endl << "Please input the ID of the student you need to edit so we can find he/she for you and also his/her class too: ";
					cin >> id3;
					while (cin.fail() || id3 < temp)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "(ID must be an integer with 8 digits)." << endl;
						cout << endl << "Please input the ID of the student that you need to edit so we can find he/she for you and also his/her class too: ";
						cin >> id3;
					}
					FindStudentInAllClass(stL, id3, check3, st3, classname3, count3);
					while (check3 == 0)
					{
						cout << endl << "Enter 1 to input the ID of the student you to edit again or enter 0 to exit: ";
						cin >> choice3;
						while (cin.fail() || (choice3 != 1 && choice3 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Please enter 1 to input the ID of the student you wan to edit again or enter 0 to exit: ";
							cin >> choice3;
						}
						if (choice3 != 0)
						{
							cout << endl << "Input the ID of the student you want to edit (ID must an integer with 8 digits): ";
							cin >> id3;
							while (cin.fail() || id3 < temp)
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Please input the ID of the student you want to edit (ID must be an integer with 8 digits): ";
								cin >> id3;
							}
							FindStudentInAllClass(stL, id3, check3, st3, classname3, count3);
						}
						else
						{
							break;
						}
					}
					if (count3 == 1)
					{
						FindStudentIn1Class(stL, id3, classname3, check3, st3, count32);
					}
				}
				else
				{
					cout << endl << "You can use the function 7 to see all students in all classes and then choose function 4 again to edit the student you want to." << endl;
				}
			}
			if (check3 != 0)
			{
				cin.ignore(1);
				if (count3 > 1)
				{
					cout << "Because there are more than one class that constant to student has ID" << id3 << "." << endl;
					cout << "So we need you to chose the class of the student who you want to edit." << endl;
					cout << "Please input the name of the class: ";
					getline(cin, classname3);
					stL.clear();
					flclassname3 = filepath + classname3 + ".dat";
					ImportToProgram2(stL, flclassname3);
					FindStudentIn1Class(stL, id3, classname3, check3, st3, count32);
					while (check3 == 0)
					{
						cout << endl << "There is no student has the ID " << id3 << " in this class." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						cin >> choice3;
						while (cin.fail() || (choice3 != 1 && choice3 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
							cin >> choice3;
						}
						if (choice3 != 0)
						{
							cout << endl << "Please input the name of the class: ";
							stL.clear();
							cin.ignore(1);
							getline(cin, classname3);
							flclassname3 = filepath + classname3 + ".dat";
							ImportToProgram2(stL, flclassname3);
							FindStudentIn1Class(stL, id3, classname3, check3, st3, count32);
						}
						else
						{
							break;
						}
					}
				}
				if (choice3 != 0)
				{
					if (count32 > 1)
					{
						int check43 = 0;
						cout << "Because there is more than 1 student has the ID " << id3 << " in class " << classname3 << "." << endl;
						cout << "So we need you to input the No of the student you want to edit: ";
						cin >> number3;
						n32 = stL.size();
						while (cin.fail() || (number3 < 1 || number3 > n32))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Error:The No of student must bigger than 0 and smaller than " << n32 << "." << endl;
							cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
							cin >> choice3;
							while (cin.fail() || (choice3 != 1 && choice3 != 0))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Invalid choice." << endl;
								cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
								cin >> choice3;
							}
							if (choice3 == 1)
							{
								cout << "Please input the No of the student you want to edit: ";
								cin >> number3;
							}
							else
							{
								break;
							}
						}
						for (int i = 0; i < n32; i++)
						{
							if (stL[i].id == id3 && stL[i].number == number3)
							{
								check43 = 1;
								st3 = stL[i];
								break;
							}
						}
						while (check43 == 0)
						{
							cout << endl << "There is no student has the No " << number3 << " and ID " << id3 << " in this class." << endl;
							cout << "Please input 1 to input No again or 0 to exit: ";
							cin >> choice3;
							while (cin.fail() || (choice3 != 1 && choice3 != 0))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Invalid choice." << endl;
								cout << "Please input 1 to input No again or 0 to exit: ";
								cin >> choice3;
							}
							if (choice3 == 1)
							{
								cout << endl << "Input No of the student you want to edit: ";
								cin >> number3;
								while (cin.fail() || (number3 < 1 || number3 > n32))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << endl << "Error:The No of student must bigger than 0 and smaller than " << n32 << "." << endl;
									cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
									cin >> choice3;
									while (cin.fail() || (choice3 != 1 && choice3 != 0))
									{
										cin.clear();
										cin.ignore(1024, '\n');
										cout << endl << "Invalid choice." << endl;
										cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
										cin >> choice3;
									}
									if (choice3 == 1)
									{
										cout << endl << "Please input the No of the student you want to edit: ";
										cin >> number3;
									}
									else
									{
										break;
									}
								}
								if (choice3 == 1)
								{
									for (int i = 0; i < n32; i++)
									{
										if (stL[i].id == id3 && stL[i].number == number3)
										{
											check43 = 1;
											st3 = stL[i];
											break;
										}
									}
								}
							}
							else
							{
								break;
							}
						}
					}
					else
					{
						number3 = st3.number;
					}
					if (choice3 != 0)
					{
						cout << "Are you sure you want to edit this student?" << endl;
						cout << "Enter 1 to continue to edit or enter 0 to exit: ";
						cin >> choice3;
						while (cin.fail() || (choice3 != 1 && choice3 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Enter 1 to continue to edit or enter 0 to exit: ";
							cin >> choice3;
						}
						if (choice3 != 0)
						{
							cout << endl;
							Edit1Student(st3);
							UpateIn1Class(stL, number3, st3);
							cout << "Do you want to save what you have done to this class's file?" << endl;
							cout << "Enter 1 to save or 0 to exit: ";
							cin >> choice3s;
							while (cin.fail() || (choice3s != 1 && choice3s != 0))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Invalid choice." << endl;
								cout << "Please enter 1 to save or 0 to exit: ";
								cin >> choice3s;
							}
							if (choice3s == 1)
							{
								fsclassname3 = filepath + classname3 + ".dat";
								ExportFromProgram2(stL, fsclassname3);
							}
							if (count3 > 1)
							{
								cout << endl << "Do you want to update what you edited to orthers student has ID " << id3 << "?" << endl;
								cout << "Enter 1 to update to all student has ID " << id3 << " in all class." << endl;
								cout << "Enter 2 to input the number of the class and the name of class(es) that you want update." << endl;
								cout << "Enter 0 to cancle the updation and exit." << endl;
								cout << "Your choice: ";
								cin >> choice3;
								while (cin.fail() || (choice3 != 0 && choice3 != 1 && choice3 != 2))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << endl << "Invalid choice." << endl;
									cout << "Enter 1 to update to all class (all student has the ID " << id3 << ")." << endl;
									cout << "Enter 2 to input the number of the class and the name of class(es) that you want update." << endl;
									cout << "Enter 0 to cancle the updation and exit." << endl;
									cout << "Your choice: ";
									cin >> choice3;
								}
								if (choice3 == 1)
								{
									UpateInAllClass(stL, id3, st3);
								}
								else
								{
									if (choice3 == 2)
									{
										cout << endl << "Input the number of class that you want to update its (their) data: ";
										cin >> n3;
										while (cin.fail())
										{
											cin.clear();
											cin.ignore(1024, '\n');
											cout << endl << "Input the number of the class that you want to update its (their) data: ";
											cin >> n3;
										}
										for (int i = 0; i < n3; i++)
										{
											choice3 = 2;
											while (choice3 == 2)
											{
												stL.clear();
												cout << endl;
												cin.ignore(1);
												if (n3 > 1)
												{
													cout << "Input the name of class number " << i + 1 << ": ";
												}
												else
												{
													cout << "Input the name of the class you want to update the data: ";
												}
												getline(cin, classname3);
												flclassname3 = filepath + classname3 + ".dat";
												ImportToProgram2(stL, flclassname3);
												DisPlayClass(stL);
												cout << "Are you sure that you want to update what you did to class " << classname3 << "?" << endl;
												cout << "Enter 1 to continue or 2 to input the name of the class again or 0 to exit and input the name of next class: ";
												cin >> choice3;
												while (cin.fail() || (choice3 != 0 && choice3 != 1 && choice3 != 2))
												{
													cin.clear();
													cin.ignore(1024, '\n');
													cout << endl << "Invalid choice." << endl;
													cout << "Please enter 1 to continue to update the data of class " << classname3 << " or 0 to exit and input the name of next class or 2 to input the name of the class again: " << endl;
													cin >> choice3;
												}
											}
											if (choice3 == 1)
											{
												cout << endl << "Please input No of student you want to place an update to: ";
												cin >> number3;
												n32 = stL.size();
												while (cin.fail() || (number3 < 1 || number3 > n32))
												{
													cin.clear();
													cin.ignore(1024, '\n');
													cout << endl << "Error: The No of student must be bigger than 0 and smaller than " << n32 << "." << endl;
													cout << "Please enter 1 to input the No of student again or enter 0 to exit: ";
													cin >> choice3;
													while (choice3 != 0 && choice3 != 1)
													{
														cin.clear();
														cin.ignore(1024, '\n');
														cout << endl << "Invalid choice." << endl;
														cout << "Please enter 1 to input the No of student again or enter 0 to exit: ";
														cin >> choice3;
													}
													if (choice3 == 1)
													{
														cout << endl << "Please input No of student you want to place an update to: ";
														cin >> number3;
													}
												}
												UpateIn1Class(stL, number3, st3);
												cout << "Do you want to save what you have done to this class's file?" << endl;
												cout << "Enter 1 to save or 0 to exit: ";
												cin >> choice3s;
												while (cin.fail() || (choice3s != 1 && choice3s != 0))
												{
													cin.clear();
													cin.ignore(1024, '\n');
													cout << endl << "Invalid choice." << endl;
													cout << "Please enter 1 to save or 0 to exit: ";
													cin >> choice3s;
												}
												if (choice3s == 1)
												{
													fsclassname3 = filepath + classname3 + ".dat";
													ExportFromProgram2(stL, fsclassname3);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			stL.clear();
			int check4 = 0, id4, count4 = 1, count42 = 0, choice4 = -1, choice42, choice4s;
			student st4;
			string classname4;
			string flclassname4, fsclassname4;
			cout << "Do you know the class or the ID of the student you want to remove?" << endl;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			cin >> choice42;
			while (cin.fail() || (choice42 != 1 && choice42 != 2 && choice42 != 0))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Invalid choice." << endl;
				cout << "Do you know the class or the ID of the student you want to remove?" << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				cin >> choice42;
			}
			if (choice42 == 1)
			{
				cout << "Input the name of the class you want to delete student: ";
				cin.ignore(1);
				getline(cin, classname4);
				flclassname4 = filepath + classname4 + ".dat";
				ImportToProgram2(stL, flclassname4);
				while (stL.size() == 0)
				{
					cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
					cin >> choice4;
					while (cin.fail() || (choice4 != 0 && choice4 != 1))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						cin >> choice4;
					}
					if (choice4 == 1)
					{
						cout << "Input the name of the class you want to delete student: ";
						cin.ignore(1);
						getline(cin, classname4);
						flclassname4 = filepath + classname4 + ".dat";
						ImportToProgram2(stL, flclassname4);
					}
					else
					{
						break;
					}
				}
				if (choice4 != 0)
				{
					DisPlayClass(stL);
					cout << "Input the id of the student you want to delete from the class " << classname4 << " (an integer with 8 ditgits): ";
					cin >> id4;
					while (cin.fail() || id4 < temp)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Input the ID of the student you want to remove (ID must be an integer with 8 ditgits): ";
						cin >> id4;
					}
					FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
					while (check4 == 0)
					{
						cout << "Do you want to input the ID of the student you want to remove in this class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin >> choice4;
						while (cin.fail() || (choice4 != 1 && choice4 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input again or 0 to exit: ";
							cin >> choice4;
						}
						if (choice4 == 1)
						{
							cout << "Input the id of the student you want to remove in this the class " << classname4 << " (an integer with 8 digits): ";
							cin >> id4;
							while (cin.fail() || id4 < temp)
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Input the ID of the student you want to remove (ID must be an integer with 8 digits): ";
								cin >> id4;
							}
							FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
						}
						else
						{
							break;
						}
					}
				}
			}
			else
			{
				if (choice42 == 2)
				{
					cout << "Please input his/her ID so we can have you to find the student you want to remove and his/her class too: ";
					cin >> id4;
					while (cin.fail() || id4 < temp)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "(ID must be an integer with 8 digits)" << endl;
						cout << "Please input his/her ID so we can have you to find the student you want to remove and his/her class too: ";
						cin >> id4;
					}
					FindStudentInAllClass(stL, id4, check4, st4, classname4, count4);
					while (check4 == 0)
					{
						cout << "Enter 1 to input the ID of the student you to remove again or enter 0 to exit: ";
						cin >> choice4;
						while (cin.fail() || (choice4 != 1 && choice4 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the ID of the student you wan to remove again or enter 0 to exit: ";
							cin >> choice4;
						}
						if (choice4 != 0)
						{
							cout << "Input the ID of the student you want to remove (an integer with 8 digits): ";
							cin >> id4;
							while (cin.fail() || id4 < temp)
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Input the ID of the student you want to remove (ID must be an interger with 8 digits): ";
								cin >> id4;
							}
							FindStudentInAllClass(stL, id4, check4, st4, classname4, count4);
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					cout << "You can use the function 7 to see all students in all classes and then choose function 5 again to remove the student from the class you want to." << endl;
					break;
				}
			}
			if (check4 != 0 && count4 == 1)
			{
				RemoveStudentFrom1Class(stL, id4, classname4);
				cout << "The class at the moment: " << endl;
				DisPlayClass(stL);
				cout << "Do you want to save what you have done to this class's file?" << endl;
				cout << "Enter 1 to save or 0 to exit: ";
				cin >> choice4s;
				while (cin.fail() || (choice4s != 1 && choice4s != 0))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to save or 0 to exit: ";
					cin >> choice4s;
				}
				if (choice4s == 1)
				{
					fsclassname4 = filepath + classname4 + ".dat";
					ExportFromProgram2(stL, fsclassname4);
				}
			}
			if (check4 != 0 && count4 > 1)
			{
				cout << "How many classes do you want to delete this student?" << endl;
				cout << "Enter 1 to delete this student in all class." << endl;
				cout << "Enter 2 to input the number of the class and the name of class(es) that you want to delete this student." << endl;
				cout << "Enter 0 to cancle the removal and exit." << endl;
				cout << "Your choice: ";
				cin >> choice4;;
				while (cin.fail() || (choice4 != 0 && choice4 != 1 && choice4 != 2))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Invalid choice." << endl;
					cout << "Enter 1 to delete this student in all class." << endl;
					cout << "Enter 2 to input the number of the class and the name of class(es) that you want to delete this student." << endl;
					cout << "Enter 0 to cancle the removal and exit." << endl;
					cout << "Your choice: ";
					cin >> choice4;
				}
				if (choice4 == 1)
				{
					RemoveStudentFromAllClass(stL, id4);
				}
				else
				{
					if (choice4 == 2)
					{
						int n;
						cout << endl << "Input the number of class that you want to delete this student: ";
						cin >> n;
						while (cin.fail() || n > count4)
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Error: There only " << count4 << " class(es) that have (has) the student with the ID " << id4 << endl;
							cout << "Please input the number of class that you want to delete student with ID " << id4 << ": ";
							cin >> n;
						}
						for (int i = 0; i < n; i++)
						{
							choice4 = 1;
							stL.clear();
							if (n > 1)
							{
								cout << "Input the name of class number " << i + 1 << ": ";
							}
							else
							{
								cout << "Input the name of class: ";
							}
							cin.ignore(1);
							getline(cin, classname4);
							flclassname4 = filepath + classname4 + ".dat";
							ImportToProgram2(stL, flclassname4);
							FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
							while (check4 == 0)
							{
								cout << "Please input 1 to input the name of this class again or 0 to exit end input the name of the next class: ";
								cin >> choice4;
								while (cin.fail() || (choice4 != 1 && choice4 != 0))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << "Please input 1 to input the name of this class again or 0 to exit end input the name of the next class: ";
									cin >> choice4;
								}
								if (choice4 == 1)
								{
									if (n > 1)
									{
										cout << "Input the name of class number " << i + 1 << ": ";
									}
									else
									{
										cout << "Input the name of class: ";
									}
									cin.ignore(1);
									stL.clear();
									getline(cin, classname4);
									flclassname4 = filepath + classname4 + ".dat";
									ImportToProgram2(stL, flclassname4);
									FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
								}
								else
								{
									break;
								}
							}
							if (choice4 != 0)
							{
								RemoveStudentFrom1Class(stL, id4, classname4);
								cout << "The class at the moment: " << endl;
								DisPlayClass(stL);
								cout << "Do you want to save what you have done to this class's file?" << endl;
								cout << "Enter 1 to save or 0 to exit: ";
								cin >> choice4s;
								while (cin.fail() || (choice4s != 1 && choice4s != 0))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << "Invalid choice." << endl;
									cout << "Please enter 1 to save or 0 to exit: ";
									cin >> choice4s;
								}
								if (choice4s == 1)
								{
									fsclassname4 = filepath + classname4 + ".dat";
									ExportFromProgram2(stL, fsclassname4);
								}
							}
						}
					}
					else
					{
						break;
					}
				}
			}
			break;
		}
		case 5:
		{
			vector<student>stLA;
			student st5;
			vector<student>stLB;
			stLA.clear();
			stLB.clear();
			string clsAname, clsBname;
			string clsAnametempl, clsBnametempl;
			int choice5 = -1, choice52;
			int id5, check5 = 0, count5 = 1, count52 = 0, number5 = 0;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			cin >> choice52;
			while (cin.fail() || (choice52 != 1 && choice52 != 2 && choice52 != 0))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Invalid choice." << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				cin >> choice52;
			}
			if (choice52 == 1)
			{
				cout << "Input first class (class you want to bring the student out): ";
				cin.ignore(1);
				getline(cin, clsAname);
				clsAnametempl = filepath + clsAname + ".dat";
				ImportToProgram2(stLA, clsAnametempl);
				while (stLA.size() == 0)
				{
					cout << "There nothing to change here." << endl;
					cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
					cin >> choice5;
					while (cin.fail() || (choice5 != 0 && choice5 != 1))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid choice." << endl;
						cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
						cin >> choice5;
					}
					if (choice5 == 0)
					{
						break;
					}
					else
					{
						cout << "Input first class (class you want to bring the student out): ";
						cin.ignore(1);
						getline(cin, clsAname);
						clsAnametempl = filepath + clsAname + ".dat";
						ImportToProgram2(stLA, clsAnametempl);
					}
				}
				if (choice5 != 0)
				{
					cout << "Class " << clsAname << ":" << endl;
					DisPlayClass(stLA);
					cout << "Are you sure you want to change a student in this class?" << endl;
					cout << "Enter 1 to continue pr 0 to exit: ";
					cin >> choice5;
					while (cin.fail() || (choice5 != 1 && choice5 != 0))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to continue or 0 to exit: ";
						cin >> choice5;
					}
				}
				if (choice5 != 0)
				{
					cout << "Input the ID of the student you want to change his/her class (an integers with 8 digits): ";
					cin >> id5;
					while (cin.fail() || id5 < temp)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please input the ID of the student you want to change his/her class (ID must be an interger with 8 digits): ";
						cin >> id5;
					}
					FindStudentIn1Class(stLA, id5, clsAname, check5, st5, count52);
					while (check5 == 0)
					{
						cout << "There is no student has the ID " << id5 << " in this class." << endl;
						cout << "Do you want to input the ID of the student you want to change his/her class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin >> choice5;
						while (cin.fail() || (choice5 != 1 && choice5 != 0))
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input ID again or 0 to exit: ";
							cin >> choice5;
						}
						if (choice5 == 1)
						{
							cout << "Input the ID of the student you want to change his/her class (an integer with 8 digits): ";
							cin >> id5;
							while (cin.fail() || id5 < temp)
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Please input the ID of the student you want to change his/her class (ID must be an integer with 8 digits): ";
								cin >> id5;
							}
							FindStudentIn1Class(stL, id5, clsAname, check5, st5, count52);
						}
						else
						{
							break;
						}
					}
				}
			}
			else
			{
				if (choice52 == 2)
				{
					cout << "Input the ID of the student (an integer with 8 digits): ";
					cin >> id5;
					while (cin.fail() || id5 < temp)
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please input the ID of the student you want to change his/her class (ID must be an integer with 8 digits): ";
						cin >> id5;
					}
					FindStudentInAllClass(stLA, id5, check5, st5, clsAname, count5);
					while (check5 == 0)
					{
						cout << "The student with the ID " << id5 << " does not exists." << endl;
						cout << "You can enter 1 to input the student ID again or enter 0 to exit: ";
						cin >> choice5;
						while (cin.fail() || (choice5 != 1 && choice5 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the student ID again or enter 0 to exit: ";
							cin >> choice5;
						}
						if (choice5 == 0)
						{
							break;
						}
						else
						{
							cout << "Input the ID of the student (an integer with 8 digtis): ";
							cin >> id5;
							while (cin.fail() || id5 < temp)
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Please input the ID of the student you want to change his/her class (ID must be an integer with 8 ditgits): ";
								cin >> id5;
							}
							FindStudentInAllClass(stLA, id5, check5, st5, clsAname, count5);
						}
					}
					if (choice5 == 0)
					{
						break;
					}
					if (check5 != 0 && count5 > 1)
					{
						stLA.clear();
						cout << "Because there are more than one class that have the student with the ID " << id5 << "." << endl;
						cout << "So, please input the name of the class which you want this student to move out: ";
						cin.ignore(1);
						getline(cin, clsAname);
						clsAnametempl = filepath + clsAname + ".dat";
						ImportToProgram2(stLA, clsAnametempl);
						DisPlayClass(stLA);
						FindStudentIn1Class(stLA, id5, clsAname, check5, st5, count52);
						while (check5 == 0)
						{
							stLA.clear();
							cout << "Do you want to input the class you want this student to move out (first class) again?" << endl;
							cout << "Enter 1 to input again or 0 to exit: ";
							cin >> choice5;
							while (cin.fail() || (choice5 != 1 && choice5 != 0))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Invalid choice." << endl;
								cout << "Please enter 1 to input again or 0 to exit: ";
								cin >> choice5;
							}
							if (choice5 == 1)
							{
								cout << "Input the name of the first class: ";
								cin.ignore(1);
								getline(cin, clsAname);
								clsAnametempl = filepath + clsAname + ".dat";
								ImportToProgram2(stLA, clsAnametempl);
								DisPlayClass(stLA);
								FindStudentIn1Class(stLA, id5, clsAname, check5, st5, count52);
							}
							else
							{
								break;
							}
						}

					}
					if (check5 != 0 && count5 == 1)
					{
						FindStudentIn1Class(stLA, id5, clsAname, check5, st5, count52);
					}
				}
				else
				{
					cout << "Please use the 7th function to see which class is the student you want to change class staying in. " << endl;
					break;
				}
			}
			if (check5 != 0)
			{
				int check53 = 0;
				if (count5 >= 1 && count52 == 1)
				{
					number5 = st5.number;
				}
				if (count52 > 1)
				{
					cout << "Because there are more than one student that have the ID " << id5 << "." << endl;
					cout << "Please input the No of the student you want to change: ";
					cin >> number5;
					int n5 = stLA.size();
					while (cin.fail() || (number5 < 1 || number5 > n5))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "The No of the student must be bigger than 0 and smaller than " << n5 << "." << endl;
						cout << "Please input the No of the student you want to change: ";
						cin >> number5;
					}
					for (int i = 0; i < n5; i++)
					{
						if (stLA[i].id == id5 && stLA[i].number == number5)
						{
							if (stLA[i].number == number5)
							{
								check53 = 1;
								break;
							}
						}
					}
					while (check53 == 0)
					{
						cout << "There is no student has No " << number5 << " and ID " << id5 << "." << endl;
						cout << "Please enter 1 to input the No again or 0 to exit: ";
						cin >> choice5;
						while (cin.fail() || (choice5 != 1 && choice5 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the No again or 0 to exit: ";
							cin >> choice5;
						}
						if (choice5 == 1)
						{
							cout << "Inout No: ";
							cin >> number5;
							while (cin.fail() || (number5 < 1 || number5 > n5))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "The No of the student must be bigger than 0 and smaller than " << n5 << "." << endl;
								cout << "Please input the No of the student you want to change: ";
								cin >> number5;
							}
							for (int i = 0; i < n5; i++)
							{
								if (stLA[i].id == id5 && stLA[i].number == number5)
								{
									if (stLA[i].number == number5)
									{
										check53 = 1;
										break;
									}
								}
							}
						}
						else
						{
							break;
						}
					}
				}
				if (choice5 != 0)
				{
					choice5 = 2;
					while (choice5 == 2)
					{
						stLB.clear();
						cout << "Input second class (class to want to put the student into): ";
						cin.ignore(1);
						getline(cin, clsBname);
						clsBnametempl = filepath + clsBname + ".dat";
						ImportToProgram2(stLB, clsBnametempl);
						if (stLB.size() == 0)
						{
							cout << endl << "The class may not exist." << endl;
							cout << "So, if you move a student into this class, you may create a new class with one student." << endl << endl;
						}
						else
						{
							DisPlayClass(stLB);
						}
						cout << "Are you sure you want to change student into this class?" << endl;
						cout << "Enter 1 to continue or 2 to input the name of the second class again or 0 to exit: ";
						cin >> choice5;
						while (cin.fail() || (choice5 != 1 && choice5 != 0 && choice5 != 2))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Please enter 1 to continue or 2 to input the name of the second class again or 0 to exit: ";
							cin >> choice5;
						}
						if (choice5 == 1)
						{
							int check52 = 0;
							ChangeStudentFromClassAToClassB(stLA, stLB, number5, check52, id5);
							if (check52 == 1)
							{
								cout << endl << "Error: This student is already in class " << clsBname << "." << endl;
							}
							else
							{
								cout << "Class " << clsAname << " at the moment:" << endl;
								DisPlayClass(stLA);
								cout << "Class " << clsBname << " at the moment:" << endl;
								DisPlayClass(stLB);
								int choice5s;
								cout << "Do you want to save what you have done to class" << clsAname << "'s file and class" << clsBname << "'s file?" << endl;
								cout << "Enter 1 to save or 0 to exit: ";
								cin >> choice5s;
								while (cin.fail() || (choice5s != 1 && choice5s != 0))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << "Invalid choice." << endl;
									cout << "Please enter 1 to save or 0 to exit: ";
									cin >> choice5s;
								}
								if (choice5s == 1)
								{
									string clsAnametemps = filepath + clsAname + ".dat";
									ExportFromProgram2(stLA, clsAnametemps);
									string clsBnametemps = filepath + clsBname + ".dat";
									ExportFromProgram2(stLB, clsBnametemps);
									if (CheckClassnameSavedorNot(clsBname) == 0)
									{
										AddClassname(clsBname);
									}
								}
							}
						}
					}
				}
			}
			break;
		}
		case 6:
		{
			stL.clear();
			DisPlayAllClass(stL);
			break;
		}
		case 7:
		{
			stL.clear();
			string classname7;
			int choice7 = 1;
			cout << "Enter the class you want to view: ";
			cin.ignore(1);
			getline(cin, classname7);
			string fclassname7 = filepath + classname7 + ".dat";
			ImportToProgram2(stL, fclassname7);
			while (stL.size() == 0)
			{
				cout << "Do you want to enter the name of the class you want view again?" << endl;
				cout << "Enter 1 to input the name of the class again." << endl;
				cout << "Enter 0 to exit." << endl;
				cout << "Your choice: ";
				cin >> choice7;
				while (cin.fail() || (choice7 != 1 && choice7 != 0))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Invalid choice." << endl;
					cout << "Enter 1 to input the name of the class again." << endl;
					cout << "Enter 0 to exit." << endl;
					cout << "Your choice: ";
					cin >> choice7;
				}
				if (choice7 == 1)
				{
					cout << "Enter the class you want to view: ";
					cin.ignore(1);
					getline(cin, classname7);
					fclassname7 = filepath + classname7 + ".dat";
					ImportToProgram2(stL, fclassname7);
				}
				else
				{
					break;
				}
			}
			if (choice7 == 1)
			{
				cout << "The list of students in your class:" << endl;
				DisPlayClass(stL);
			}
			break;
		}
		}
	}
	return;
}