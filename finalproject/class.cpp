#include "class.h"

int maxdayinmonth(int month, int year)
{
	int maxday = 31;
	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
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
	string classname;
	student nst;
	int check = 0, count = 0;
	vector<student>stLtemp;
	string choice = "-1";
	cout << "Please input the information of the new student" << endl;
	cout << "ID           : ";
	cin >> nst.id;
	findstudentinexistingclasses(stLtemp, nst.id, check, nst, classname, count);
	while (check == 1)
	{
		cout << "Error: The ID " << nst.id << " has already been given to another student in class " << classname << "." << endl;
		cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
		cout << "Your choice: ";
		cin.ignore(1);
		getline(cin, choice);
		while (choice != "1" && choice != "0")
		{
			cout << "Invalid choice." << endl;
			cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
			cout << "Your choice: ";
			getline(cin, choice);
		}
		if (choice == "1")
		{
			cout << "Please input the information of the new student" << endl;
			cout << "ID           : ";
			cin >> nst.id;
			findstudentinexistingclasses(stLtemp, nst.id, check, nst, classname, count);
		}
		else
		{
			return;
		}
	}
	cout << "Please input others information of the new student:" << endl;
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
	cin.ignore(1);
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
		st.No = stL.size() + 1;
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
	cout << "Gender:" << st.gender << endl;
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
			fclassname = classname + "/" + classname + ".dat";
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
			fclassname = classname + "/" + classname + ".dat";
			cout << "Class " << classname << ":" << endl;
			importtoprogram2(stL, fclassname);
			displayclassline(stL);
			stL.clear();
		}
		fload.close();
	}
}

void editinganexistingstudent(student &st)
{
	cout << endl;
	string choicestr = "-1";
	int choice;
	cout << "What do you want to edit from this student?" << endl;
	while (choicestr != "0")
	{
		cout << "(0).Exit" << endl;
		cout << "(1).ID." << endl;
		cout << "(2).Lastname and Firstname" << endl;
		cout << "(3).Gender." << endl;
		cout << "(4).Date of birth." << endl;
		cout << "Enter your choice: ";
		getline(cin, choicestr);
		choice = stoi(choicestr);
		while (choice < 0 || choice > 4)
		{
			cout << "Invalid choice." << endl;
			cout << "Enter your choice again: ";
			getline(cin, choicestr);
			choice = stoi(choicestr);
		}
		switch (choice)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			int check = 0, count = 0;
			string classname;
			vector<student>stLtemp;
			cout << "Input new ID: ";
			cin >> st.id;
			findstudentinexistingclasses(stLtemp, st.id, check, st, classname, count);
			while (check == 1)
			{
				string choice1;
				cout << "Error: The ID " << st.id << " has already been given to another student in class " << classname << "." << endl;
				cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
				cout << "Your choice: ";
				cin.ignore(1);
				getline(cin, choice1);
				while (choice1 != "1" && choice1 != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to input the ID of new student again or enter 0 to exit." << endl;
					cout << "Your choice: ";
					getline(cin, choice1);
				}
				if (choice1 == "1")
				{
					cout << "Please input the information of the new student" << endl;
					cout << "ID           : ";
					cin >> st.id;
					findstudentinexistingclasses(stLtemp, st.id, check, st, classname, count);
				}
				else
				{
					break;
				}
			}
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
		cout << endl << "Is there anythings else about this student that to want to edit?" << endl;
	}
	cout << endl << "The student information after edited:" << endl;
	display1studentline(st);
}

void updateeditstudentin1class(vector<student>& stL, int No, student st)
{
	int n = stL.size();
	string choice;
	for (int i = 0; i < n; i++)
	{
		if (stL[i].No == No)
		{
			cout << "Are you sure you want to place an update on the student:" << endl;
			display1studentline(stL[i]);
			cout << "Enter 1 to continue or 0 to exit: ";
			getline(cin, choice);
			while (choice != "1" && choice != "0")
			{
				cout << "Invalid choice." << endl;
				cout << "Please enter 1 to continue or 0 to exit.";
				getline(cin, choice);
			}
			if (choice != "0")
			{
				stL[i] = st;
			}
		}
	}
	sortclassinascendingorderbyid(stL);
	cout << "The class after updated data:" << endl;
	displayclass(stL);
}

