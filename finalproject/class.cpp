#include"class.h"

int maxdayinmonth(int month, int year)
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
		if (year == 4 || year == 6 || year == 9 || year == 11)
		{
			maxday = 30;
		}
	}
	return maxday;
}

void addonestudent(vector<student>& stL)
{
	student nst;
	int check = 0;
	cout << "Please input the information of the new student" << endl;
	cout << "ID           : ";
	cin >> nst.id;
	if (stL.size() > 0)
	{
		int size = stL.size();
		for (int i = 0; i < size; i++)
		{
			if (nst.id == stL[i].id)
			{
				cout << "This student is already in this class." << endl;
				cout << "This is his/her information: " << endl;
				display1student(stL[i]);
				check = 1;
			}
		}
		if (check == 1)
		{
			return;
		}
		cout << "Please input others information of the new student:" << endl;
	}
	cout << "Lastname     : "; cin.ignore(1); getline(cin, nst.Lastname);
	cout << "Firstname    : "; getline(cin, nst.Firstname);
	cout << "Gender       : "; nst.gender = getchar();
	cout << "Date of birth: " << endl;
	cout << "Input year: ";
	cin >> nst.DoB.year;
	while (nst.DoB.year < 1900)
	{
		cout << "Invalid year." << endl;
		cout << "Enter the year again (Note: The year shouble be from 1900): ";
		cin >> nst.DoB.year;
	}
	cout << "Input month: ";
	cin >> nst.DoB.month;
	while (nst.DoB.month <= 0 || nst.DoB.month > 12)
	{
		cout << "Invalid month." << endl;
		cout << "Enter the month again (Note: The month shoul be from 1 to 12): ";
		cin >> nst.DoB.month;
	}
	cout << "Input day: ";
	cin >> nst.DoB.day;
	while (nst.DoB.day <= 0 || nst.DoB.day > maxdayinmonth(nst.DoB.month, nst.DoB.year))
	{
		cout << "Invalid day." << endl;
		cout << "Enter the day again (Note: The day shoul be from 1 to " << maxdayinmonth(nst.DoB.month, nst.DoB.year) << "): ";
		cin >> nst.DoB.day;
	}
	nst.No = stL.size() + 1;
	stL.push_back(nst);
}

void createnewclass(vector<student>& stL, int& n)
{
	for (int i = 0; i < n; i++)
	{
		addonestudent(stL);
	}
}

void loadfile(ifstream& fload, vector<student>& stL)
{
	string temp;
	string line;
	string temp2;
	student st;
	int count = 0;
	while (!fload.eof())
	{
		if (count < 1)
		{
			getline(fload, line);
			count++;
		}
		getline(fload, temp, ',');
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
		st.DoB.day = stoi(temp);
		getline(fload, temp, '/');
		st.DoB.month = stoi(temp);
		getline(fload, temp);
		st.DoB.year = stoi(temp);
		stL.push_back(st);
	}
}

void importtoprogram(vector<student>&stL, string flname)
{
	ifstream fload;
	int choice = -1;
	flname += ".csv";
	fload.open(flname);
	while (!fload.is_open())
	{
		cout << "The class does not exist." << endl;
		cout << "You can enter 0 to exit or press any key to continue: ";
		cin >> (choice);
		if (choice == 0)
		{
			break;
		}
		else
		{
			cin.ignore(1);
			cout << "Input name of the file you want to load: ";
			getline(cin, flname);
			flname.push_back('.');
			flname.push_back('c');
			flname.push_back('s');
			flname.push_back('v');
			fload.open(flname);
		}
	}
	if (choice != 0)
	{
		cout << "The information you need: " << endl;
		loadfile(fload, stL);
		fload.close();
	}
}

void display1student(student st)
{
	int distance = st.Lastname.size() + 4;
	int distance2 = (21 - (st.Lastname.size() - 8)) + st.Firstname.size();
	int distance3 = 8 - st.Firstname.size() + 11;
	cout << setw(5) << st.No << setw(12) << st.id << setw(distance) << st.Lastname << setw(distance2) << st.Firstname 
		<< setw(distance3) << st.gender << setw(15);
	if (st.DoB.day < 10)
	{
		cout << "0" << st.DoB.day;
	}
	else
	{
		cout << st.DoB.day;
	}
	cout << "/";
	if (st.DoB.month < 10)
	{
		cout << "0" << st.DoB.month; 
	}
	else
	{
		cout << st.DoB.month;
	}
	cout << "/" << st.DoB.year << endl;
}

