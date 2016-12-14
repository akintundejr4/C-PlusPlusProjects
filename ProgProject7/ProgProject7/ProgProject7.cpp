//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: ProgProject7.cpp    Assignment #7    Grade: _____              *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 24400  11                   Due Date:  December 2, 2016              *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads data information about a group of employees at an  IT * 
//*           company. The data consists of a First and Last name, an ID number, a     * 
//*           department, a title and the employee's pay. The data will contain action * 
//*           codes that will perform actions based on the code. Those actions will be * 
//*           reading in data, delete an employee record, updating information, print- * 
//*           ing information and terminating the program. Each action will be modu-   * 
//*           larized within a function.                                               *
//*                                                                                    * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*       CompanyInformation-  constructor for the Company Information class           *
//*				               Intializes class values to empty.                       *
//*                                                                                    * 
//*       calcEmployeePay -   calculates the company payroll                           * 
//*                                                                                    * 
//*		  readEmployee -      adds an employee to the company list.                    *  
//*																			           *
//*       deleteEmployee -    deletes an employee from the company list                *
//*                                                                                    * 
//*       changeEmployee -    changes information on a specifed employee.              *
//*                                                                                    * 
//*       printEmployee -     prints employee information.                             * 
//*                                                                                    * 
//*																			           *
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <iostream>

#define readEmployeeCode "I" // Read in the data.  
#define delEmployeeCode "D" // Delete an employee record. 
#define changeEmployeeCode "C" // Update employee info. 
#define printEmployeeInfo "P"  // Print to output file. 
#define sentinel "Q"  // End of file character. 
#define formatLines "************************************************************************************"
#define formatSigns "===================================================================================="

using namespace std;

struct EmployeeType
{
	int ID;
	string firstName;
	string lastName;
	string department;
	string title;
	float pay;
};

class CompanyInformation
{
public:
	CompanyInformation();
	void calcEmployeePay(CompanyInformation companyEmployees[], int &EU);
	void readEmployee(ifstream &infile, int &EU);
	void deleteEmployee(ifstream &infile, CompanyInformation companyEmployees[], int &EU);
	void changeEmployee(ifstream &infile, CompanyInformation companyEmployees[], int &EU);
	void printEmployee(ifstream &infile, ofstream &outFile, 
		              CompanyInformation companyEmployees[], int &EU);

private:
	EmployeeType employee;
	static float totalPayRollAmt;
};

float CompanyInformation::totalPayRollAmt;
void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);


int main()
{
	ifstream inFile("DATA7.TXT", ios::in); // Open the Input File. 
	ofstream outFile("RESULTS.TXT", ios::out); // Create the Output File. 
	outFile.setf(ios::fixed); // Set preciscion of Output File. 

	int EU = 0;
	CompanyInformation companyEmployees[50];
	char tempCode[20];

	//*******************************************************

		//Print the Header for the output file. 
	Header(outFile);

		// Read in the operation code. 
	inFile >> ws;
	inFile >> tempCode;

		// Determine what action to take based on operation code. 
	while (strcmp(tempCode, sentinel) != 0)
	{
		if (strcmp(tempCode, readEmployeeCode) == 0)
		{
			companyEmployees[EU].readEmployee(inFile, EU);
		}
		if (strcmp(tempCode, delEmployeeCode) == 0)
		{
			companyEmployees[EU].deleteEmployee(inFile, companyEmployees, EU);
		}
		if (strcmp(tempCode, changeEmployeeCode) == 0)
		{
			companyEmployees[EU].changeEmployee(inFile, companyEmployees, EU);
		}
		if (strcmp(tempCode, printEmployeeInfo) == 0)
		{
			companyEmployees[EU].calcEmployeePay(companyEmployees, EU);
			companyEmployees[EU].printEmployee(inFile, outFile, 
				                               companyEmployees, EU);
			outFile << endl;
		}
			// Read in the next operation code. 
		inFile >> ws;
		inFile >> tempCode;
	}

		//Print the footer for the output file. 
	Footer(outFile);

	//*******************************************************

		// Close the Output file. 
	outFile.close();

	return 0;
}

//********************************************************************************

CompanyInformation::CompanyInformation()
{
	// Given:   Nothing. 
	// Task:    Initialize CompanyInformation's starting values to zero and null. 
	// Returns: Nothing. 

	employee = { 0 };
	totalPayRollAmt = 0;
}
//********************************************************************************

void CompanyInformation::calcEmployeePay(CompanyInformation companyEmployees[], int &EU)
{
	// Given:   The array of company employees and the elements used in it.  
	// Task:    Calculate the company payroll. 
	// Returns: The company employee list and it's elements used by reference.  

	for (int i = 0; i < EU; i++)
	{
		totalPayRollAmt += companyEmployees[i].employee.pay;
	}
}

//********************************************************************************

void CompanyInformation::readEmployee(ifstream &infile, int &EU)
{
	// Given:   The input file & the elements used in the company employee list array.  
	// Task:    Add an employee to the company list. 
	// Returns: the input file and the elements used in the company employee list
	//          array all by reference.  

	infile >> employee.ID;
	infile >> ws;
	getline(infile, employee.firstName);
	infile >> ws;
	getline(infile, employee.lastName);
	infile >> ws;
	getline(infile, employee.department);
	infile >> ws;
	getline(infile, employee.title);
	infile >> employee.pay;
	EU++;

}

//********************************************************************************