void updateeditedstudentinallhisorherclasses(vector<student>& stL, int id, student st)
{
	ifstream fload;
	string choices, choice;
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
		getline(cin, choices);
		while (choices != "1" && choices != "0")
		{
			cout << "Invalid choice." << endl;
			cout << "Please enter 1 to save or 0 to not save anything: ";
			getline(cin, choices);
		}
		cout << endl;
		while (fload >> classname)
		{
			stL.clear();
			string flname = classname + "/" + classname + ".dat";
			importtoprogram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (stL[i].id == id)
				{
					display1studentline(stL[i]);
					cout << endl;
					cout << "Are you sure you want to place the update on this student?" << endl;
					cout << "Enter 1 to replace or 0 to exit: ";
					getline(cin, choice);
					while (choice != "0" && choice != "1")
					{
						cout << "Invalid choice." << endl;
						cout << "Enter 1 to replace or 0 to exit: ";
						getline(cin, choice);
					}
					if (choice != "0")
					{
						cout << endl << "Class " << classname << ":" << endl;
						stL[i] = st;
						sortclassinascendingorderbyid(stL);
					}
				}
			}
			cout << "The class " << classname << " after updated data:" << endl;
			displayclass(stL);
			if (choices == "1")
			{
				string fsname = flname;
				exportfromprogram2(stL, fsname);
			}
		}
		fload.close();
	}
}

void removestudentfromclass(vector<student>& stL, int id, string classname)
{
	int n = stL.size();
	string choice;
	for (int i = 0; i < n; i++)
	{
		if (id == stL[i].id)
		{
			cout << "Are you sure you want to delete this student?" << endl;
			display1studentline(stL[i]);
			cout << "Enter 1 to continue or 0 to exit: ";
			getline(cin, choice);
			while (choice != "0" && choice != "1")
			{
				cout << "Invalid choice." << endl;
				cout << "Please enter 1 to continue or 0 to exit: ";
				getline(cin, choice);
			}
			if (choice != "0")
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

void removestudentfromallclass(vector<student>stL, int id)
{
	ifstream fload;
	string classname;
	string choices, choice;
	fload.open("allclassname.txt");
	if (!fload.is_open())
	{
		cout << "Can not open file." << endl;
	}
	else
	{
		cout << "Would you like to save all update to all the classes's files?" << endl;
		cout << "Enter 1 to save (for all classes that have the student has given ID) or 0 to update but the updation won't be save: ";
		getline(cin, choices);
		while (choices != "1" && choices != "0")
		{
			cout << "Invalid choice." << endl;
			cout << "Please enter 1 to save or 0 to exit: ";
			getline(cin, choices);
		}
		while (fload >> classname)
		{
			stL.clear();
			string flname = classname + "/" + classname + ".dat";
			importtoprogram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (stL[i].id == id)
				{
					if (choice != "0")
					{
						cout << "Class " << classname << ":" << endl;
						removestudentfromclass(stL, id, classname);
						n = stL.size();
						cout << "The class " << classname << " after deleted the student has ID " << id << ":" << endl;
						displayclass(stL);
					}
				}
			}
			if (choices == "1")
			{
				string fsname = flname;
				exportfromprogram2(stL, fsname);
			}
		}
		fload.close();
	}
}

void changestudentfromclassAtoclassB(vector<student>& stLA, vector<student>& stLB, int No, int& check, int id)
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
				sortclassinascendingorderbyid(stLA);
				sortclassinascendingorderbyid(stLB);
			}
			break;
		}
	}
}

