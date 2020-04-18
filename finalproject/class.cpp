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
	flname.push_back('.');
	flname.push_back('c');
	flname.push_back('s');
	flname.push_back('v');
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
	//fsname.push_back('.');
	//fsname.push_back('c');
	//fsname.push_back('s');
	//fsname.push_back('v');
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