//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: ProgProject6.cpp    Assignment #6    Grade: _____              *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 24400  11                   Due Date:  November 18, 2016             *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of mailing records from an input   * 
//*           file into appropriate arrays of structures. After reading in all data    * 
//*           into the appropriate arrays the program is to take actions depending     * 
//*           on the info given in each line of input. Those actions are adding a      * 
//*           mailing record to the mailing list, deleting a record, changing the      * 
//*           information in an indicated field, printing the indicated information    * 
//*           and terminating the program. A mailing record consists of a Last Name,   *
//*           First Name, Street Address, City, State and Zip Code                     * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*       addCustomer -      adds a new customer to the mailing list.                  *
//*				                                                                       *
//*		  deleteCustomer -   deletes a customer from the mailing list.                 *  
//*																			           *
//*       changeCustomer -   changes the information of a customer in the mailing      *
//*                          list                                                      *  
//*		                                                                               *
//*       printCustomer -    prints the specified part of the mailing list             *
//*                                                                                    * 
//*       trim -             removes extra spaces from strings for formatting          * 
//*                          purposes                                                  * 
//*																			           *
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <iostream>

#define readEmployeeCode "A" // Add a customer. 
#define delEmployeeCode "D" // Delete a customer. 
#define changeEmployeeCode "C" // Change customer info. 
#define printEmployeeInfo "P"  // Print one or all customers. 
#define sentinel "Q"  // End of file character. 
#define formatLines "*********************************************************************"
#define formatSigns "================================================================================"

using namespace std;

struct MailingList
{
	char firstName[13];
	char lastName[13];
	char streetAddress[21];
	char city[13];
	char state[3];
	char zipCode[6];
};

void addCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU);
void deleteCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU);
void changeCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU);
void printCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU);
char *trim(char *theString);

void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);


