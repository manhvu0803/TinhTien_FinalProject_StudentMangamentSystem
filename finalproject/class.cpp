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
	cout << "Please input the information of the new student" << endl;
	cout << "ID           : ";
	cin >> nst.id;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Please input the information of the new student" << endl;
		cout << "ID          : ";
		cin >> nst.id;
	}
	FindStudentInAllClass(stLtemp, nst.id, check, nst, classname, count);
	while (check == 1)
	{
		cout << "Error: The ID " << nst.id << " has already been given to student name " << nst.Lastname << " " << nst.Firstname << " in class " << classname << "." << endl;
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
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Please input the information of the new student" << endl;
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
	cout << "Lastname     : "; cin.ignore(1); getline(cin, nst.Lastname);
	cout << "Firstname    : "; getline(cin, nst.Firstname);
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
	nst.No = stL.size() + 1;
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
		st.No = stoi(temp);
		getline(fload, temp, ',');
		st.id = stoi(temp);
		getline(fload, temp, ',');
		st.Lastname = temp;
		getline(fload, temp, ',');
		st.Firstname = temp;
		getline(fload, temp, ',');
		st.gender = temp[0];
		getline(fload, temp, '/');
		st.DoB.d = stoi(temp);
		getline(fload, temp, '/');
		st.DoB.m = stoi(temp);
		getline(fload, temp);
		st.DoB.y = stoi(temp);
		st.No = stL.size() + 1;
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
	int distance = st.Lastname.size() + 4;
	int distance2 = (21 - (st.Lastname.size() - 8)) + st.Firstname.size();
	int distance3 = 8 - st.Firstname.size() + 11;
	cout << setw(5) << st.No << setw(12) << st.id << setw(distance) << st.Lastname << setw(distance2) << st.Firstname
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
	cout << "No: " << st.No << endl;
	cout << "ID: " << st.id << endl;
	cout << "Lastname: " << st.Lastname << endl;
	cout << "Firstname: " << st.Firstname << endl;
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
	cout << setw(5) << "No" << setw(6) << "ID" << setw(18) << "Lastname" << setw(30) << "Firstname" << setw(15) << "Gender"
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
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (fload >> classname)
		{
			fclassname = classname + "/" + classname + ".dat";
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
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (fload >> classname)
		{
			fclassname = classname + "/" + classname + ".dat";
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
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Please input new ID: ";
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
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please input new ID: ";
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
			getline(cin, st.Lastname);
			cout << "Firstname: ";
			getline(cin, st.Firstname);
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

void UpateIn1Class(vector<student>& stL, int No, student st)
{
	int n = stL.size();
	int choice;
	for (int i = 0; i < n; i++)
	{
		if (stL[i].No == No)
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
	fload.open("allclassname.txt");
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
			string flname = classname + "/" + classname + ".dat";
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
					stL[j].No = stL[j].No - 1;
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
	fload.open("allclassname.txt");
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
			string flname = classname + "/" + classname + ".dat";
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

void ChangeStudentFromClassAToClassB(vector<student>& stLA, vector<student>& stLB, int No, int& check, int id)
{
	int nA = stLA.size();
	int nB = stLB.size();
	check = 0;
	for (int i = 0; i < nA; i++)
	{
		if (stLA[i].No == No)
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
				stLA[i].No = stLB.size() + 1;
				stLB.push_back(stLA[i]);
				nB = stLB.size();
				for (int j = i + 1; j < nA; j++)
				{
					stLA[j].No = stLA[j].No - 1;
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
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		while (fload >> classname)
		{
			stL.clear();
			flname = classname + "/" + classname + ".dat";
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
				flname = classnametemp + "/" + classnametemp + ".dat";
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
		fsave << stL[i].No << "," << stL[i].id << "," << stL[i].Lastname << "," << stL[i].Firstname << "," << stL[i].gender << ","
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
	while(fload>>st.No)
	{
		fload >> st.id;
		getline(fload, st.Lastname);
		getline(fload, st.Lastname);
		getline(fload, st.Firstname);
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
		fsave << stL[i].No << endl;
		fsave << stL[i].id << endl;
		fsave << stL[i].Lastname << endl;
		fsave << stL[i].Firstname << endl;
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
				Notemp = stL[i].No;
				stL[i].No = stL[j].No;
				stL[j].No = Notemp;
				sttemp = stL[i];
				stL[i] = stL[j];
				stL[j] = sttemp;
			}
		}
	}
}

int checkaccounteon(student st)
{
	int check = 0;
	ifstream fload;
	fload.open("accountsave.txt");
	if (!fload.is_open())
	{
		cout << "Can not file any data of any accounts." << endl;
	}
	else
	{
		while (fload >> st.acc.ID)
		{
			getline(fload, st.acc.password);
			getline(fload, st.acc.password);
			fload >> st.acc.status;
			if (st.acc.ID == st.id) //already existed.
			{
				if (st.acc.status == 1) //activation is still working
				{
					check = 1;
					break;
				}
				if (st.acc.status == 0) //has been disabled.
				{
					check = -1;
					break;
				}
			}
			if (check != 0)
			{
				break;
			}
		}
		fload.close();
	}
	return check; //hasn't been existed.
}

void pushbacktoaccfile(student& st)
{
	if (st.DoB.d < 10)
	{
		st.acc.password = "0" + to_string(st.DoB.d);
	}
	else
	{
		st.acc.password = to_string(st.DoB.d);
	}
	if (st.DoB.m < 10)
	{
		st.acc.password = st.acc.password + "0" + to_string(st.DoB.m);
	}
	else
	{
		st.acc.password = st.acc.password + to_string(st.DoB.m);
	}
	st.acc.password = st.acc.password + to_string(st.DoB.y);
	st.acc.ID = st.id;
	st.acc.status = 1;
	ofstream fsave;
	string fsname;
	//fsname = classname + "/" + classname + ".txt";
	fsave.open("accountsave.txt", ios::app);
	if (!fsave.is_open())
	{
		cout << "Can not save the account." << endl;
	}
	else
	{
		ifstream fload;
		vector<account>accL;
		loadaccsavefile(fload, accL);
		if (accL.size() > 0)
		{
			fsave << endl;
		}
		fsave << st.acc.ID;
		fsave << endl << st.acc.password;
		fsave << endl << st.acc.status;
		fsave.close();
	}
}

void loadaccsavefile(ifstream& fload, vector<account>& accL)
{
	account acc;
	fload.open("accountsave.txt");
	if (!fload.is_open())
	{
		cout << "Can not file any data of any accounts." << endl;
	}
	else
	{
		while (fload >> acc.ID)
		{
			getline(fload, acc.password);
			getline(fload, acc.password);
			fload >> acc.status;
			accL.push_back(acc);
		}
		fload.close();
	}
}

void saveaccount(ofstream& fsave, vector<account> accL)
{
	fsave.open("accountsave.txt");
	if (!fsave.is_open())
	{
		cout << "Can not find any data of any accounts." << endl;
	}
	else
	{
		int n = accL.size();
		for (int i = 0; i < n; i++)
		{
			if (i > 0)
			{
				fsave << endl;
			}
			fsave << accL[i].ID;
			fsave << endl;
			fsave << accL[i].password;
			fsave << endl;
			fsave << accL[i].status;
		}
		fsave.close();
	}
}

void activeacccount(student st)
{
	ifstream fload;
	vector<account>accL;
	loadaccsavefile(fload, accL);
	int check = 0;
	int n = accL.size();
	for (int i = 0; i < n; i++)
	{
		if (accL[i].ID == st.id)
		{
			accL[i].status = 1;
			break;
		}
	}
	ofstream fsave;
	saveaccount(fsave, accL);
}

void disableaccount(student st)
{
	vector<account>accL;
	ifstream fload;
	loadaccsavefile(fload, accL);
	int n = accL.size();
	for (int i = 0; i < n; i++)
	{
		if (accL[i].ID == st.id)
		{
			accL[i].status = 0;
			break;
		}
	}
	ofstream fsave;
	saveaccount(fsave, accL);
}


void ManageClassFunction()
{
	vector<student> stL;
	int choice = -1;
	string choicestr;
	cout << "================================================CLASS MANAGE PROGRAM===================================================" << endl << endl;
	cout << "What do you want to do: "; cout << endl;
	while (choice != 0)
	{
		cout << endl;
		cout << "Enter 0 to exit the program.                                         " << endl;
		cout << "Enter 1 to import your data to program. (tran csv file to dat file)  " << endl;
		cout << "Enter 2 to input new class.                                          " << endl;
		cout << "Enter 3 to add new student.                                          " << endl;
		cout << "Enter 4 to edit an existing student.                                 " << endl;
		cout << "Enter 5 to remove a student.                                         " << endl;
		cout << "Enter 6 to change student from class A to class B.                   " << endl;
		cout << "Enter 7 to view list of classes.                                     " << endl;
		cout << "Enter 8 to view list of students in a class.                         " << endl;
		cout << "Enter 9 to export the data from program. (tran dat file to csv file) " << endl << endl;
		cout << "Your choice: ";
		cin >> choice;
		while (cin.fail() || (choice < 0 || choice>9))
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
		case 2:
		{
			stL.clear();
			int choice2 = -1, choice2s;
			int n = -1;
			cout << endl << "Please input the number of the student in the class: ";
			cin >> n;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << endl << "Please input the number of the student in the class: ";
				cin >> n;
			}
			while (n <= 0)
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
					cin >> n;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << endl << "Please input the number of the student in the class: ";
						cin >> n;
					}
				}
			}
			if (n > 0)
			{
				CreateNewClass(stL, n);
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
					string classname2;
					cout << endl << "Enter the name of the new class: ";
					cin.ignore(1);
					getline(cin, classname2);
					string fsclassname2 = classname2 + "/" + classname2 + ".dat";
					ExportFromProgram2(stL, fsclassname2);
				};
			}
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
			flclassname1 = classname1 + "/" + classname1 + ".csv";
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
					flclassname1 = classname1 + "/" + classname1 + ".csv";
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
				string fsclassname1 = classname1 + "/" + classname1 + ".dat";
				ExportFromProgram2(stL, fsclassname1);
			}
			break;
		}
		case 3:
		{
			stL.clear();
			int check3 = 0;
			int choice3 = -1, choice3s;
			cout << endl << "Which class do you want to add new student?" << endl;
			cout << "Class: ";
			string classname3, flclassname3;
			cin.ignore(1);
			getline(cin, classname3);
			flclassname3 = classname3 + "/" + classname3 + ".dat";
			ImportToProgram2(stL, flclassname3);
			while (stL.size() == 0)
			{
				cout << "Do you want to input the name of the class that you want to add new student again?" << endl;
				cout << "Enter 1 to continue to input the name of the class again or 0 to exit: ";
				cin >> choice3;
				while (cin.fail() || (choice3 != 0 && choice3 != 1))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << endl << "Invalid choice." << endl;
					cout << "Please enter 1 to continue to input the name of the class again or 0 to exit: ";
					cin >> choice3;
				}
				if (choice3 == 1)
				{
					cout << endl << "Which class do you want to add new student? " << endl;
					cout << "Class: ";
					cin.ignore(1);
					getline(cin, classname3);
					flclassname3 = classname3 + "/" + classname3 + ".dat";
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
				AddOneStudent(stL);
				SortClassInAscendingOrderByID(stL);
				cout << endl << "Addition is updated:" << endl;
				DisPlayClass(stL);
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
					string fsclassname3 = classname3 + "/" + classname3 + ".dat";
					ExportFromProgram2(stL, fsclassname3);
				}
			}
			break;
		}
		case 4:
		{
			stL.clear();
			int check4 = 0, id4, count4 = 1, count42 = 0, n4, No4, n42;
			int choice42, choice4 = -1, choice4s;
			string classname4;
			string flclassname4;
			student st4;
			string fsclassname4;
			cout << endl << "Do you know the class or the ID of the student you want to edit?" << endl;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			cin >> choice42;
			while (cin.fail() || (choice42 != 1 && choice42 != 2 && choice42 != 0))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << endl << "Invalid choice." << endl;
				cout << "Do you know the class or the ID of the student you want to edit?" << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				cin >> choice42;
			}
			if (choice42 == 1)
			{
				cout << endl << "Input the name of the class you want to edit student: ";
				cin.ignore(1);
				getline(cin, classname4);
				flclassname4 = classname4 + "/" + classname4 + ".dat";
				ImportToProgram2(stL, flclassname4);
				while (stL.size() == 0)
				{
					cout << endl << "There is nothing to edit here." << endl;
					cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
					cin >> choice4;
					while (cin.fail() || (choice4 != 0 && choice4 != 1))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << endl << "Invalid choice." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						cin >> choice4;
					}
					if (choice4 == 1)
					{
						cout << endl << "Input the name of the class you want to edit student: ";
						cin.ignore(1);
						getline(cin, classname4);
						flclassname4 = classname4 + "/" + classname4 + ".dat";
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
					cout << "Input the ID of the student you want to edit in this class: ";
					cin >> id4;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please in put the ID of the student you want to edit in this class: ";
						cin >> id4;
					}
					FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
					while (check4 == 0)
					{
						cout << endl << "Do you want to input the ID of the student you want to edit in this class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin >> choice4;
						while (cin.fail() || (choice4 != 1 && choice4 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Please enter 1 to input ID again or 0 to exit: ";
							cin >> choice4;
						}
						if (choice4 == 1)
						{
							cout << endl << "Input the ID of the student you want to edit in this class: ";
							cin >> id4;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Please input the ID of the student you want to edit in this class: ";
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
					cout << endl << "Please input the ID of the student you need to edit so we can find he/she for you and also his/her class too: ";
					cin >> id4;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << endl << "Please input the ID of the student that you need to edit so we can find he/she for you and also his/her class too: ";
						cin >> id4;
					}
					FindStudentInAllClass(stL, id4, check4, st4, classname4, count4);
					while (check4 == 0)
					{
						cout << endl << "Enter 1 to input the ID of the student you to edit again or enter 0 to exit: ";
						cin >> choice4;
						while (cin.fail() || (choice4 != 1 && choice4 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Please enter 1 to input the ID of the student you wan to edit again or enter 0 to exit: ";
							cin >> choice4;
						}
						if (choice4 != 0)
						{
							cout << endl << "Input the ID of the student you want to edit: ";
							cin >> id4;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Please input the ID of the student you want to edit: ";
								cin >> id4;
							}
							FindStudentInAllClass(stL, id4, check4, st4, classname4, count4);
						}
						else
						{
							break;
						}
					}
					if (count4 == 1)
					{
						FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
					}
				}
				else
				{
					cout << endl << "You can use the function 7 to see all students in all classes and then choose function 4 again to edit the student you want to." << endl;
				}
			}
			if (check4 != 0)
			{
				cin.ignore(1);
				if (count4 > 1)
				{
					cout << "Because there are more than one class that constant to student has ID" << id4 << "." << endl;
					cout << "So we need you to chose the class of the student who you want to edit." << endl;
					cout << "Please input the name of the class: ";
					getline(cin, classname4);
					stL.clear();
					flclassname4 = classname4 + "/" + classname4 + ".dat";
					ImportToProgram2(stL, flclassname4);
					FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
					while (check4 == 0)
					{
						cout << endl << "There is no student has the ID " << id4 << " in this class." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						cin >> choice4;
						while (cin.fail() || (choice4 != 1 && choice4 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
							cin >> choice4;
						}
						if (choice4 != 0)
						{
							cout << endl << "Please input the name of the class: ";
							stL.clear();
							cin.ignore(1);
							getline(cin, classname4);
							flclassname4 = classname4 + "/" + classname4 + ".dat";
							ImportToProgram2(stL, flclassname4);
							FindStudentIn1Class(stL, id4, classname4, check4, st4, count42);
						}
						else
						{
							break;
						}
					}
				}
				if (choice4 != 0)
				{
					if (count42 > 1)
					{
						int check43 = 0;
						cout << "Because there is more than 1 student has the ID " << id4 << " in class " << classname4 << "." << endl;
						cout << "So we need you to input the No of the student you want to edit: ";
						cin >> No4;
						n42 = stL.size();
						while (cin.fail() || (No4 < 1 || No4 > n42))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Error:The No of student must bigger than 0 and smaller than " << n42 << "." << endl;
							cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
							cin >> choice4;
							while (cin.fail() || (choice4 != 1 && choice4 != 0))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Invalid choice." << endl;
								cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
								cin >> choice4;
							}
							if (choice4 == 1)
							{
								cout << "Please input the No of the student you want to edit: ";
								cin >> No4;
							}
							else
							{
								break;
							}
						}
						for (int i = 0; i < n42; i++)
						{
							if (stL[i].id == id4 && stL[i].No == No4)
							{
								check43 = 1;
								st4 = stL[i];
								break;
							}
						}
						while (check43 == 0)
						{
							cout << endl << "There is no student has the No " << No4 << " and ID " << id4 << " in this class." << endl;
							cout << "Please input 1 to input No again or 0 to exit: ";
							cin >> choice4;
							while (cin.fail() || (choice4 != 1 && choice4 != 0))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Invalid choice." << endl;
								cout << "Please input 1 to input No again or 0 to exit: ";
								cin >> choice4;
							}
							if (choice4 == 1)
							{
								cout << endl << "Input No of the student you want to edit: ";
								cin >> No4;
								while (cin.fail() || (No4 < 1 || No4 > n42))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << endl << "Error:The No of student must bigger than 0 and smaller than " << n42 << "." << endl;
									cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
									cin >> choice4;
									while (cin.fail() || (choice4 != 1 && choice4 != 0))
									{
										cin.clear();
										cin.ignore(1024, '\n');
										cout << endl << "Invalid choice." << endl;
										cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
										cin >> choice4;
									}
									if (choice4 == 1)
									{
										cout << endl << "Please input the No of the student you want to edit: ";
										cin >> No4;
									}
									else
									{
										break;
									}
								}
								if (choice4 == 1)
								{
									for (int i = 0; i < n42; i++)
									{
										if (stL[i].id == id4 && stL[i].No == No4)
										{
											check43 = 1;
											st4 = stL[i];
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
						No4 = st4.No;
					}
					if (choice4 != 0)
					{
						cout << "Are you sure you want to edit this student?" << endl;
						cout << "Enter 1 to continue to edit or enter 0 to exit: ";
						cin >> choice4;
						while (cin.fail() || (choice4 != 1 && choice4 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Enter 1 to continue to edit or enter 0 to exit: ";
							cin >> choice4;
						}
						if (choice4 != 0)
						{
							cout << endl;
							Edit1Student(st4);
							UpateIn1Class(stL, No4, st4);
							cout << "Do you want to save what you have done to this class's file?" << endl;
							cout << "Enter 1 to save or 0 to exit: ";
							cin >> choice4s;
							while (cin.fail() || (choice4s != 1 && choice4s != 0))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "Invalid choice." << endl;
								cout << "Please enter 1 to save or 0 to exit: ";
								cin >> choice4s;
							}
							if (choice4s == 1)
							{
								fsclassname4 = classname4 + "/" + classname4 + ".dat";
								ExportFromProgram2(stL, fsclassname4);
							}
							if (count4 > 1)
							{
								cout << endl << "Do you want to update what you edited to orthers student has ID " << id4 << "?" << endl;
								cout << "Enter 1 to update to all student has ID " << id4 << " in all class." << endl;
								cout << "Enter 2 to input the number of the class and the name of class(es) that you want update." << endl;
								cout << "Enter 0 to cancle the updation and exit." << endl;
								cout << "Your choice: ";
								cin >> choice4;
								while (cin.fail() || (choice4 != 0 && choice4 != 1 && choice4 != 2))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << endl << "Invalid choice." << endl;
									cout << "Enter 1 to update to all class (all student has the ID " << id4 << ")." << endl;
									cout << "Enter 2 to input the number of the class and the name of class(es) that you want update." << endl;
									cout << "Enter 0 to cancle the updation and exit." << endl;
									cout << "Your choice: ";
									cin >> choice4;
								}
								if (choice4 == 1)
								{
									UpateInAllClass(stL, id4, st4);
								}
								else
								{
									if (choice4 == 2)
									{
										cout << endl << "Input the number of class that you want to update its (their) data: ";
										cin >> n4;
										while (cin.fail())
										{
											cin.clear();
											cin.ignore(1024, '\n');
											cout << endl << "Input the number of the class that you want to update its (their) data: ";
											cin >> n4;
										}
										for (int i = 0; i < n4; i++)
										{
											choice4 = 2;
											while (choice4 == 2)
											{
												stL.clear();
												cout << endl;
												cin.ignore(1);
												if (n4 > 1)
												{
													cout << "Input the name of class number " << i + 1 << ": ";
												}
												else
												{
													cout << "Input the name of the class you want to update the data: ";
												}
												getline(cin, classname4);
												flclassname4 = classname4 + "/" + classname4 + ".dat";
												ImportToProgram2(stL, flclassname4);
												DisPlayClass(stL);
												cout << "Are you sure that you want to update what you did to class " << classname4 << "?" << endl;
												cout << "Enter 1 to continue or 2 to input the name of the class again or 0 to exit: ";
												cin >> choice4;
												while (cin.fail() || (choice4 != 0 && choice4 != 1 && choice4 != 2))
												{
													cin.clear();
													cin.ignore(1024, '\n');
													cout << endl << "Invalid choice." << endl;
													cout << "Please enter 1 to continue to update the data of class " << classname4 << " or 0 to exit or 2 to input the name of the class again: " << endl;
													cin >> choice4;
												}
											}
											if (choice4 == 1)
											{
												cout << endl << "Please input No of student you want to place an update to: ";
												cin >> No4;
												n42 = stL.size();
												while (cin.fail() || (No4 < 1 || No4 > n42))
												{
													cin.clear();
													cin.ignore(1024, '\n');
													cout << endl << "Error: The No of student must be bigger than 0 and smaller than " << n42 << "." << endl;
													cout << "Please enter 1 to input the No of student again or enter 0 to exit: ";
													cin >> choice4;
													while (choice4 != 0 && choice4 != 1)
													{
														cin.clear();
														cin.ignore(1024, '\n');
														cout << endl << "Invalid choice." << endl;
														cout << "Please enter 1 to input the No of student again or enter 0 to exit: ";
														cin >> choice4;
													}
													if (choice4 == 1)
													{
														cout << endl << "Please input No of student you want to place an update to: ";
														cin >> No4;
													}
												}
												UpateIn1Class(stL, No4, st4);
												cout << "Do you want to save what you have done to this class's file?" << endl;
												cout << "Enter 1 to save or 0 to exit: ";
												cin >> choice4s;
												while (cin.fail() || (choice4s != 1 && choice4s != 0))
												{
													cin.clear();
													cin.ignore(1024, '\n');
													cout << endl << "Invalid choice." << endl;
													cout << "Please enter 1 to save or 0 to exit: ";
													cin >> choice4s;
												}
												if (choice4s == 1)
												{
													fsclassname4 = classname4 + "/" + classname4 + ".dat";
													ExportFromProgram2(stL, fsclassname4);
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
		case 5:
		{
			stL.clear();
			int check5 = 0, id5, count5 = 1, count52 = 0, choice5 = -1, choice52, choice5s;
			student st5;
			string classname5;
			string flclassname5, fsclassname5;
			cout << "Do you know the class or the ID of the student you want to remove?" << endl;
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
				cout << "Do you know the class or the ID of the student you want to remove?" << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				cin >> choice52;
			}
			if (choice52 == 1)
			{
				cout << "Input the name of the class you want to delete student: ";
				cin.ignore(1);
				getline(cin, classname5);
				flclassname5 = classname5 + "/" + classname5 + ".dat";
				ImportToProgram2(stL, flclassname5);
				while (stL.size() == 0)
				{
					cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
					cin >> choice5;
					while (cin.fail() || (choice5 != 0 && choice5 != 1))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						cin >> choice5;
					}
					if (choice5 == 1)
					{
						cout << "Input the name of the class you want to delete student: ";
						cin.ignore(1);
						getline(cin, classname5);
						flclassname5 = classname5 + "/" + classname5 + ".dat";
						ImportToProgram2(stL, flclassname5);
					}
					else
					{
						break;
					}
				}
				if (choice5 != 0)
				{
					DisPlayClass(stL);
					cout << "Input the id of the student you want to delete from the class " << classname5 << ": ";
					cin >> id5;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Input the ID of the student you want to remove: ";
						cin >> id5;
					}
					FindStudentIn1Class(stL, id5, classname5, check5, st5, count52);
					while (check5 == 0)
					{
						cout << "Do you want to input the ID of the student you want to edit in this class again?" << endl;
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
							cout << "Input the id of the student you want to edit in this the class " << classname5 << ": ";
							cin >> id5;
							FindStudentIn1Class(stL, id5, classname5, check5, st5, count52);
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
					cout << "Please input his/her ID so we can have you to find the student you want to remove and his/her class too: ";
					cin >> id5;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please input his/her ID so we can have you to find the student you want to remove and his/her class too: ";
						cin >> id5;
					}
					FindStudentInAllClass(stL, id5, check5, st5, classname5, count5);
					while (check5 == 0)
					{
						cout << "Enter 1 to input the ID of the student you to edit again or enter 0 to exit: ";
						cin >> choice5;
						while (cin.fail() || (choice5 != 1 && choice5 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the ID of the student you wan to edit again or enter 0 to exit: ";
							cin >> choice5;
						}
						if (choice5 != 0)
						{
							cout << "Input the ID of the student you want to remove: ";
							cin >> id5;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Input the ID of the student you want to remove: ";
								cin >> id5;
							}
							FindStudentInAllClass(stL, id5, check5, st5, classname5, count5);
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
			if (check5 != 0 && count5 == 1)
			{
				RemoveStudentFrom1Class(stL, id5, classname5);
				cout << "The class at the moment: " << endl;
				DisPlayClass(stL);
				cout << "Do you want to save what you have done to this class's file?" << endl;
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
					fsclassname5 = classname5 + "/" + classname5 + ".dat";
					ExportFromProgram2(stL, fsclassname5);
				}
			}
			if (check5 != 0 && count5 > 1)
			{
				cout << "How many classes do you want to delete this student?" << endl;
				cout << "Enter 1 to delete this student in all class." << endl;
				cout << "Enter 2 to input the number of the class and the name of class(es) that you want to delete this student." << endl;
				cout << "Enter 0 to cancle the removal and exit." << endl;
				cout << "Your choice: ";
				cin >> choice5;;
				while (cin.fail() || (choice5 != 0 && choice5 != 1 && choice5 != 2))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Invalid choice." << endl;
					cout << "Enter 1 to delete this student in all class." << endl;
					cout << "Enter 2 to input the number of the class and the name of class(es) that you want to delete this student." << endl;
					cout << "Enter 0 to cancle the removal and exit." << endl;
					cout << "Your choice: ";
					cin >> choice5;
				}
				if (choice5 == 1)
				{
					RemoveStudentFromAllClass(stL, id5);
				}
				else
				{
					if (choice5 == 2)
					{
						int n;
						cout << endl << "Input the number of class that you want to delete this student: ";
						cin >> n;
						while (cin.fail() || n > count5)
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Error: There only " << count5 << " class(es) that have (has) the student with the ID " << id5 << endl;
							cout << "Please input the number of class that you want to delete student with ID " << id5 << ": ";
							cin >> n;
						}
						for (int i = 0; i < n; i++)
						{
							choice5 = 1;
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
							getline(cin, classname5);
							flclassname5 = classname5 + "/" + classname5 + ".dat";
							ImportToProgram2(stL, flclassname5);
							FindStudentIn1Class(stL, id5, classname5, check5, st5, count52);
							while (check5 == 0)
							{
								cout << "Please input 1 to input the name of this class again or 0 to exit end input the name of the next class: ";
								cin >> choice5;
								while (cin.fail() || (choice5 != 1 && choice5 != 0))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << "Please input 1 to input the name of this class again or 0 to exit end input the name of the next class: ";
									cin >> choice5;
								}
								if (choice5 == 1)
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
									getline(cin, classname5);
									flclassname5 = classname5 + "/" + classname5 + ".dat";
									ImportToProgram2(stL, flclassname5);
									FindStudentIn1Class(stL, id5, classname5, check5, st5, count52);
								}
								else
								{
									break;
								}
							}
							if (choice5 != 0)
							{
								RemoveStudentFrom1Class(stL, id5, classname5);
								cout << "The class at the moment: " << endl;
								DisPlayClass(stL);
								cout << "Do you want to save what you have done to this class's file?" << endl;
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
									fsclassname5 = classname5 + "/" + classname5 + ".dat";
									ExportFromProgram2(stL, fsclassname5);
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
		case 6:
		{
			vector<student>stLA;
			student st6;
			vector<student>stLB;
			stLA.clear();
			stLB.clear();
			string clsAname, clsBname;
			string clsAnametempl, clsBnametempl;
			int choice6 = -1, choice62;
			int id6, check6 = 0, count6 = 1, count62 = 0, No6 = 0;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			cin >> choice62;
			while (cin.fail() || (choice62 != 1 && choice62 != 2 && choice62 != 0))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "Invalid choice." << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				cin >> choice62;
			}
			if (choice62 == 1)
			{
				cout << "Input first class (class you want to bring the student out): ";
				cin.ignore(1);
				getline(cin, clsAname);
				clsAnametempl = clsAname + "/" + clsAname + ".dat";
				ImportToProgram2(stLA, clsAnametempl);
				while (stLA.size() == 0)
				{
					cout << "There nothing to change here." << endl;
					cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
					cin >> choice6;
					while (cin.fail() || (choice6 != 0 && choice6 != 1))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid choice." << endl;
						cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
						cin >> choice6;
					}
					if (choice6 == 0)
					{
						break;
					}
					else
					{
						cout << "Input first class (class you want to bring the student out): ";
						cin.ignore(1);
						getline(cin, clsAname);
						clsAnametempl = clsAname + "/" + clsAname + ".dat";
						ImportToProgram2(stLA, clsAnametempl);
					}
				}
				if (choice6 != 0)
				{
					cout << "Class " << clsAname << ":" << endl;
					DisPlayClass(stLA);
					cout << "Are you sure you want to change a student in this class?" << endl;
					cout << "Enter 1 to continue pr 0 to exit: ";
					cin >> choice6;
					while (cin.fail() || (choice6 != 1 && choice6 != 0))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to continue or 0 to exit: ";
						cin >> choice6;
					}
				}
				if (choice6 != 0)
				{
					cout << "Input the ID of the student you want to change his/her class: ";
					cin >> id6;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please input the ID of the student you want to change his/her class: ";
						cin >> id6;
					}
					FindStudentIn1Class(stLA, id6, clsAname, check6, st6, count62);
					while (check6 == 0)
					{
						cout << "There is no student has the ID " << id6 << " in this class." << endl;
						cout << "Do you want to input the ID of the student you want to change his/her class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin >> choice6;
						while (cin.fail() || (choice6 != 1 && choice6 != 0))
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input ID again or 0 to exit: ";
							cin >> choice6;
						}
						if (choice6 == 1)
						{
							cout << "Input the id of the student you want to change his/her class: ";
							cin >> id6;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Please input the ID of the student you want to change his/her class: ";
								cin >> id6;
							}
							FindStudentIn1Class(stL, id6, clsAname, check6, st6, count62);
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
				if (choice62 == 2)
				{
					cout << "Input the ID of the student: ";
					cin >> id6;
					while (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "Please input the ID of the student you want to change his/her class: ";
						cin >> id6;
					}
					FindStudentInAllClass(stLA, id6, check6, st6, clsAname, count6);
					while (check6 == 0)
					{
						cout << "The student with the ID " << id6 << " does not exists." << endl;
						cout << "You can enter 1 to input the student ID again or enter 0 to exit: ";
						cin >> choice6;
						while (cin.fail() || (choice6 != 1 && choice6 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the student ID again or enter 0 to exit: ";
							cin >> choice6;
						}
						if (choice6 == 0)
						{
							break;
						}
						else
						{
							cout << "Input the ID of the student: ";
							cin >> id6;
							while (cin.fail())
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Please input the ID of the student you want to change his/her class: ";
								cin >> id6;
							}
							FindStudentInAllClass(stLA, id6, check6, st6, clsAname, count6);
						}
					}
					if (choice6 == 0)
					{
						break;
					}
					if (check6 != 0 && count6 > 1)
					{
						stLA.clear();
						cout << "Because there are more than one class that have the student with the ID " << id6 << "." << endl;
						cout << "So, please input the name of the class which you want this student to move out: ";
						cin.ignore(1);
						getline(cin, clsAname);
						clsAnametempl = clsAname + "/" + clsAname + ".dat";
						ImportToProgram2(stLA, clsAnametempl);
						while (stLA.size() == 0)
						{
							cout << "There nothing to change here." << endl;
							cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
							cin >> choice6;
							while (cin.fail() || (choice6 != 0 && choice6 != 1))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << "Invalid choice." << endl;
								cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
								cin >> choice6;
							}
							if (choice6 == 0)
							{
								check6 = 0;
								break;
							}
							else
							{
								cout << "Input first class (class you want to bring the student out): ";
								cin.ignore(1);
								getline(cin, clsAname);
								clsAnametempl = clsAname + "/" + clsAname + ".dat";
								ImportToProgram2(stLA, clsAnametempl);
							}
						}
						if (choice6 != 0)
						{
							DisPlayClass(stLA);
							FindStudentIn1Class(stLA, id6, clsAname, check6, st6, count62);
							while (check6 == 0)
							{
								stLA.clear();
								cout << "Do you want to input the class you want this student to move out (first class) again?" << endl;
								cout << "Enter 1 to input again or 0 to exit: ";
								cin >> choice6;
								while (cin.fail() || (choice6 != 1 && choice6 != 0))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << "Invalid choice." << endl;
									cout << "Please enter 1 to input again or 0 to exit: ";
									cin >> choice6;
								}
								if (choice6 == 1)
								{
									cout << "Input the name of the first class: ";
									cin.ignore(1);
									getline(cin, clsAname);
									clsAnametempl = clsAname + "/" + clsAname + ".dat";
									ImportToProgram2(stLA, clsAnametempl);
									DisPlayClass(stLA);
									FindStudentIn1Class(stLA, id6, clsAname, check6, st6, count62);
								}
								else
								{
									break;
								}
							}
						}
					}
					if (check6 != 0 && count6 == 1)
					{
						FindStudentIn1Class(stLA, id6, clsAname, check6, st6, count62);
					}
				}
				else
				{
					cout << "Please use the 7th function to see which class is the student you want to change class staying in. " << endl;
					break;
				}
			}
			if (check6 != 0)
			{
				int check63 = 0;
				if (count6 >= 1 && count62 == 1)
				{
					No6 = st6.No;
				}
				if (count62 > 1)
				{
					cout << "Because there are more than one student that have the ID " << id6 << "." << endl;
					cout << "Please input the No of the student you want to change: ";
					cin >> No6;
					int n6 = stLA.size();
					while (cin.fail() || (No6 < 1 || No6 > n6))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "The No of the student must be bigger than 0 and smaller than " << n6 << "." << endl;
						cout << "Please input the No of the student you want to change: ";
						cin >> No6;
					}
					for (int i = 0; i < n6; i++)
					{
						if (stLA[i].id == id6 && stLA[i].No == No6)
						{
							if (stLA[i].No == No6)
							{
								check63 = 1;
								break;
							}
						}
					}
					while (check63 == 0)
					{
						cout << "There is no student has No " << No6 << " and ID " << id6 << "." << endl;
						cout << "Please enter 1 to input the No again or 0 to exit: ";
						cin >> choice6;
						while (cin.fail() || (choice6 != 1 && choice6 != 0))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the No again or 0 to exit: ";
							cin >> choice6;
						}
						if (choice6 == 1)
						{
							cout << "Inout No: ";
							cin >> No6;
							while (cin.fail() || (No6 < 1 || No6 > n6))
							{
								cin.clear();
								cin.ignore(1024, '\n');
								cout << endl << "The No of the student must be bigger than 0 and smaller than " << n6 << "." << endl;
								cout << "Please input the No of the student you want to change: ";
								cin >> No6;
							}
							for (int i = 0; i < n6; i++)
							{
								if (stLA[i].id == id6 && stLA[i].No == No6)
								{
									if (stLA[i].No == No6)
									{
										check63 = 1;
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
				if (choice6 != 0)
				{
					choice6 = 2;
					while (choice6 == 2)
					{
						stLB.clear();
						cout << "Input second class (class to want to put the student into): ";
						cin.ignore(1);
						getline(cin, clsBname);
						clsBnametempl = clsBname + "/" + clsBname + ".dat";
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
						cin >> choice6;
						while (cin.fail() || (choice6 != 1 && choice6 != 0 && choice6 != 2))
						{
							cin.clear();
							cin.ignore(1024, '\n');
							cout << endl << "Invalid choice." << endl;
							cout << "Please enter 1 to continue or 2 to input the name of the second class again or 0 to exit: ";
							cin >> choice6;
						}
						if (choice6 == 1)
						{
							int check62 = 0;
							ChangeStudentFromClassAToClassB(stLA, stLB, No6, check62, id6);
							if (check62 == 1)
							{
								cout << endl << "Error: This student is already in class " << clsBname << "." << endl;
							}
							else
							{
								cout << "Class " << clsAname << " at the moment:" << endl;
								DisPlayClass(stLA);
								cout << "Class " << clsBname << " at the moment:" << endl;
								DisPlayClass(stLB);
								int choice6s;
								cout << "Do you want to save what you have done to class" << clsAname << "'s file and class" << clsBname << "'s file?" << endl;
								cout << "Enter 1 to save or 0 to exit: ";
								cin >> choice6s;
								while (cin.fail() || (choice6s != 1 && choice6s != 0))
								{
									cin.clear();
									cin.ignore(1024, '\n');
									cout << "Invalid choice." << endl;
									cout << "Please enter 1 to save or 0 to exit: ";
									cin >> choice6s;
								}
								if (choice6s == 1)
								{
									string clsAnametemps = clsAname + "/" + clsAname + ".dat";
									ExportFromProgram2(stLA, clsAnametemps);
									string clsBnametemps = clsBname + "/" + clsBname + ".dat";
									ExportFromProgram2(stLB, clsBnametemps);
								}
							}
						}
					}
				}
			}
			break;
		}
		case 7:
		{
			stL.clear();
			DisPlayAllClass(stL);
			break;
		}
		case 8:
		{
			stL.clear();
			string classname8;
			int choice8;
			cout << "Enter the class you want to view: ";
			getline(cin, classname8);
			string fclassname8l = classname8 + "/" + classname8 + ".dat";
			ImportToProgram2(stL, fclassname8l);
			while (stL.size() == 0)
			{
				cout << "Do you want to enter the name of the class you want view again?" << endl;
				cout << "Enter 1 to input the name of the class again." << endl;
				cout << "Enter 0 to exit." << endl;
				cout << "Your choice: ";
				cin >> choice8;
				while (cin.fail() || (choice8 != 1 && choice8 != 0))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Invalid choice." << endl;
					cout << "Enter 1 to input the name of the class again." << endl;
					cout << "Enter 0 to exit." << endl;
					cout << "Your choice: ";
					cin >> choice8;
				}
				if (choice8 == 1)
				{
					cout << "Enter the class you want to view: ";
					cin.ignore(1);
					getline(cin, classname8);
					fclassname8l = classname8 + "/" + classname8 + ".dat";
					ImportToProgram2(stL, fclassname8l);
				}
				else
				{
					break;
				}
			}
			if (choice8 == 1)
			{
				cout << "The list of students in your class:" << endl;
				DisPlayClass(stL);
			}
			break;
		}
		case 9:
		{
			stL.clear();
			ofstream fsave;
			string flclassname9, classname9;
			int choice9 = -1;
			cout << "Input name of the class you want to export its data: ";
			cin.ignore(1);
			getline(cin, classname9);
			flclassname9 = classname9 + "/" + classname9 + ".dat";
			ImportToProgram2(stL, flclassname9);
			while (stL.size() == 0)
			{
				cout << "There nothing to export here." << endl;
				cout << "Enter 1 if you want to input name of the class you want to import its data." << endl;
				cout << "Enter 0 to exit." << endl;
				cout << "Your choice: ";
				cin >> choice9;
				while (cin.fail() || (choice9 != 1 && choice9 != 0))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 if you want to input name of the class you want to import its data." << endl;
					cout << "Or please enter 0 to exit." << endl;
					cout << "Your choice: ";
					cin >> choice9;
				}
				if (choice9 == 1)
				{
					cout << "Input name of the class you want to import its data: ";
					cin.ignore(1);
					getline(cin, classname9);
					flclassname9 = classname9 + "/" + classname9 + ".dat";
					ImportToProgram2(stL, flclassname9);
				}
				else
				{
					break;
				}
			}
			if (choice9 != 0)
			{
				SortClassInAscendingOrderByID(stL);
				DisPlayClass(stL);
				string fsclassname9 = classname9 + "/" + classname9 + ".csv";
				ExportFromProgram(stL, fsclassname9);
			}
			break;
		}
		}
	}
	return;
}