void displayclass(vector<student> stL)
{
	int n = stL.size();
	cout << setw(5) << "No" << setw(6) << "ID" << setw(18) << "Lastname" << setw(30) << "Firstname" << setw(15) << "Gender" 
		<< setw(21) << "Date of birth" << endl;
	for (int i = 0; i < n; i++)
	{
		display1student(stL[i]);
	}
	cout << endl;
}

void displayallclassincourse(vector<student>stL)
{
	ifstream fload;
	string classname;
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (!fload.eof())
		{
			fload >> classname;
			cout << "Class " << classname << ":" << endl;
			importtoprogram(stL, classname);
			displayclass(stL);
			stL.clear();
		}
		fload.close();
	}
}

void editinganexistingstudent(student &st)
{
	int choice;
	cout << "What do you want to edit from this student?" << endl;
	cout << "(0).Exit" << endl;
	cout << "(1).ID." << endl;
	cout << "(2).Lastname and Firstname" << endl;
	cout << "(3).Gender." << endl;
	cout << "(4).Date of birth." << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice < 0 || choice>5)
	{
		cout << "Invalid choice." << endl;
		cout << "Enter your choice again: ";
		cin >> choice;
	}
	cin.ignore(1);
	switch (choice)
	{
	case 0:
	{
		break;
	}
	case 1:
	{
		cout << "Input new ID: ";
		cin >> st.id;
		break;
	}
	case 2:
	{
		cout << "Input new name (Lastname and Firstname): ";
		getline(cin, st.Lastname);
		getline(cin, st.Firstname);
		break;
	}
	case 3:
	{
		cout << "Input new gender: ";
		st.gender = getchar();
		break;
	}
	case 4:
	{
		cout << "Input new Date of birth: " << endl;
		cout << "Input year: ";
		cin >> st.DoB.year;
		while (st.DoB.year < 1900)
		{
			cout << "Invalid year." << endl;
			cout << "Enter the year again (Note: The year shouble be from 1900): ";
			cin >> st.DoB.year;
		}
		cout << "Input month: ";
		cin >> st.DoB.month;
		while (st.DoB.month <= 0 || st.DoB.month > 12)
		{
			cout << "Invalid month." << endl;
			cout << "Enter the month again (Note: The month shoul be from 1 to 12): ";
			cin >> st.DoB.month;
		}
		cout << "Input day: ";
		cin >> st.DoB.day;
		while (st.DoB.day <= 0 || st.DoB.day > maxdayinmonth(st.DoB.month, st.DoB.year))
		{
			cout << "Invalid day." << endl;
			cout << "Enter the day again (Note: The day shoul be from 1 to " << maxdayinmonth(st.DoB.month, st.DoB.year) << "): ";
			cin >> st.DoB.day;
		}
		break;
	}
	}
	cout << "The student information after edited:" << endl;
}

void updateeditedstudentinallhisorherclasses(vector<student>stL, int id, student st)
{
	ifstream fload;
	vector<student>Listtemp;
	string classname;
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (!fload.eof())
		{
			fload >> classname;
			cout << "Class " << classname << ":" << endl;
			importtoprogram(Listtemp, classname);
			stL = Listtemp;
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (id == stL[i].id)
				{
					stL[i] = st;
					cout << "The class " << classname << " after edited the student has the ID " << id << ":" << endl;
					displayclass(stL);
					break;
				}
			}
			Listtemp.clear();
		}
		fload.close();
	}
}

void removestudentfromclass(vector<student>& stL, int id, string classname)
{
	int n = stL.size();
	for (int i = 0; i < n; i++)
	{
		if (id == stL[i].id)
		{
			stL.erase(stL.begin() + i);
			stL.shrink_to_fit();
			n = stL.size();
			break;
		}
	}
}

void removestudentfromallclass(vector<student>stL, int id)
{
	ifstream fload;
	string classname;
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (!fload.eof())
		{
			fload >> classname;
			cout << "Class " << classname << ":" << endl;
			importtoprogram(stL, classname);
			removestudentfromclass(stL, id, classname);
			cout << "The class " << classname << " after deleted the student has ID " << id << ":" << endl;
			displayclass(stL);
			stL.clear();
		}
		fload.close();
	}
}