int main()
{
	ifstream inFile("DATA6.TXT", ios::in); // Open the Input File. 
	ofstream outFile("RESULTS.TXT", ios::out); // Create the Output File. 
	outFile.setf(ios::fixed); // Set preciscion of Output File. 

	int EU = 0;
	MailingList mailers[50];
	char tempCode[20];

	//*******************************************************

		//Print the Header for the output file. 
	Header(outFile);

		// Read in the operation code. 
	inFile >> ws;
	inFile >> tempCode;

	  // Loop to determine what action to take based on operation code. 
	while (strcmp(tempCode, sentinel) != 0)
	{
		if (strcmp(tempCode, readEmployeeCode) == 0)
		{
			addCustomer(inFile, outFile, mailers, EU);
		}
		if (strcmp(tempCode, delEmployeeCode) == 0)
		{
			deleteCustomer(inFile, outFile, mailers, EU);
		}
		if (strcmp(tempCode, changeEmployeeCode) == 0)
		{
			changeCustomer(inFile, outFile, mailers, EU);
		}
		if (strcmp(tempCode, printEmployeeInfo) == 0)
		{
			printCustomer(inFile, outFile, mailers, EU);
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

char *trim(char *theString)
{
	// Given:   A character pointer to a string to be trimmed of white spaces.   
	// Task:    Trim the string of empty white spaces. 
	// Returns: A character pointer to the string that has now been trimmed of white spaces. 

		// Point to last character
	char *p = &theString[strlen(theString) - 1];

		// Move forward to first non-whitespace
	while (isspace(*p)) --p;

		// Move back one to beginning of whitespace
		// and terminate the string at that point
	*(++p) = '\0';

		// Point to front
	p = theString;

		// Find first non-whitespace
	while (isspace(*p)) ++p;

		// Copy from here (first non-whitespace) to beginning
	strcpy(theString, p);

	return theString;
}

//********************************************************************************

void addCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU)
{
	// Given:   The input file, the output file and the mailing list with it's elements used.  
	// Task:    Add a customer to the mailing list if it is valid to do so. 
	// Returns: the input file, the output file and the mailing list with its elements used all 
	//          by reference. 


	bool isDuplicateEntry = false;
	char trimFirstName[21] = { 0 };
	char trimLastName[21] = { 0 };
	char duplicateAddress[21] = { 0 };
	char duplicateCity[13] = { 0 };
	char duplicateState[3] = { 0 };
	char duplicateZip[6] = { 0 };

	infile >> ws;
	infile.getline(mailers[EU].firstName, 13);
	infile >> ws;
	infile.getline(mailers[EU].lastName, 13);

	for (int i = 0; i < EU; i++)
	{
		if (strcmp(mailers[i].firstName, mailers[EU].firstName) == 0 && strcmp(mailers[i].lastName, mailers[EU].lastName) == 0)
		{
			isDuplicateEntry = true;
			outFile << "ERROR ! Attempt to add a duplicate record. Attempt failed!" << endl;
			infile >> ws;
			infile.getline(duplicateAddress, 21);
			infile >> ws;
			infile.getline(duplicateCity, 13);
			infile >> ws;
			infile.getline(duplicateState, 3);
			infile >> ws;
			infile.getline(duplicateZip, 6);
			break;
		}
	}

	if (!isDuplicateEntry)
	{
		strcpy(trimFirstName, mailers[EU].firstName);
		strcpy(trimLastName, mailers[EU].lastName);

		outFile << "New customer " << trim(trimFirstName) << setw(8) << trim(trimLastName)
			    << " successfully added to the database!" << endl;

		infile >> ws;
		infile.getline(mailers[EU].streetAddress, 21);
		infile >> ws;
		infile.getline(mailers[EU].city, 13);
		infile >> ws;
		infile.getline(mailers[EU].state, 3);
		infile >> ws;
		infile.getline(mailers[EU].zipCode, 6);
		EU++;
	}
	outFile << formatLines << endl;

}

//********************************************************************************

void deleteCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU)
{
	// Given:   The input file, the output file and the mailing list with its elements used. 
	// Task:    Delete a customer from the mailing list if it is valid to do so. 
	// Returns: The input file, the output file, the mailing list and its used elements
	//          all by reference. 

	char firstNameToDelete[13] = { 0 };
	char lastNameToDelete[13] = { 0 };
	char trimFirstName[21] = { 0 };
	char trimLastName[21] = { 0 };
	bool isAMailer;
	int indexPos = 0;

	infile >> ws;
	infile.getline(firstNameToDelete, 13);
	infile >> ws;
	infile.getline(lastNameToDelete, 13);

	for (int i = 0; i < EU; i++)
	{
		if (strcmp(firstNameToDelete, mailers[i].firstName) == 0 && strcmp(lastNameToDelete, mailers[i].lastName) == 0)
		{
			isAMailer = true;  indexPos = i;
			break;
		}
		else {
			isAMailer = false;
		}
	}

	if (isAMailer)
	{
		strcpy(trimFirstName, mailers[indexPos].firstName);
		strcpy(trimLastName, mailers[indexPos].lastName);

		outFile << "Customer " << trim(trimFirstName) << setw(5) << trim(trimLastName) 
			    << " successfully removed from the database!" << endl; 
		outFile << formatLines << endl;

		for (int i = indexPos; i < EU; i++)
		{
			mailers[i] = mailers[i + 1];
		}
		EU--;
	}
	else {
		outFile << "ERROR ! Attempt to delete a non-existent record" << endl;
		outFile << formatLines << endl;
	}

}

//********************************************************************************

void changeCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU)
{
	// Given:   The input file, the output file and the mailing list with its elements used. 
	// Task:    Change information about a specified customer if it is valid to do so. 
	// Returns: The input file, the output file and the mailing list with it's elements used
	//          all by reference. 

	char newFirstName[13] = { 0 };
	char newLastName[13] = { 0 };
	char newStreetAddress[21] = { 0 };
	char newCity[13] = { 0 };
	char newState[3] = { 0 };
	char newZipCode[6] = { 0 };

	char trimFirstName[21] = { 0 };
	char trimLastName[21] = { 0 };

	char incorrectInformation[50] = { 0 };
	char lastNameToChange[13] = { 0 };

	int fieldID;
	bool isAMailer;
	int indexPos;

	infile >> ws;
	infile.getline(lastNameToChange, 13);
	infile >> fieldID;
	for (int i = 0; i < EU; i++)
	{
		if (strcmp(lastNameToChange, mailers[i].lastName) == 0)
		{
			isAMailer = true; indexPos = i;
			break;
		}
		else {
			isAMailer = false;
		}
	}

	if (isAMailer)
	{
		switch (fieldID) {
		case 1:
			infile >> ws;
			infile.getline(newFirstName, 13);
			strcpy(mailers[indexPos].firstName, newFirstName);
			break;
		case 2:
			infile >> ws;
			infile.getline(newLastName, 13);
			strcpy(mailers[indexPos].lastName, newLastName);
			break;
		case 3:
			infile >> ws;
			infile.getline(newStreetAddress, 21);
			strcpy(mailers[indexPos].streetAddress, newStreetAddress);
			break;
		case 4:
			infile >> ws;
			infile.getline(newCity, 13);
			strcpy(mailers[indexPos].city, newCity);
			break;
		case 5:
			infile >> ws;
			infile.getline(newState, 3);
			strcpy(mailers[indexPos].state, newState);
			break;
		case 6:
			infile >> ws;
			infile.getline(newZipCode, 6);
			strcpy(mailers[indexPos].zipCode, newZipCode);
			break;
		}

		strcpy(trimFirstName, mailers[indexPos].firstName);
		strcpy(trimLastName, mailers[indexPos].lastName);

		outFile << "Customer " << trimFirstName << setw(7) 
			    << trimLastName << " successfully updated!" << endl; 
		outFile << formatLines << endl;

	}
	else {
		infile >> ws;
		infile.getline(incorrectInformation, 22);

		outFile << "ERROR ! Attempt to change a non-existent record. Attempt failed!" << endl;
		outFile << formatLines << endl;

	}
}

