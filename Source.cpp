//---------------------------------------------------------< Header Files >------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//---------------------------------------------------------< Strcture >----------------------------------------------------------------
struct employ {
	string e_id;                 //Employ ID
	string e_name;               //Employ Name
	string desi;                 //Designation
	string b_sal;                   //Basic Salary
	string month;                //Month
	string leaves;                  //Leaves
	string a_leaves;                //Allowed leaves
	string p_l_d_r;                 //Per Leave Deduction Rate
	string salary;                  //Salary After Decduction
};
//----------------------------------------------------------< Prototypes >--------------------------------------------------------------
void mainheader();
void choices(employ alldata);
void choice2(employ alldata);
string inputcheck(string str);
void FirstLineOfFile();
int spacecountstring(string x);
int spacecountstring2(string x);
string spaceremove(string str);
//*****************************************************************************************************************************************
//*************************************************************< MAIN FUNCTION >***********************************************************
//*****************************************************************************************************************************************
int main()
{
	string choice;
	string moreinput;
	struct employ list = { "","","","","","","","","" };                //Delclareation of Array of struct type employ
	system("CLS");
	do {
		mainheader();
		cout << "\n\n\n";
		cout << "1.Enter 1 to enter information of employee to manage salary of specific month" << endl;
		cout << "2.Enter 2 to Print Salary Slip" << endl;
		cout << "3.Enter 3 to enter information of new employee" << endl;
		cout << "4.Enter 4 to Quit" << endl;
		cout << "Enter Here >>";
		cin >> choice;
		int success = 0;
		while (success == 0)
		{
			if (choice != "1" && choice != "2" && choice != "3" && choice != "4")
			{
				cout << "Please Enter Digits between (1-4)>>";
				cin >> choice;
				success = 0;
			}
			else
				success = 1;
		}
		switch (stoi(choice))
		{
		case 1:
		{
			fstream data("EmployeesManagementSystem.txt", ios::binary | ios::app);     //ios::binary for checking file size and ios::out included is file was not created to create one
			data.seekg(0, ios::end);                //size check
			int file_size = data.tellg();            //size stored in file_size
			if (file_size == 0)                      //If size is zero means file is empty then print first line 
			{
				FirstLineOfFile();
			}
			data.close();                           //file closed
			do {
				choices(list);
				cout << ">>Enter anykey for futher inputs. \n>>Enter -1 to terminate inputs." << endl;
				cout << "Enter Here >>";
				cin >> moreinput;
			} while (moreinput != "-1");
			system("CLS");
			break;
		}
		case 2:
		{
			choice2(list);
			break;
		}
		case 3:
		{
			fstream data("EmployeesManagementSystem.txt", ios::binary | ios::app);
			data.seekg(0, ios::end);
			int file_size = data.tellg();
			if (file_size == 0)
			{
				FirstLineOfFile();
			}
			data.close();
			choices(list);
			system("CLS");
			break;
		}
		case 4:
			break;
		}

	} while (choice != "4");

	return 0;
}
void choices(employ alldata)
{
	cin.ignore();
	cout << "Enter Employs ID :";
	getline(cin, alldata.e_id);
	cout << "Enter Employs Name :";
	getline(cin, alldata.e_name);
	cout << "Enter Employs Designation :";
	getline(cin, alldata.desi);
	cout << "Enter Employs Basic Salary :";
	cin >> alldata.b_sal;
	alldata.b_sal = inputcheck(alldata.b_sal);
	cin.ignore();
	cout << "Enter month of salary :";
	getline(cin, alldata.month);
	cout << "Enter Employs Total leaves :";
	cin >> alldata.leaves;
	alldata.leaves = inputcheck(alldata.leaves);
	cout << "Enter total number of leaves allowed per month :";
	cin >> alldata.a_leaves;
	alldata.a_leaves = inputcheck(alldata.a_leaves);
	cout << "Enter Per Leave Deduction Rate :";
	cin >> alldata.p_l_d_r;
	alldata.p_l_d_r = inputcheck(alldata.p_l_d_r);
	int b_sal = stoi(alldata.b_sal), leaves = stoi(alldata.leaves), a_leaves = stoi(alldata.a_leaves), p_l_d_r = stoi(alldata.p_l_d_r);           //stoi() covert string to int             
	int salary = b_sal - (leaves - a_leaves) * p_l_d_r;
	if (alldata.leaves > alldata.a_leaves)
	{
		alldata.salary = to_string(salary);                    //to_string() convert int to string
	}
	else
	{
		alldata.salary = alldata.b_sal;
	}
	fstream data;     //Created an object of type fstream 
	data.open("EmployeesManagementSystem.txt", ios::app);     //iso::app used to write file from last written text
	if (data.is_open())
	{
		int space1 = spacecountstring(alldata.e_id);                  //ID
		int space2 = spacecountstring(alldata.e_name);                  //Name
		int space3 = spacecountstring(alldata.desi);                  //Designation
		int space4 = spacecountstring(alldata.b_sal);                     //Basic Salary
		int space5 = spacecountstring(alldata.month);                  //Month
		int space6 = spacecountstring(alldata.leaves);                    //Leaves
		int space7 = spacecountstring(alldata.a_leaves);                    //Allowed Leaves
		int space8 = spacecountstring2(alldata.p_l_d_r);                     //Per Leave Deduction Rate
		data << "____________________________________________________________________________________________________________________________________________________________________________________________" << endl;
		data << alldata.e_id;
		for (int v = 0; v < space1; v++)
			data << " ";
		data << "|" << alldata.e_name;
		for (int w = 0; w < space2; w++)
			data << " ";
		data << "|" << alldata.desi;
		for (int x = 0; x < space3; x++)
			data << " ";
		data << "|" << alldata.b_sal;
		for (int y = 0; y < space4; y++)
			data << " ";
		data << "|" << alldata.month;
		for (int y = 0; y < space5; y++)
			data << " ";
		data << "|" << alldata.leaves;
		for (int z = 0; z < space6; z++)
			data << " ";
		data << "|" << alldata.a_leaves;
		for (int y = 0; y < space7; y++)
			data << " ";
		data << "|" << alldata.p_l_d_r;
		for (int g = 0; g < space8; g++)
			data << " ";
		data << "|" << alldata.salary << endl;
	}
	data.close();
}
void choice2(employ alldata)
{
	string month;
	cout << "Please Enter Month>>";
	cin >> month;
	fstream data;   //creted an object of type fstream
	data.open("EmployeesManagementSystem.txt", ios::in);        //ios::in used to read a file
	data.ignore(9898, '\n');
	data.ignore(9898, '\n');
	data.ignore(9898, '\n');
	getline(data, alldata.e_id, '|');
	getline(data, alldata.e_name, '|');
	getline(data, alldata.desi, '|');
	getline(data, alldata.b_sal, '|');
	getline(data, alldata.month, '|');
	getline(data, alldata.leaves, '|');
	getline(data, alldata.a_leaves, '|');
	getline(data, alldata.p_l_d_r, '|');
	getline(data, alldata.salary, '\n');
	int counter = 0;
	while (!data.eof())
	{
		string id = spaceremove(alldata.e_id);       //employ id without space
		string name = spaceremove(alldata.e_name);     //name without space
		string mahine = spaceremove(alldata.month);        //months without space   
		if (mahine == month)
		{
			string filename = id + "_" + name + "_" + mahine + "_" + "SalarySlip.txt";
			ofstream file;
			file.open(filename);
			file << "Salary Month :" << alldata.month << endl;
			file << "Employee Name :" << alldata.e_name << endl;
			file << "Designation :" << alldata.desi << endl;
			file << "Salary :" << alldata.salary << endl;
			file.close();
			counter++;
		}
		data.ignore(9898, '\n');
		getline(data, alldata.e_id, '|');
		getline(data, alldata.e_name, '|');
		getline(data, alldata.desi, '|');
		getline(data, alldata.b_sal, '|');
		getline(data, alldata.month, '|');
		getline(data, alldata.leaves, '|');
		getline(data, alldata.a_leaves, '|');
		getline(data, alldata.p_l_d_r, '|');
		getline(data, alldata.salary, '\n');
	}
	system("CLS");
	cout << "*********************************" << endl;
	if (counter == 0)
		cout << "No Record Found for this month!" << endl;
	else
		cout << "Slips Have been Printed...." << endl;

	cout << "*********************************" << endl;
	data.close();

}
void FirstLineOfFile() {
	fstream data;     //Created an object of type fstream 
	data.open("EmployeesManagementSystem.txt", ios::app);     //iso::app used to write file from last written text
	if (data.is_open())
	{
		data << "____________________________________________________________________________________________________________________________________________________________________________________________" << endl;
		data << "Employee ID";
		for (int v = 0; v < 9; v++)
			data << " ";
		data << "|" << "Employee Name";
		for (int v = 0; v < 7; v++)
			data << " ";
		data << "|" << "Designation";
		for (int v = 0; v < 9; v++)
			data << " ";
		data << "|" << "Basic Salary";
		for (int v = 0; v < 8; v++)
			data << " ";
		data << "|" << "Month";
		for (int v = 0; v < 15; v++)
			data << " ";
		data << "|" << "Leaves";
		for (int v = 0; v < 14; v++)
			data << " ";
		data << "|" << "Allowed Leaves";
		for (int v = 0; v < 6; v++)
			data << " ";
		data << "|" << "Per Leave Deduction Rate";
		for (int v = 0; v < 6; v++)
			data << " ";
		data << "|" << "Salary" << endl;
		data.close();
	}
}
string inputcheck(string str) {
	int counts = 0, len = 0, sucess = 0;
	do {
		int counts = 0, i, len = 0;
		for (i = 0; str[i] != '\0'; i++)
		{
			len++;                             //total length
		}
		for (i = 0; i < len; i++)
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				counts++;                  //length of digits
			}
		}
		if (counts != len)
		{
			cout << ">>Please Enter Digits From (0-9) :";
			cin >> str;
			sucess = 0;
		}
		else
			sucess = 1;
	} while (sucess == 0);
	return str;
}
int spacecountstring(string x) {
	return (20 - x.length());
}
int spacecountstring2(string x) {
	return (30 - x.length());
}
string spaceremove(string str)
{
	int len = str.length();
	string rstr = "";
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] != ' ')
		{
			for (int j = 0; j <= i; j++)
			{
				rstr += str[j];
			}
			break;
		}
	}
	return rstr;
}
void mainheader()
{
	cout << "    ____                          __    __                                                               " << endl;
	cout << "   / __ | ____ __  __ _____ ____ / /   / /                                                               " << endl;
	cout << "  / /_/ / __ `/ / / / ____/ __  / /   / /                                                                " << endl;
	cout << " / ____/ /_/ / /_/ / /   / /_/ / /___/ /___                                                              " << endl;
	cout << "/_/    |__,_/|__, /_/   /_____/_____/_____/                                                              " << endl;
	cout << "             /___/                                                                                       " << endl;
	cout << "                               __  ___                                                  __                           " << endl;
	cout << "                              /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_                          " << endl;
	cout << "                             / /|_/ / __ `/ __ |/ __ `/ __ `/ _ |/ __ `__ |/__ |/ __ |/ __/                          " << endl;
	cout << "                            / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_                            " << endl;
	cout << "                           /_/  /_/|__,_/_/ /_/|__,_/|__, /|___/_/ /_/ /_/|___/_/ /_/|__/                            " << endl;
	cout << "                                                    /____/                                                           " << endl;
	cout << "                                                       _____            __                                          " << endl;
	cout << "                                                      / ___/__  _______/ /____  ____ ___                            " << endl;
	cout << "                                                      |__ |/ / / / ___/ __/ _ |/ __ `__ |                           " << endl;
	cout << "                                                     ___/ / /_/ (__  ) /_/  __/ / / / / /                           " << endl;
	cout << "                                                    /____/|__, /____/|__/|___/_/ /_/ /_/                            " << endl;
	cout << "                                                         /____/                                                     " << endl;
}