void changestudentfromclassAtoclassB(vector<student>& stLA, vector<student>& stLB, int id)
{
	int nA = stLA.size();
	for (int i = 0; i < nA; i++)
	{
		if (stLA[i].id == id)
		{
			stLA[i].No = stLB.size() + 1;
			stLB.push_back(stLA[i]);
			stLA.erase(stLA.begin() + i);

			break;
		}
	}
}

void findstudentincourse(vector<student> stL, int id, int& check, student& st)
{
	ifstream fload;
	check = 0;
	string classname;
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Load successed." << endl;
		while (!fload.eof())
		{
			fload >> classname;
			cout << "Class" << classname << ":" << endl;
			importtoprogram(stL, classname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (id == stL[i].id)
				{
					check = 1;
					st = stL[i];
					display1student(stL[i]);
					cout << endl;
					break;
				}
			}
			stL.clear();
		}
		fload.close();
		if (check == 0)
		{
			cout << "There is no student has the ID " << id << "in this cousrse" << endl;
		}
	}
}

void exporttofile(ofstream& fsave, vector<student> stL)
{
	int size = stL.size();
	fsave << "No," << "ID," << "Lastname," << "Firstname," << "Gender," << "Date of birth" << endl;
	for (int i = 0; i < size; i++)
	{
		fsave << stL[i].No << "," << stL[i].id << "," << stL[i].Lastname << "," << stL[i].Firstname << "," << stL[i].gender << ","
			<< stL[i].DoB.day << "/" << stL[i].DoB.month << "/" << stL[i].DoB.year << endl;
	}
}

void exporrfromprogram(vector<student>stL)
{
	string fsname = { "save.csv" };
	ofstream fsave;
	int choice = -1;
	fsname += ".csv";
	fsave.open(fsname);
	if (!fsave.is_open())
	{
		cout << "Can not create file." << endl;
	}
	else
	{
		cout << "Save successed." << endl;
		exporttofile(fsave, stL);
		fsave.close();
	}
}