void findstudentinexistingclasses(vector<student>& stL, int id, int& check, student& st, string& classname, int& count)
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
			importtoprogram2(stL, flname);
			int n = stL.size();
			for (int i = 0; i < n; i++)
			{
				if (id == stL[i].id)
				{
					check = 1;
					st = stL[i];
					cout << "Here is his/her information:" << endl;
					display1studentline(st);
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
				importtoprogram2(stL, flname);
				displayclass(stL);
			}
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

void exportfromprogram(vector<student>stL, string fsname)
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
		exporttofile(fsave, stL);
		fsave.close();
	}
}

void findstudentin1class(vector<student> stL, int id, string classname, int& check, student& st, int& count)
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
			display1studentline(st);
			cout << endl;
			count++;
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
		st.DoB.year = stoi(temp);
		getline(fload, temp, ' ');
		st.DoB.month = stoi(temp);
		getline(fload, temp);
		st.DoB.day = stoi(temp);
		stL.push_back(st);
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
		fsave << stL[i].DoB.year << " " << stL[i].DoB.month << " " << stL[i].DoB.day;
		if (i < n - 1)
		{
			fsave << endl;
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

void sortclassinascendingorderbyid(vector<student>& stL)
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
	if (st.DoB.day < 10)
	{
		st.acc.password = "0" + to_string(st.DoB.day);
	}
	else
	{
		st.acc.password = to_string(st.DoB.day);
	}
	if (st.DoB.month < 10)
	{
		st.acc.password = st.acc.password + "0" + to_string(st.DoB.month);
	}
	else
	{
		st.acc.password = st.acc.password + to_string(st.DoB.month);
	}
	st.acc.password = st.acc.password + to_string(st.DoB.year);
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


void manageclassfunction()
{
	vector<student> stL;
	int choice = -1;
	cout << "What do you want to do: "; cout << endl;
	while (choice != 0)
	{
		cout << "Enter 0 to exit the program" << endl;
		cout << "Enter 1 to import a class from csv file" << endl;
		cout << "Enter 2 to add new student" << endl;
		cout << "Enter 3 to edit an existing student" << endl;
		cout << "Enter 4 to remove a student" << endl;
		cout << "Enter 5 to change a student's class" << endl;
		cout << "Enter 6 to view list of classes" << endl;
		cout << "Enter 7 to view list of students in a class" << endl;
		cout << "Enter what you want to do: ";
		cin >> choice;
		while (choice < 0 && choice > 9)
		{
			cout << "Invalid choice. Please enter your choice again: ";
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
			stL.clear();
			ifstream fload;
			string className;
			cout << "Input file to import: ";
			getline(cin, className);
			className = className + ".csv";
			importtoprogram(stL, className);
			while (stL.size() == 0)
			{
			    int confirmChoice;
				cout << "There nothing to import here." << endl;
				cout << "Enter 1 to input the name of the class you want to import, enter 0 to exit." << endl;
				cout << "Your choice: ";
				cin >> confirmChoice;
				while (cin.fail() || confirmChoice != 1 || confirmChoice != 0)
				{
				    cin.clear();
				    cin.ignore(1024, '\n');
					cout << "Invalid choice" << endl;
					cin >> confirmChoice;
				}
				if (confirmChoice == 1)
				{
					cout << "Input name of the class you want to import its data: ";
					getline(cin, className);
					className = className + ".csv";
					importtoprogram(stL, className);
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
			stL.clear();
			string choice3 = "-1", choice3s;
			cout << "Which class do you want to add new student?" << endl;
			cout << "Class: ";
			string classname3, flclassname3;
			getline(cin, classname3);
			flclassname3 = classname3 + "/" + classname3 + ".dat";
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
					flclassname3 = classname3 + "/" + classname3 + ".dat";
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
				sortclassinascendingorderbyid(stL);
				cout << endl << "Addition is updated:" << endl;
				displayclass(stL);
				cout << "Do you want to save what you have done to this class's file?" << endl;
				cout << "Enter 1 to save or 0 to exit: ";
				getline(cin, choice3s);
				while (choice3s != "1" && choice3s != "0")
				{
					cout << "Invalid choice." << endl;
					cout << "Please enter 1 to save or 0 to exit: ";
					getline(cin, choice3s);
				}
				if (choice3s == "1")
				{
					string fsclassname3 = classname3 + "/" + classname3 + ".dat";
					exportfromprogram2(stL, fsclassname3);
				}
			}
			break;
		}
		case 3:
		{
			stL.clear();
			int check4 = 0, id4, count4 = 1, count42 = 0, n4, No4, n42;
			string choice42, choice4 = "-1", choice4s;
			string classname4;
			string flclassname4;
			student st4;
			string fsclassname4;
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
				flclassname4 = classname4 + "/" + classname4 + ".dat";
				importtoprogram2(stL, flclassname4);
				while (stL.size() == 0)
				{
					cout << "There is nothing to edit here." << endl;
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
						flclassname4 = classname4 + "/" + classname4 + ".dat";
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
					findstudentin1class(stL, id4, classname4, check4, st4, count42);
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
							findstudentin1class(stL, id4, classname4, check4, st4, count42);
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
					findstudentinexistingclasses(stL, id4, check4, st4, classname4, count4);
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
							findstudentinexistingclasses(stL, id4, check4, st4, classname4, count4);
						}
						else
						{
							break;
						}
					}
					if (count4 == 1)
					{
						findstudentin1class(stL, id4, classname4, check4, st4, count42);
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
				if (count4 > 1)
				{
					cout << "Because there are more than one class that constant to student has ID" << id4 << "." << endl;
					cout << "So we need you to chose the class of the student who you want to edit." << endl;
					cout << "Please input the name of the class: ";
					getline(cin, classname4);
					stL.clear();
					flclassname4 = classname4 + "/" + classname4 + ".dat";
					importtoprogram2(stL, flclassname4);
					findstudentin1class(stL, id4, classname4, check4, st4, count42);
					while (check4 == 0)
					{
						cout << "There is no student has the ID " << id4 << " in this class." << endl;
						cout << "Please enter 1 to input the name of the class again or enter 0 to exit: ";
						getline(cin, choice4);
						while (choice4 != "1" && choice4 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Enter 1 to input the name of the class again or enter 0 to exit: ";
							getline(cin, choice4);
						}
						if (choice4 != "0")
						{
							cout << "Please input the name of the class: ";
							stL.clear();
							getline(cin, classname4);
							flclassname4 = classname4 + "/" + classname4 + ".dat";
							importtoprogram2(stL, flclassname4);
							findstudentin1class(stL, id4, classname4, check4, st4, count42);
						}
						else
						{
							break;
						}
					}
				}
				if (choice4 != "0")
				{
					if (count42 > 1)
					{
						int check43 = 0;
						cout << "Because there is more than 1 student has the ID " << id4 << " in class " << classname4 << "." << endl;
						cout << "So we need you to input the No of the student you want to edit: ";
						cin >> No4;
						cin.ignore(1);
						n42 = stL.size();
						while (No4 < 1 || No4 > n42)
						{
							cout << "Error:The No of student must bigger than 0 and smaller than " << n42 << "." << endl;
							cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
							getline(cin, choice4);
							while (choice4 != "1" && choice4 != "0")
							{
								cout << "Invalid choice." << endl;
								cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
								getline(cin, choice4);
							}
							if (choice4 == "1")
							{
								cout << "Please input the No of the student you want to edit: ";
								cin >> No4;
								cin.ignore(1);
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
							cout << "There is no student has the No " << No4 << "and ID " << id4 << " in this class." << endl;
							cout << "Please input 1 to input No again or 0 to exit: ";
							getline(cin, choice4);
							while (choice4 != "1" && choice4 != "0")
							{
								cout << "Invalid choice." << endl;
								cout << "Please input 1 to input No again or 0 to exit: ";
								getline(cin, choice4);
							}
							if (choice4 == "1")
							{
								cout << "Input No of the student you want to edit: ";
								cin >> No4;
								cin.ignore(1);
								while (No4 < 1 || No4 > n42)
								{
									cout << "Error:The No of student must bigger than 0 and smaller than " << n42 << "." << endl;
									cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
									getline(cin, choice4);
									while (choice4 != "1" && choice4 != "0")
									{
										cout << "Invalid choice." << endl;
										cout << "Please enter 1 to input the No of the student you want to edit again or enter 0 to exit: ";
										getline(cin, choice4);
									}
									if (choice4 == "1")
									{
										cout << "Please input the No of the student you want to edit: ";
										cin >> No4;
										cin.ignore(1);
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
							}
						}
					}
					else
					{
						No4 = st4.No;
					}
					if (choice4 != "0")
					{
						cout << "Are you sure you want to edit this student?" << endl;
						cout << "Enter 1 to continue to edit or enter 0 to exit: ";
						getline(cin, choice4);
						while (choice4 != "1" && choice4 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Enter 1 to continue to edit or enter 0 to exit: ";
							getline(cin, choice4);
						}
						if (choice4 != "0")
						{
							editinganexistingstudent(st4);
							updateeditstudentin1class(stL, No4, st4);
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
								fsclassname4 = classname4 + "/" + classname4 + ".dat";
								exportfromprogram2(stL, fsclassname4);
							}
							if (count4 > 1)
							{
								cout << endl << "Do you want to update what you edited to orthers student has ID " << id4 << "?" << endl;
								cout << "Enter 1 to update to all class." << endl;
								cout << "Enter 2 to input the number of the class and the name of class(es) that you want update." << endl;
								cout << "Enter 0 to cancle the updation and exit." << endl;
								cout << "Your choice: ";
								getline(cin, choice4);
								while (choice4 != "0" && choice4 != "1" && choice4 != "2")
								{
									cout << endl << "Invalid choice." << endl;
									cout << "Enter 1 to update to all class (all student has the ID " << id4 << ")." << endl;
									cout << "Enter 2 to input the number of the class and the name of class(es) that you want update." << endl;
									cout << "Enter 0 to cancle the updation and exit." << endl;
									cout << "Your choice: ";
									getline(cin, choice4);
								}
								if (choice4 == "1")
								{
									updateeditedstudentinallhisorherclasses(stL, id4, st4);
								}
								else
								{
									if (choice4 == "2")
									{
										cout << "Input the number of class that you want to update its (their) data: ";
										cin >> n4;
										cin.ignore(1);
										for (int i = 0; i < n4; i++)
										{
											stL.clear();
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
											importtoprogram2(stL, flclassname4);
											displayclass(stL);
											cout << "Are you sure that you want to update what you did to class " << classname4 << "?" << endl;
											cout << "Enter 1 to continue or 0 to exit: ";
											getline(cin, choice4);
											while (choice4 != "0" && choice4 != "1")
											{
												cout << "Invalid choice." << endl;
												cout << "Please enter 1 to continue to update the data of class " << classname4 << " or 0 to exit: " << endl;
												getline(cin, choice4);
											}
											if (choice4 != "0")
											{
												cout << "Please input No of student you want to place an update to: ";
												cin >> No4;
												cin.ignore(1);
												n42 = stL.size();
												while (No4 < 1 || No4 > n42)
												{
													cout << "The No of student must be bigger than 0 and smaller than " << n42 << "." << endl;
													cout << "Please enter 1 to input the No of student again or enter 0 to exit: ";
													getline(cin, choice4);
													while (choice4 != "0" && choice4 != "1")
													{
														cout << "Invalid choice." << endl;
														cout << "Please enter 1 to input the No of student again or enter 0 to exit: ";
														getline(cin, choice4);
													}
													if (choice4 == "1")
													{
														cout << "Please input No of student you want to place an update to: ";
														cin >> No4;
														cin.ignore(1);
													}
												}
												updateeditstudentin1class(stL, No4, st4);
												cout << "Do you want to save what you have done to this class's file?" << endl;
												cout << "Enter 1 to save or 0 to exit: "; getline(cin, choice4s);
												while (choice4s != "1" && choice4s != "0")
												{
													cout << "Invalid choice." << endl;
													cout << "Please enter 1 to save or 0 to exit: ";
													getline(cin, choice4s);
												}
												if (choice4s == "1")
												{
													fsclassname4 = classname4 + "/" + classname4 + ".dat";
													exportfromprogram2(stL, fsclassname4);
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
			int check5 = 0, id5, count5 = 1, count52 = 0;
			student st5;
			string classname5, choice5 = "-1", choice52, choice5s;
			string flclassname5, fsclassname5;
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
				flclassname5 = classname5 + "/" + classname5 + ".dat";
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
						flclassname5 = classname5 + "/" + classname5 + ".dat";
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
					findstudentin1class(stL, id5, classname5, check5, st5, count52);
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
							findstudentin1class(stL, id5, classname5, check5, st5, count52);
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
					findstudentinexistingclasses(stL, id5, check5, st5, classname5, count5);
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
							findstudentinexistingclasses(stL, id5, check5, st5, classname5, count5);
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
				cin.ignore(1);
				removestudentfromclass(stL, id5, classname5);
				cout << "The class at the moment: " << endl;
				displayclass(stL);
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
					fsclassname5 = classname5 + "/" + classname5 + ".dat";
					exportfromprogram2(stL, fsclassname5);
				}
			}
			if (check5 != 0 && count5 > 1)
			{
				cout << "How many classes do you want to delete this student?" << endl;
				cout << "Enter 1 to delete this student in all class." << endl;
				cout << "Enter 2 to input the number of the class and the name of class(es) that you want to delete this student." << endl;
				cout << "Enter 0 to cancle the removal and exit." << endl;
				cout << "Your choice: ";
				cin.ignore(1);
				getline(cin, choice5);
				while (choice5 != "0" && choice5 != "1" && choice5 != "2")
				{
					cout << "Invalid choice." << endl;
					cout << "Enter 1 to delete this student in all class." << endl;
					cout << "Enter 2 to input the number of the class and the name of class(es) that you want to delete this student." << endl;
					cout << "Enter 0 to cancle the removal and exit." << endl;
					cout << "Your choice: ";
					getline(cin, choice5);
				}
				if (choice5 == "1")
				{
					removestudentfromallclass(stL, id5);
				}
				else
				{
					if (choice5 == "2")
					{
						int n;
						cout << "Input the number of class that you want to delete this student: "; cin >> n;
						cin.ignore(1);
						for (int i = 0; i < n; i++)
						{
							stL.clear();
							if (n > 1)
							{
								cout << "Input the name of class number " << i + 1 << ": ";
							}
							else
							{
								cout << "Input the name of class: ";
							}
							getline(cin, classname5);
							flclassname5 = classname5 + "/" + classname5 + ".dat";
							importtoprogram2(stL, flclassname5);
							removestudentfromclass(stL, id5, classname5);
							cout << "The class at the moment: " << endl;
							displayclass(stL);
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
								fsclassname5 = classname5 + "/" + classname5 + ".dat";
								exportfromprogram2(stL, fsclassname5);
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
			student st6;
			vector<student>stLB;
			stLA.clear();
			stLB.clear();
			string clsAname, clsBname;
			string clsAnametempl, clsBnametempl;
			string choice6 = "-1", choice62;
			int id6, check6 = 0, count6 = 1, count62 = 0, No6 = 0;
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
				clsAnametempl = clsAname + "/" + clsAname + ".dat";
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
						clsAnametempl = clsAname + "/" + clsAname + ".dat";
						importtoprogram2(stLA, clsAnametempl);
					}
				}
				if (choice6 != "0")
				{
					cout << "Class " << clsAname << ":" << endl;
					displayclass(stLA);
					cout << "Are you sure you want to change a student in this class?" << endl;
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
					findstudentin1class(stLA, id6, clsAname, check6, st6, count62);
					while (check6 == 0)
					{
						cout << "There is no student has the ID " << id6 << " in this class." << endl;
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
							findstudentin1class(stL, id6, clsAname, check6, st6, count62);
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
					findstudentinexistingclasses(stLA, id6, check6, st6, clsAname, count6);
					while (check6 == 0)
					{
						cout << "The student with the ID " << id6 << " does not exists." << endl;
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
							findstudentinexistingclasses(stLA, id6, check6, st6, clsAname, count6);
						}
					}
					if (choice6 == "0")
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
						importtoprogram2(stLA, clsAnametempl);
						displayclass(stLA);
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
								check6 = 0;
								break;
							}
							else
							{
								cout << "Input first class (class you want to bring the student out): ";
								getline(cin, clsAname);
								clsAnametempl = clsAname + "/" + clsAname + ".dat";
								importtoprogram2(stLA, clsAnametempl);
							}
						}
						findstudentin1class(stLA, id6, clsAname, check6, st6, count62);
						while (check6 == 0)
						{
							cout << "There is no student has ID " << id6 << " in this class." << endl;
							cout << "Do you want to input the class you want this student to move out (first class) again?" << endl;
							cout << "Enter 1 to input again or 0 to exit: ";
							getline(cin, choice6);
							while (choice6 != "1" && choice6 != "0")
							{
								cout << "Invalid choice." << endl;
								cout << "Please enter 1 to input again or 0 to exit: ";
								getline(cin, choice6);
							}
							if (choice6 == "1")
							{
								cout << "Input the name of the first class: ";
								getline(cin, clsAname);
								clsAnametempl = clsAname + "/" + clsAname + ".dat";
								importtoprogram2(stLA, clsAnametempl);
								findstudentin1class(stL, id6, clsAname, check6, st6, count62);
							}
							else
							{
								break;
							}
						}
					}
					if (check6 != 0 && count6 == 1)
					{
						findstudentin1class(stLA, id6, clsAname, check6, st6, count62);
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
				if (count6 == 1 && count62 == 1)
				{
					cin.ignore(1);
					No6 = st6.No;
				}
				if (count6 > 1 && count62 == 1)
				{
					No6 = st6.No;
				}
				if (count62 > 1)
				{
					cout << "Because there are more than one student that have the ID " << id6 << "." << endl;
					cout << "Please input the No of the student you want to change: ";
					cin >> No6;
					int n6 = stLA.size();
					while (No6 < 1 || No6 > n6)
					{
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
					cin.ignore(1);
					while (check63 == 0)
					{
						cout << "There is no student has No " << No6 << " and ID " << id6 << "." << endl;
						cout << "Please enter 1 to input the No again or 0 to exit: ";
						getline(cin, choice6);
						while (choice6 != "1" && choice6 != "0")
						{
							cout << "Invalid choice." << endl;
							cout << "Please enter 1 to input the No again or 0 to exit: ";
							getline(cin, choice6);
						}
						if (choice6 == "1")
						{
							cout << "Inout No: "; cin >> No6;
							while (No6 < 1 || No6 > n6)
							{
								cout << "The No of the student must be bigger than 0 and smaller than " << n6 << "." << endl;
								cout << "Please input the No of the student you want to change: ";
								cin >> No6;
							}
							cin.ignore(1);
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
				if (choice6 != "0")
				{
					cout << "Input second class (class to want to put the student into): ";
					getline(cin, clsBname);
					clsBnametempl = clsBname + "/" + clsBname + ".dat";
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
						changestudentfromclassAtoclassB(stLA, stLB, No6, check62, id6);
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
							cout << "Do you want to save what you have done to class" << clsAname << "'s file and class" << clsBname << "'s file?" << endl;
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
								string clsAnametemps = clsAname + "/" + clsAname + ".dat";
								exportfromprogram2(stLA, clsAnametemps);
								string clsBnametemps = clsBname + "/" + clsBname + ".dat";
								exportfromprogram2(stLB, clsBnametemps);
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
			displayallclassincourse(stL);
			break;
		}
		case 7:
		{
			stL.clear();
			string classname8, choice8;
			cout << "Enter the class you want to view: ";
			getline(cin, classname8);
			string fclassname8l = classname8 + "/" + classname8 + ".dat";
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
