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
		if (month == 4 || month == 6 || month == 9 || month == 11)
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
				cout << "Error: This student is already in this class." << endl;
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

void loadfromcsvfile(ifstream& fload, vector<student>& stL)
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
	fload.open(flname);
	if (!fload.is_open())
	{
		cout << "Can not find any data of this class." << endl;
	}
	else
	{
		loadfromcsvfile(fload, stL);
		fload.close();
	}
}

void display1student(student st)
{
	int distance = st.Lastname.size() + 4;
	int distance2 = (21 - (st.Lastname.size() - 8)) + st.Firstname.size();
	int distance3 = 8 - st.Firstname.size() + 11;
	cout << setw(5) << st.No << setw(12) << st.id << setw(distance) << st.Lastname << setw(distance2) << st.Firstname
		<< setw(distance3) << st.gender; 
	if (st.DoB.day < 10)
	{
		cout << setw(14) << "0" << st.DoB.day;
	}
	else
	{
		cout << setw(15) << st.DoB.day;
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

void display1studentline(student st)
{
	cout << "No: " << st.No << endl;
	cout << "ID: " << st.id << endl;
	cout << "Lastname: " << st.Lastname << endl;
	cout << "Firstname: " << st.Firstname << endl;
	cout << "Date of birth: ";
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

void displayclassline(vector<student> stL)
{
	int n = stL.size();
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		display1studentline(stL[i]);
	}
	cout << endl;
}

void displayallclassincourse(vector<student>stL)
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
			fclassname = classname + ".dat";
			cout << "Class " << classname << ":" << endl;
			importtoprogram2(stL, fclassname);
			displayclass(stL);
			stL.clear();
		}
		fload.close();
	}
}

void displayallclassincourseline(vector<student>stL)
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
			fclassname = classname + ".csv";
			cout << "Class " << classname << ":" << endl;
			importtoprogram(stL, fclassname);
			displayclassline(stL);
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
	while (choice < 0 || choice > 4)
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
		cin.ignore(1);
		break;
	}
	case 2:
	{
		cout << "Input new name (Lastname and Firstname): " << endl;
		cout << "Lastname: ";
		getline(cin, st.Lastname);
		cout << "Firstname: ";
		getline(cin, st.Firstname);
		break;
	}
	case 3:
	{
		cout << "Input new gender: ";
		st.gender = getchar();
		cin.ignore(1);
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
		cin.ignore(1);
		break;
	}
	}
	cout << "The student information after edited:" << endl;
}

void updateeditedstudentinallhisorherclasses(vector<student>& stL, int& id, student& st)
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
		while (fload >> classname)
		{
			string flname = classname + ".dat";
			importtoprogram2(Listtemp, flname);
			stL = Listtemp;
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (id == stL[i].id)
				{
					cout << "Class " << classname << ":" << endl;
					stL[i] = st;
					cout << "The class " << classname << " after edited the student has the ID " << id << ":" << endl;
					displayclass(stL);
					fload.close();
					return;
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
			for (int j = i + 1; j < n; j++)
			{
				stL[j].No = stL[j].No - 1;
			}
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
		while (fload >> classname)
		{
			cout << "Class " << classname << ":" << endl;
			string flname = classname + ".dat";
			importtoprogram(stL, flname);
			removestudentfromclass(stL, id, classname);
			cout << "The class " << classname << " after deleted the student has ID " << id << ":" << endl;
			displayclass(stL);
			stL.clear();
		}
		fload.close();
	}
}

void changestudentfromclassAtoclassB(vector<student>& stLA, vector<student>& stLB, int id, int& check)
{
	int nA = stLA.size();
	int nB = stLB.size();
	check = 0;
	for (int i = 0; i < nA; i++)
	{
		if (stLA[i].id == id)
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
			}
			break;
		}
	}
}