//********************************************************************************

void printCustomer(ifstream &infile, ofstream &outFile, MailingList mailers[], int &EU)
{
	// Given:   The input file, the output file and the mailing list with its elements used. 
	// Task:    Print customer information. 
	// Returns: The input file, the output file and the mailing list with it's elements used
	//          all by reference. 

	char lastNameToChange[13] = { 0 };
	char trimFirstName[21] = { 0 };
	char trimLastName[21] = { 0 };

	char transType; // Transaction Type. 
	bool isAMailer;
	int indexPos;
	

	infile >> transType;
	if (transType == 'E')
	{
		outFile << "Customer" << setw(8) << "First"
			    << setw(11) << "Last" << setw(51) << "Zip" << endl;

		outFile << "Number" << setw(9) << "Name" << setw(12) << "Name"
			    << setw(19) << "Address" << setw(14) << "City"
		     	<< setw(11) << "State" << setw(8) << "Code" << endl;

		outFile << formatSigns << endl;

		for (int i = 0; i < EU; i++)
		{
		   outFile << i + 1 << setw(22) << mailers[i].firstName << setw(10)
				   << mailers[i].lastName << setw(10) << mailers[i].streetAddress
				   << setw(10) << mailers[i].city << setw(3) << mailers[i].state
				   << setw(10) << mailers[i].zipCode << endl;
		}
	}
	if (transType == 'S')
	{
		infile >> ws;
		infile.getline(lastNameToChange, 13);

		for (int i = 0; i < EU; i++)
		{
			if (strcmp(lastNameToChange, mailers[i].lastName) == 0)
			{
				isAMailer = true; indexPos = i;
				break;
			}
			else {
				isAMailer = false;
			}
		}

		if (isAMailer)
		{
			strcpy(trimFirstName, mailers[indexPos].firstName);
			strcpy(trimLastName, mailers[indexPos].lastName);

		    outFile << "Customer Number: " << indexPos + 1 << endl; 

		    outFile << "Name: " << trim(trimFirstName) << setw(8)
			        << trim(trimLastName) << setw(15) << "Address: " 
				    << setw(10) << mailers[indexPos].streetAddress << endl;
			 
		    outFile << "City: " << mailers[indexPos].city << setw(12)
				    << "State: " << mailers[indexPos].state << setw(14)
				    << "Zip Code: " << mailers[indexPos].zipCode << endl;

		    outFile << formatLines << endl;

		}
		else {
			outFile << "ERROR ! Attempt to print a non-existent record. Attempt failed!" << endl;
			outFile << formatLines << endl;

		}

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
	Outfile << setw(20) << "Assignment #6" << endl;
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