void CompanyInformation::deleteEmployee(ifstream &infile, CompanyInformation companyEmployees[], 
	                                    int &EU)
{
	// Given:   The input file, the company employee list array and it's elements used. 
	// Task:    Delete an employee from the company employee list. 
	// Returns: The input file, the company employee list and it's elements used
	//          all by reference. 

	int idToDelete;
	int indexPos;
	infile >> idToDelete;

	for (int i = 0; i < EU; i++)
	{
		if (companyEmployees[i].employee.ID == idToDelete)
		{
			indexPos = i;
			break;
		}
	}

	for (int i = indexPos; i < EU; i++)
	{
		companyEmployees[i] = companyEmployees[i + 1];
	}
	EU--;

}

////********************************************************************************

void CompanyInformation::changeEmployee(ifstream &infile, CompanyInformation companyEmployees[],
	                                    int &EU)
{
	// Given:   The input file, the company employee list array and it's elements used. 
	// Task:    Change an employee's information. 
	// Returns: The input file, the company employee list and it's elements used
	//          all by reference. 


	string newFirstName;
	string newLastName;
	string newDepartment;
	string newTitle;
	int newPay;

	int idToChange;
	int fieldID;
	int indexPos;

	infile >> idToChange;
	infile >> fieldID;

	for (int i = 0; i < EU; i++)
	{
		if (companyEmployees[i].employee.ID == idToChange)
		{
			indexPos = i;
			break;
		}
	}

	switch (fieldID) {
	case 1:
		infile >> ws;
		getline(infile, newFirstName);
		companyEmployees[indexPos].employee.firstName = newFirstName;
		break;
	case 2:
		infile >> ws;
		getline(infile, newLastName);
		companyEmployees[indexPos].employee.lastName = newLastName;
		break;
	case 3:
		infile >> ws;
		getline(infile, newDepartment);
		companyEmployees[indexPos].employee.department = newDepartment;
		break;
	case 4:
		infile >> ws;
		getline(infile, newTitle);
		companyEmployees[indexPos].employee.title = newTitle;
		break;
	case 5:
		infile >> newPay;
		companyEmployees[indexPos].employee.pay = newPay;
		break;
	}

}

////********************************************************************************

void CompanyInformation::printEmployee(ifstream &infile, ofstream &outFile,  
	                                   CompanyInformation companyEmployees[], int &EU)
{

	// Given:   The input file, output file & employee list array with it's elements used. 
	// Task:    Print employee information. 
	// Returns: The input file, output file & the company employee list with it's elements used
	//          all by reference. 

	char transType;
	int indexPos;
	int idNumberToChange;

	infile >> transType;
	if (transType == 'E')
	{
		outFile << "ID #" << setw(21) << "Name"
			<< setw(26) << "Department" << setw(16)
			<< "Position" << setw(12) << "Pay" << endl;

		outFile << formatSigns << endl;

		for (int i = 0; i < EU; i++)
		{
			outFile << companyEmployees[i].employee.ID << setw(22)
				<< companyEmployees[i].employee.firstName << setw(10)
				<< companyEmployees[i].employee.lastName << setw(10)
				<< companyEmployees[i].employee.department << setw(10)
				<< companyEmployees[i].employee.title << setw(10)
				<< setprecision(2)
				<< companyEmployees[i].employee.pay << endl;
		}
		outFile << formatSigns << endl;

		outFile << setw(50) << "Total Amount of Payroll "
			<< setw(34) << setprecision(2)
			<< totalPayRollAmt << endl;
		outFile << formatLines << endl;

	}
	if (transType == 'S')
	{
		infile >> idNumberToChange;

		for (int i = 0; i < EU; i++)
		{
			if (companyEmployees[i].employee.ID == idNumberToChange)
			{
				indexPos = i;
				break;
			}
		}

		outFile << "ID #" << setw(23) << "Name"
			<< setw(24) << "Department" << setw(17)
			<< "Position" << setw(13) << "Pay" << endl;

		outFile << formatSigns << endl;

		outFile << companyEmployees[indexPos].employee.ID << setw(22)
			<< companyEmployees[indexPos].employee.firstName << setw(10)
			<< companyEmployees[indexPos].employee.lastName << setw(10)
			<< companyEmployees[indexPos].employee.department << setw(10)
			<< companyEmployees[indexPos].employee.title << setw(11)
			<< setprecision(2)
			<< companyEmployees[indexPos].employee.pay << endl;

		outFile << formatLines << endl;
	}
}

//********************************************************************************


//********************************** FUNCTION HEADER *****************************
void Header(ofstream &Outfile)
{
	// Recieves - the output file
	// Task - Prints the output preamble
	// Returns - Nothing

	Outfile << setw(30) << "AkinTunde Akinyemi";
	Outfile << setw(17) << "CSC 24400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Fall 2016";
	Outfile << setw(20) << "Assignment #7" << endl;
	Outfile << setw(35) << "----------------------------------------";
	Outfile << setw(35) << "----------------------------------------" << endl << endl;
	return;
}
//******************************* END OF FUNCTION HEADER *************************

//********************************** FUNCTION FOOTER *****************************
void Footer(ofstream &Outfile)
{
	// Recieves - the output file
	// Task - Prints the output salutation
	// Returns - Nothing

	Outfile << endl;
	Outfile << setw(35) << "----------------------------------------" << endl;
	Outfile << setw(35) << "|         END OF PROGRAM OUTPUT        |" << endl;
	Outfile << setw(35) << "----------------------------------------" << endl;
	return;
}
//******************************* END OF FUNCTION FOOTER ***********************