void findstudentinexistingclasses(vector<student>& stL, int id, int& check, student& st, string& classname)
{
	ifstream fload;
	string flname;
	check = 0;
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
			flname = classname + ".dat";
			importtoprogram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (id == stL[i].id)
				{
					cout << "Here is his/her class: class " << classname << endl;
					check = 1;
					st = stL[i];
					cout << "And here is his/her information:" << endl;
					display1student(stL[i]);
					cout << endl;
					fload.close();
					return;
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

void exporrfromprogram(vector<student>stL, string fsname)
{
	fsname = { "save.csv" };
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

void findstudentin1class(vector<student> stL, int id, string classname, int& check, student& st)
{
	check = 0;
	int n = stL.size();
	for (int i = 0; i < n; i++)
	{
		if (stL[i].id == id)
		{
			check = 1;
			st = stL[i];
			cout << "The student has the ID " << id << " is:" << endl;
			display1student(st);
			break;
		}
	}
	if (check == 0)
	{
		cout << "There is no student has the given id in class " << classname << "." << endl;
	}
}

void loadfromdatfile(ifstream& fload, vector<student>& stL)
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
		st.DoB.day = stoi(temp);
		getline(fload, temp, ' ');
		st.DoB.month = stoi(temp);
		getline(fload, temp);
		st.DoB.year = stoi(temp);
		stL.push_back(st);
		getline(fload, line);
	}
}

void importtoprogram2(vector<student>& stL, string flname)
{
	ifstream fload;
	fload.open(flname);
	if (!fload.is_open())
	{
		cout << "Can not find any data of this class." << endl;
	}
	else
	{
		loadfromdatfile(fload, stL);
		fload.close();
	}
}

void savetodatfile(ofstream& fsave, vector<student> stL)
{
	int n = stL.size();
	for (int i = 0; i < n; i++)
	{
		fsave << stL[i].No << endl;
		fsave << stL[i].id << endl;
		fsave << stL[i].Lastname << endl;
		fsave << stL[i].Firstname << endl;
		fsave << stL[i].gender << endl;
		fsave << stL[i].DoB.day << " " << stL[i].DoB.month << " " << stL[i].DoB.year;
		if (i < n - 1)
		{
			fsave << endl << endl;
		}
	}
}

void exportfromprogram2(vector<student> stL, string fsname)
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
		savetodatfile(fsave, stL);
		fsave.close();
	}
}