void manageclassfunction()
{
	vector<student> stL;
	int choice = -1, choice1 = -1;
	cout << "========================================CLASS MANAGE PROGRAM===================================================" << endl << endl;
	cout << "What do you want to do: ";
	while (choice1 != 0)
	{
		cout << endl;
		cout << "== == == == == == == == ==" << endl;
		cout << "*--------MAIN MENU-------*" << endl;
		cout << "== == == == == == == == ==" << endl;
		cout << "................................................................" << endl;
		cout << ":Enter 0 to exit the program.                                  :" << endl;
		cout << ":Enter 1 to input new class.                                   :" << endl;
		cout << ":Enter 2 to load existing class.                               :" << endl;
		cout << ":Enter 3 to add new student.                                   :" << endl;
		cout << ":Enter 4 to edit an existing student.                          :" << endl;
		cout << ":Enter 5 to remove a student.                                  :" << endl;
		cout << ":Enter 6 to change student from class A to class B.            :" << endl;
		cout << ":Enter 7 to view list of classes.                              :" << endl;
		cout << ":Enter 8 to view list of students in a class.                  :" << endl;
		cout << "................................................................" << endl;
		cout << "Enter what you want to do: ";
		cin >> choice1;
		while (choice1 != 0 && choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4 && choice1 != 5 && choice1 != 6
			&& choice1 != 7 && choice1 != 8)
		{
			cout << "Invalid choice." << endl;
			cout << "Please enter your choice again: ";
			cin >> choice1;
		}
		switch (choice1)
		{
		case 0:
		{
			cout << "=================================Thanks for using our program. Have a nice day!=========================================";
			break;
		}
		case 1:
		{
			int n = -1;
			cout << "Please input the number of the student in the class: ";
			cin >> n;
			while (n < 0)
			{
				cout << "The number of the student in the class can't be a negative number." << endl;
				cout << "Please input the number of the student in the class again (or you can enter 0 to exit): ";
				cin >> n;
			}
			if (n > 0)
			{
				createnewclass(stL, n);
				displayclass(stL);
				break;
			}
			else
			{
				break;
			}
		}
		case 2:
		{
			ifstream fload;
			string flname;
			int choice3 = -1;
			cin.ignore(1);
			cout << "Input name of the file you want to load: ";
			getline(cin, flname);
			importtoprogram(stL, flname);
			displayclass(stL);
			break;
		}
		case 3:
		{
			int check3 = 0;
			addonestudent(stL);
			cout << "Addition is updated:" << endl;
			displayclass(stL);
			break;
		}
		case 4:
		{
			int check4 = 0, id4;
			student st4;
			cout << "Input the id of the student you want to edit: ";
			cin >> id4;
			findstudentincourse(stL, id4, check4, st4);
			if (check4 != 0)
			{
				editinganexistingstudent(st4);
				updateeditedstudentinallhisorherclasses(stL, id4, st4);
			}
			break;
		}
		case 5:
		{
			int check5 = 0, id5;
			student st5;
			cout << "Input the id of the student you want to remove: ";
			cin >> id5;
			findstudentincourse(stL, id5, check5, st5);
			if (check5 != 0)
			{
				int choice5 = -1;
				cout << "Enter 1 to delete the student from all of his/her class." << endl;
				cout << "Enter 2 to choose the class you want to delete this student." << endl;
				cout << "Enter 0 to exit." << endl;
				cout << "Enter your choice: "; cin >> choice5;
				while (choice5 != 1 && choice5 != 2 && choice5 != 0)
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter your choice again: "; cin >> choice5;
				}
				if (choice5 != 0)
				{
					if (choice5 == 1)
					{
						removestudentfromallclass(stL, id5);
					}
					else
					{
						string classname5;
						cin.ignore(1);
						getline(cin, classname5);
						importtoprogram(stL, classname5);
						cout << "The class " << classname5 << " after delete the student has ID " << id5 << ":" << endl;
						removestudentfromclass(stL, id5, classname5);
						displayclass(stL);
					}
				}
			}
			break;
		}
		case 6:
		{
			vector<student>stLA;
			vector<student>stLB;
			string clsAname, clsBname;
			int choice6 = -1;
			cout << "Input first class (class you want to bring the student out): ";
			cin.ignore(1);
			getline(cin, clsAname);
			importtoprogram(stLA, clsAname);
			while (stLA.size() == 0)
			{
				cout << "There nothing to change here." << endl;
				cout << "Please enter 0 to exit or press 1 to input the name of first class again: ";
				cin >> choice6;
				if (choice6 == 0)
				{
					break;
				}
				else
				{
					cout << "Input first class (class you want to bring the student out): ";
					cin.ignore(1);
					getline(cin, clsAname);
					importtoprogram(stLA, clsAname);
				}
			}
			if (stLA.size() != 0 && choice6 != 0)
			{
				displayclass(stLA);
				int nA = stLA.size();
				int id6, check6 = 0;
				cout << "Input the id of the student you want to change his/her class: "; cin >> id6;
				for (int i = 0; i < nA; i++)
				{
					if (id6 == stLA[i].id)
					{
						check6 = 1;
						break;
					}
				}
				while (check6 == 0)
				{
					cout << "There is no student has this ID." << endl;
					cout << "Please input the ID of the student you want to change his/her class again or inputr 0 to exit: "; cin >> id6;
					if (id6 == 0)
					{
						break;
					}
					else
					{
						for (int i = 0; i < nA; i++)
						{
							if (id6 == stLA[i].id)
							{
								check6 = 1;
								break;
							}
						}
					}
				}
				if (check6 != 0)
				{
					cout << "Input second class (class to want to put the student into): ";
					cin.ignore(1);
					getline(cin, clsBname);
					importtoprogram(stLB, clsBname);
					displayclass(stLB);
					changestudentfromclassAtoclassB(stLA, stLB, id6);
					displayclass(stLA);
					displayclass(stLB);
				}
			}
			break;
		}
		case 7:
		{
			displayallclassincourse(stL);
			break;
		}
		case 8:
		{
			vector<student>stL8;
			string classname8;
			cout << "Enter the class you want to view: "; cin.ignore(1); getline(cin, classname8);
			importtoprogram(stL8, classname8);
			cout << "The list of students in your class:" << endl;
			displayclass(stL8);
			break;
		}
		}
	}
}