void manageclassfunctionold()
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
			string classname4;
			student st4;
			cout << "Input the id of the student you want to edit: ";
			cin >> id4;
			findstudentinexistingclasses(stL, id4, check4, st4, classname4);
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
			string classname5;
			student st5;
			cout << "Input the id of the student you want to remove: ";
			cin >> id5;
			findstudentinexistingclasses(stL, id5, check5, st5, classname5);
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
			string clsAnametemp = clsAname + ".csv";
			importtoprogram(stLA, clsAnametemp);
			while (stLA.size() == 0)
			{
				cout << "There nothing to change here." << endl;
				cout << "Please enter 0 to exit or press 1 to input the name of first class again: ";
				cin >> choice6;
				while (choice6 != 0 && choice6 != 1)
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 0 to exit or press 1 to input the name of first class again: ";
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
					string clsAnametemp = clsAname + ".csv";
					importtoprogram(stLA, clsAnametemp);
				}
			}
			displayclass(stLA);
			cout << "Are you sure you want to change any students in this class?" << endl;
			cout << "Enter 1 to continue pr 0 to exit: "; cin >> choice6;
			while (choice6 != 1 && choice6 != 0)
			{
				cout << "Invalid choice." << endl;
				cout << "Please enter 1 to continue or 0 to exit: "; cin >> choice6;
			}
			if (stLA.size() != 0 && choice6 != 0)
			{
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
					string clsBnametemp = clsBname + ".csv";
					importtoprogram(stLB, clsBnametemp);
					displayclass(stLB);
					cout << "Are you sure you want to change student into this class?" << endl;
					cout << "Enter 1 to continue or 0 to exit: "; cin >> choice6;
					while (choice6 != 1 && choice6 != 0)
					{
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to continue or 0 to exit: "; cin >> choice6;
					}
					if (choice6 != 0)
					{
						int check62 = 0;
						changestudentfromclassAtoclassB(stLA, stLB, id6, check62);
						if (check62 == 1)
						{
							cout << endl << "Error: This student is already in class " << clsBname << "." << endl;
						}
						else
						{
							cout << "Class " << clsAname << " at the moment:" << endl;
							displayclass(stLA);
							cout << "Class " << clsBname << " at the moment:" << endl;
							displayclass(stLB);
						}
					}
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


void manageclassfunctionnew()
{
	vector<student> stL;
	int choice = -1;
	string choicestr;
	cout << "========================================CLASS MANAGE PROGRAM===================================================" << endl << endl;
	cout << "What do you want to do: "; cout << endl;
	while (choice != 0)
	{
		cout << "== == == == == == == == ==" << endl;
		cout << "*--------MAIN MENU-------*" << endl;
		cout << "== == == == == == == == ==" << endl;
		cout << "......................................................................" << endl;
		cout << ":Enter 0 to exit the program.                                        :" << endl;
		cout << ":Enter 1 to input new class.                                         :" << endl;
		cout << ":Enter 2 to import your data to program (tran csv file to dat file)  :" << endl;
		cout << ":Enter 3 to add new student.                                         :" << endl;
		cout << ":Enter 4 to edit an existing student.                                :" << endl;
		cout << ":Enter 5 to remove a student.                                        :" << endl;
		cout << ":Enter 6 to change student from class A to class B.                  :" << endl;
		cout << ":Enter 7 to view list of classes.                                    :" << endl;
		cout << ":Enter 8 to view list of students in a class.                        :" << endl;
		cout << ":Enter 9 to find student in class.                                   :" << endl;
		cout << "......................................................................" << endl;
		cout << "Enter what you want to do: ";
		getline(cin, choicestr);
		while (choicestr != "0" && choicestr != "1" && choicestr != "2" && choicestr != "3" && choicestr != "4" && choicestr != "5" && choicestr != "6"
			&& choicestr != "7" && choicestr != "8")
		{
			cout << "Invalid choice." << endl;
			cout << "Please enter your choice again: ";
			getline(cin, choicestr);
		}
		choice = stoi(choicestr);
		switch (choice)
		{
		case 0:
		{
			cout << "=================================Thanks for using our program. Have a nice day!=========================================";
			break;
		}
		case 1:
		{
			stL.clear();
			string choice1s, choice1;
			int n = -1;
			cout << "Please input the number of the student in the class: ";
			cin >> n;
			while (n <= 0)
			{
				cout << "The number of the student in the class must be a positive number." << endl;
				cout << "Please enter 1 to input the number of the student in the class again or you can enter 0 to exit: ";
				cin.ignore(1);
				getline(cin, choice1);
				while (choice1 != "1" && choice1 != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to input the number of the student in the class again or you can enter 0 to exit: ";
					getline(cin, choice1);
				}
				if (choice1 == "1")
				{
					cout << "Please input the number of the student in the class: ";
					cin >> n;
				}
			}
			if (n > 0)
			{
				createnewclass(stL, n);
				displayclass(stL);
				cout << "Do you want to save this new class?" << endl;
				cout << "Enter 1 to save or 0 to exit: ";
				cin.ignore(1);
				getline(cin, choice1s);
				while (choice1s != "1" && choice1s != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to save or 0 to exit: ";
					getline(cin, choice1s);
				}
				if (choice1s == "1")
				{
					string classname1;
					cout << "Enter the name of the new class: ";
					getline(cin, classname1);
					string fsclassname1 = classname1 + ".dat";
					exportfromprogram2(stL, fsclassname1);
				};
			}
			break;
		}
		case 2:
		{
			stL.clear();
			ifstream fload;
			string flclassname2, classname2;
			string choice2 = "-1";
			cout << "Input name of the class you want to import its data: ";
			getline(cin, classname2);
			flclassname2 = classname2 + ".csv";
			importtoprogram(stL, flclassname2);
			while (stL.size() == 0)
			{
				cout << "There nothing to save." << endl;
				cout << "Enter 1 if you want to input name of the class you want to import its data." << endl;
				cout << "Enter 0 to exit." << endl;
				cout << "Your choice: ";
				getline(cin, choice2);
				while (choice2 != "1" && choice2 != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 if you want to input name of the class you want to import its data." << endl;
					cout << "Or please enter 0 to exit." << endl;
					cout << "Your choice: ";
					getline(cin, choice2);
				}
				if (choice2 == "1")
				{
					cin.ignore(1);
					cout << "Input name of the class you want to import its data: ";
					getline(cin, classname2);
					flclassname2 = classname2 + ".csv";
					importtoprogram(stL, flclassname2);
				}
				else
				{
					break;
				}
			}
			if (choice2 != "0")
			{
				displayclass(stL);
				string fsclassname2 = classname2 + ".dat";
				exportfromprogram2(stL, fsclassname2);
			}
			break;
		}
		case 3:
		{
			stL.clear();
			int check3 = 0;
			string choice3 = "-1", choice3s;
			cout << "Which class do you want to add new student?" << endl;
			cout << "Class: ";
			string classname3, flclassname3;
			getline(cin, classname3);
			flclassname3 = classname3 + ".dat";
			importtoprogram2(stL, flclassname3);
			while (stL.size() == 0)
			{
				cout << "Do you want to create new class with the name " << classname3 << "?" << endl;
				cout << "Enter 1 to continue to create new class or 0 to exit: ";
				getline(cin, choice3);
				while (choice3 != "0" && choice3 != "1")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to continue to create new class or 0 to exit: ";
					getline(cin, choice3);
				}
				if (choice3 == "1")
				{
					cout << "Which class do you want to add new student?" << endl;
					cout << "Class: ";
					getline(cin, classname3);
					flclassname3 = classname3 + ".dat";
					importtoprogram2(stL, flclassname3);
				}
				else
				{
					break;
				}
			}
			if (choice3 != "0")
			{
				displayclass(stL);
				addonestudent(stL);
				cout << endl << "Addition is updated:" << endl;
				displayclass(stL);
				cout << "Do you want to save what you have done to this class's file?" << endl;
				cout << "Enter 1 to save or 0 to exit: ";
				cin.ignore(1);
				getline(cin, choice3s);
				while (choice3s != "1" && choice3s != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to save or 0 to exit: ";
					getline(cin, choice3s);
				}
				if (choice3s == "1")
				{
					string fsclassname3 = classname3 + ".dat";
					exportfromprogram2(stL, fsclassname3);
				}
			}
			break;
		}
		case 4:
		{
			stL.clear();
			int check4 = 0, id4;
			string choice42, choice4 = "-1", choice4s;
			string classname4;
			student st4;
			cout << "Do you know the class or the ID of the student you want to edit?" << endl;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			getline(cin, choice42);
			while (choice42 != "1" && choice42 != "2" && choice42 != "0")
			{
				cout << "Invalid choice." << endl;
				cout << "Do you know the class or the ID of the student you want to edit?" << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				getline(cin, choice42);
			}
			if (choice42 == "1")
			{
				cout << "Input the name of the class you want to edit student: ";
				getline(cin, classname4);
				string flclassname4 = classname4 + ".dat";
				importtoprogram2(stL, flclassname4);
				while (stL.size() == 0)
				{
					cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
					getline(cin, choice4);
					while (choice4 != "0" && choice4 != "1")
					{
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						getline(cin, choice4);
					}
					if (choice4 == "1")
					{
						;
						cout << "Input the name of the class you want to edit student: ";
						getline(cin, classname4);
						flclassname4 = classname4 + ".dat";
						importtoprogram2(stL, flclassname4);
					}
					else
					{
						break;
					}
				}
				if (choice4 != "0")
				{
					displayclass(stL);
					cout << "Input the id of the student you want to edit in this the class " << classname4 << ": ";
					cin >> id4;
					findstudentin1class(stL, id4, classname4, check4, st4);
					while (check4 == 0)
					{
						cout << "Do you want to input the ID of the student you want to edit in this class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin.ignore(1);
						getline(cin, choice4);
						while (choice4 != "1" && choice4 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input again or 0 to exit: ";
							getline(cin, choice4);
						}
						if (choice4 == "1")
						{
							cout << "Input the id of the student you want to edit in this the class " << classname4 << ": ";
							cin >> id4;
							findstudentin1class(stL, id4, classname4, check4, st4);
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
				if (choice42 == "2")
				{
					cout << "Please input the ID of the student you need to edit so we can find he/she for you and also his/her class too: ";
					cin >> id4;
					findstudentinexistingclasses(stL, id4, check4, st4, classname4);
					while (check4 == 0)
					{
						cout << "Enter 1 to input the ID of the student you to edit again or enter 0 to exit: ";
						cin.ignore(1);
						getline(cin, choice4);
						while (choice4 != "1" && choice4 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the ID of the student you wan to edit again or enter 0 to exit: ";
							getline(cin, choice4);
						}
						if (choice4 != "0")
						{
							cout << "Input the ID of the student you wan to edit: "; cin >> id4;
							findstudentinexistingclasses(stL, id4, check4, st4, classname4);
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					cout << "You can use the function 7 to see all students in all classes and then choose function 4 again to edit the student you want to." << endl;
				}
			}
			if (check4 != 0)
			{
				cin.ignore(1);
				editinganexistingstudent(st4);
				updateeditedstudentinallhisorherclasses(stL, id4, st4);
				cout << "Do you want to save what you have done to this class's file?" << endl;
				cout << "Enter 1 to save or 0 to exit: ";
				getline(cin, choice4s);
				while (choice4s != "1" && choice4s != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to save or 0 to exit: ";
					getline(cin, choice4s);;
				}
				if (choice4s == "1")
				{
					string fsclassname4 = classname4 + ".dat";
					exportfromprogram2(stL, fsclassname4);
				}
			}
			break;
		}
		case 5:
		{
			stL.clear();
			int check5 = 0, id5;
			student st5;
			string classname5, choice5, choice52;
			cout << "Do you know the class or the ID of the student you want to remove?" << endl;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			getline(cin, choice52);
			while (choice52 != "1" && choice52 != "2" && choice52 != "0")
			{
				cout << "Invalid choice." << endl;
				cout << "Do you know the class or the ID of the student you want to remove?" << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				getline(cin, choice52);
			}
			if (choice52 == "1")
			{
				cout << "Input the name of the class you want to delete student: ";
				getline(cin, classname5);
				string flclassname5 = classname5 + ".dat";
				importtoprogram2(stL, flclassname5);
				while (stL.size() == 0)
				{
					cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
					getline(cin, choice5);
					while (choice5 != "0" && choice5 != "1")
					{
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						getline(cin, choice5);
					}
					if (choice5 == "1")
					{
						cout << "Input the name of the class you want to delete student: ";
						getline(cin, classname5);
						flclassname5 = classname5 + ".dat";
						importtoprogram2(stL, flclassname5);
					}
					else
					{
						break;
					}
				}
				if (choice5 != "0")
				{
					displayclass(stL);
					cout << "Input the id of the student you want to delete from the class " << classname5 << ": ";
					cin >> id5;
					findstudentin1class(stL, id5, classname5, check5, st5);
					while (check5 == 0)
					{
						cout << "Do you want to input the ID of the student you want to edit in this class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin.ignore(1);
						getline(cin, choice5);
						while (choice5 != "1" && choice5 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input again or 0 to exit: ";
							getline(cin, choice5);
						}
						if (choice5 == "1")
						{
							cout << "Input the id of the student you want to edit in this the class " << classname5 << ": ";
							cin >> id5;
							findstudentin1class(stL, id5, classname5, check5, st5);
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
				if (choice52 == "2")
				{
					cout << "Please input his/her ID so we can have you to find the student you want to remove and his/her class too: ";
					cin >> id5;
					findstudentinexistingclasses(stL, id5, check5, st5, classname5);
					if (check5 != 0)
					{
						displayclass(stL);
					}
					while (check5 == 0)
					{
						cout << "Enter 1 to input the ID of the student you to edit again or enter 0 to exit: ";
						cin.ignore(1);
						getline(cin, choice5);
						while (choice5 != "1" && choice5 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the ID of the student you wan to edit again or enter 0 to exit: ";
							getline(cin, choice5);
						}
						if (choice5 != "0")
						{
							cout << "Input the ID of the student you want to remove: ";
							cin >> id5;
							findstudentinexistingclasses(stL, id5, check5, st5, classname5);
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
			if (check5 != 0)
			{
				cin.ignore(1);
				cout << "Are you sure that you want to delete the student has the ID " << id5 << " from class " << classname5 << "?" << endl;
				cout << "Enter 1 to continue or 0 to exit: ";
				getline(cin, choice5);
				while (choice5 != "0" && choice5 != "1")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to continue to delete the student has the ID " << id5 << " from class " << classname5 << ": " << endl;
					getline(cin, choice5);
				}
				if (choice5 == "1")
				{
					removestudentfromclass(stL, id5, classname5);
					cout << "The class at the moment: " << endl;
					displayclass(stL);
					string choice5s;
					cout << "Do you want to save what you have done to this class's file?" << endl;
					cout << "Enter 1 to save or 0 to exit: "; getline(cin, choice5s);
					while (choice5s != "1" && choice5s != "0")
					{
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to save or 0 to exit: ";
						getline(cin, choice5s);
					}
					if (choice5s == "1")
					{
						string fsclassname5 = classname5 + ".dat";
						exportfromprogram2(stL, fsclassname5);
					}
				}
			}
			/*cout << "Input the id of the student you want to remove: ";
			cin >> id5;
			findstudentinexistingclasses(stL, id5, check5, st5);
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
						classname5 += ".csv";
						importtoprogram(stL, classname5);
						cout << "The class " << classname5 << " after delete the student has ID " << id5 << ":" << endl;
						removestudentfromclass(stL, id5, classname5);
						displayclass(stL);
					}
				}
			}*/
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
			string choice6 = "-1", choice62;
			int id6, check6 = 0;
			cout << "Do you know the class of the student that you want to change his/her class?" << endl;
			cout << "Do you know the class or the ID of the student you want to remove?" << endl;
			cout << "Enter 1 to say input his/her class." << endl;
			cout << "Enter 2 to input his / her ID." << endl;
			cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
			cout << "Your choice: ";
			getline(cin, choice62);
			while (choice62 != "1" && choice62 != "2" && choice62 != "0")
			{
				cout << "Invalid choice." << endl;
				cout << "Do you know the class or the ID of the student you want to change class?" << endl;
				cout << "Enter 1 to say input his/her class." << endl;
				cout << "Enter 2 to input his / her ID." << endl;
				cout << "Enter 0 to show that you don't have needed information about the student you want to edit." << endl;
				cout << "Your choice: ";
				getline(cin, choice62);
			}
			if (choice62 == "1")
			{
				cout << "Input first class (class you want to bring the student out): ";
				getline(cin, clsAname);
				clsAnametempl = clsAname + ".dat";
				importtoprogram2(stLA, clsAnametempl);
				while (stLA.size() == 0)
				{
					cout << "There nothing to change here." << endl;
					cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
					getline(cin, choice6);
					while (choice6 != "0" && choice6 != "1")
					{
						cout << "Invalid choice." << endl;
						cout << "Please enter 0 to exit or press 1 to input the name of first class: ";
						getline(cin, choice6);
					}
					if (choice6 == "0")
					{
						break;
					}
					else
					{
						cout << "Input first class (class you want to bring the student out): ";
						getline(cin, clsAname);
						clsAnametempl = clsAname + ".dat";
						importtoprogram2(stLA, clsAnametempl);
					}
				}
				if (choice6 != "0")
				{
					cout << "Class " << clsAname << ":" << endl;
					displayclass(stLA);
					cout << "Are you sure you want to change any students in this class?" << endl;
					cout << "Enter 1 to continue pr 0 to exit: ";
					getline(cin, choice6);
					while (choice6 != "1" && choice6 != "0")
					{
						cout << "Invalid choice." << endl;
						cout << "Please enter 1 to continue or 0 to exit: ";
						getline(cin, choice6);
					}
				}
				if (choice6 != "0")
				{
					cout << "Input the id of the student you want to change his/her class: ";
					cin >> id6;
					findstudentin1class(stLA, id6, clsAname, check6, st6);
					while (check6 == 0)
					{
						cout << "Do you want to input the ID of the student you want to edit in this class again?" << endl;
						cout << "Enter 1 to input again or 0 to exit: ";
						cin.ignore(1);
						getline(cin, choice6);
						while (choice6 != "1" && choice6 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input again or 0 to exit: ";
							getline(cin, choice6);
						}
						if (choice6 == "1")
						{
							cout << "Input the id of the student you want to edit in this the class " << clsAname << ": ";
							cin >> id6;
							findstudentin1class(stL, id6, clsAname, check6, st6);
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
				if (choice62 == "2")
				{
					cout << "Input the ID of the student: ";
					cin >> id6;
					findstudentinexistingclasses(stLA, id6, check6, st6, clsAname);
					while (check6 == 0)
					{
						cout << "You can enter 1 to input the student ID again or enter 0 to exit: ";
						cin.ignore(1);
						getline(cin, choice6);
						while (choice6 != "1" && choice6 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the student ID again or enter 0 to exit: ";
							getline(cin, choice6);
						}
						if (choice6 == "0")
						{
							break;
						}
						else
						{
							cout << "Input the ID of the student: ";
							cin >> id6;
							findstudentinexistingclasses(stLA, id6, check6, st6, clsAname);
						}
					}
					if (choice6 == "0")
					{
						break;
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
				cout << "Input second class (class to want to put the student into): ";
				cin.ignore(1);
				getline(cin, clsBname);
				clsBnametempl = clsBname + ".dat";
				importtoprogram2(stLB, clsBnametempl);
				if (stLB.size() == 0)
				{
					cout << "The class may not exist." << endl;
					cout << "So, if you move a student into this class, you may create a new class with one student." << endl;
				}
				else
				{
					displayclass(stLB);
				}
				cout << "Are you sure you want to change student into this class?" << endl;
				cout << "Enter 1 to continue or 0 to exit: ";
				getline(cin, choice6);
				while (choice6 != "1" && choice6 != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to continue or 0 to exit: ";
					getline(cin, choice6);
				}
				if (choice6 != "0")
				{
					int check62 = 0;
					changestudentfromclassAtoclassB(stLA, stLB, id6, check62);
					if (check62 == 1)
					{
						cout << endl << "Error: This student is already in class " << clsBname << "." << endl;
					}
					else
					{
						cout << "Class " << clsAname << " at the moment:" << endl;
						displayclass(stLA);
						cout << "Class " << clsBname << " at the moment:" << endl;
						displayclass(stLB);
						string choice6s;
						cout << "Do you want to save what you have done to this class's file?" << endl;
						cout << "Enter 1 to save or 0 to exit: ";
						getline(cin, choice6s);
						while (choice6s != "1" && choice6s != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to save or 0 to exit: ";
							getline(cin, choice6s);
						}
						if (choice6s == "1")
						{
							string clsAnametemps = clsAname + ".dat";
							exportfromprogram2(stLA, clsAnametemps);
							string clsBnametemps = clsBname + ".dat";
							exportfromprogram2(stLB, clsBnametemps);
						}
					}
				}
			}
			break;
		}
		case 7:
		{
			stL.clear();
			displayallclassincourse(stL);
			break;
		}
		case 8:
		{
			stL.clear();
			string classname8, choice8;
			cout << "Enter the class you want to view: ";
			getline(cin, classname8);
			string fclassname8l = classname8 + ".dat";
			importtoprogram2(stL, fclassname8l);
			if (stL.size() > 0)
			{
				cout << "The list of students in your class:" << endl;
				displayclass(stL);
			}
			while (stL.size() == 0)
			{
				cout << "Do you want to enter the name of the class you want view again?" << endl;
				cout << "Enter 1 to input the name of the class again." << endl;
				cout << "Enter 0 to exit." << endl;
				cout << "Your choice: ";
				getline(cin, choice8);
				while (choice8 != "1" && choice8 != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Enter 1 to input the name of the class again." << endl;
					cout << "Enter 0 to exit." << endl;
					cout << "Your choice: ";
					getline(cin, choice8);
				}
				if (choice8 == "1")
				{
					cout << "Enter the class you want to view: ";
					getline(cin, classname8);
				}
				else
				{
					break;
				}
			}
			break;
		}
		}
	}
}