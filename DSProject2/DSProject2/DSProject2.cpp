
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of mailing  records to maintain a  * 
//*           a mailing list. The program will deal with adding, deleting, changing    * 
//*           and printing informaion about the mailing list.                          * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*       addRecord    -    adds a customer to the mailing list.                       *
//*                            												           *
//*		  deleteRecord -    deletes a customer from the mailing list                   * 
//*																			           *
//*       changeRecord -    changes the requested information of a customer in the list*
//*		                                                                               *
//*      printRecord   -    prints the linked list.                                    *
//*                                                                                    * 
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <iostream>

#define formatSigns "================================================================================"
#define addCode "A" // Add a customer. 
#define delCode "D" // Delete a customer. 
#define changeCode "C" // Change customer info. 
#define printCode "P"  // Print one or all customers. 
#define endCode "Q"  // End of file character. 

using namespace std;

struct NodeType
{
	char firstName[13];
	char lastName[13];
	char streetAddress[21];
	char city[13];
	char state[3];
	char zipCode[6];

	NodeType *next;
};

class LinkedList
{
public:
	LinkedList();
	void addRecord(ofstream &outfile, NodeType node);
	NodeType deleteRecord(ofstream &outfile, char fname[13], char lname[13], NodeType node);
	void changeRecord(ifstream &infile, ofstream &outfile, NodeType node);
	void printRecords(ofstream &outFile);

private:
	NodeType *startPtr;
};


void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);


int main()
{
	ifstream infile("data2.TXT", ios::in); // Open the Input File. 
	ofstream outfile("RESULTS.TXT", ios::out); // Create the Output File. 
	outfile.setf(ios::fixed); // Set preciscion of Output File. 


	int EU = 0;
	LinkedList Mailers;
	NodeType Node;
	char operationCode;
	char fnameDelete[13];
	char lnameDelete[13];
	//**************************************************

		// Print the Header for the output file 
	Header(outfile);

		// Read the operation code. 
	infile.get(operationCode);

		//Process the operation code. 
	while (operationCode != 'Q')
	{
		switch (operationCode)
		{
		case 'A':
			infile >> ws;
			infile.getline(Node.firstName, 13);
			infile >> ws;
			infile.getline(Node.lastName, 13);
			infile >> ws;
			infile.getline(Node.streetAddress, 21);
			infile >> ws;
			infile.getline(Node.city, 13);
			infile >> ws;
			infile.getline(Node.state, 3);
			infile >> ws;
			infile.getline(Node.zipCode, 6);
			Mailers.addRecord(outfile, Node);
			break;
		case 'D':
			infile >> ws;
			infile.getline(fnameDelete, 13);
			infile >> ws;
			infile.getline(lnameDelete, 13);
			Node = Mailers.deleteRecord(outfile, fnameDelete, lnameDelete, Node);
			break;
		case 'C':
			Mailers.changeRecord(infile, outfile, Node);
			break;
		case 'P':
			Mailers.printRecords(outfile);
			break;
		}
		infile.get(operationCode);
	
	}

		//Print the footer for the output file. 
	Footer(outfile);

	//*******************************************************

		// Close the Output file. 
	outfile.close();
	return 0;
}
//***************************************************************

LinkedList::LinkedList()
{
	// Given: Nothing. 
	// Task: initialize the starting pointer to null 
	// Returns: Nothing

	startPtr = NULL;
}

//***************************************************************

void LinkedList::addRecord(ofstream &outfile, NodeType Node)
{
	// Given: The Node and the output file 
	// Task: Add the Node to the list 
	// Returns: The output file by reference and the updated list

	NodeType *NewPtr, *PreviousPtr, *CurrentPtr;

	NewPtr = new (NodeType);

	if (NewPtr == NULL)
	{
		cout << "Node" << " Not inserted.No memory available." << endl;
	}
	else
	{

		strcpy_s(NewPtr->firstName, Node.firstName);
		strcpy_s(NewPtr->lastName, Node.lastName);
		strcpy_s(NewPtr->streetAddress, Node.streetAddress);
		strcpy_s(NewPtr->city, Node.city);
		strcpy_s(NewPtr->state, Node.state);
		strcpy_s(NewPtr->zipCode, Node.zipCode);


		NewPtr->next = Node.next;

		PreviousPtr = NULL;
		CurrentPtr = startPtr;

		while (CurrentPtr != NULL && strcmp(NewPtr->lastName, CurrentPtr->lastName) > 0)
		{
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next;
		}

		while ((CurrentPtr != NULL) && strcmp(NewPtr->lastName, CurrentPtr->lastName) == 0 ) 
		{
			if (strcmp(NewPtr->firstName, CurrentPtr->firstName) == 0)
			{
				outfile << CurrentPtr->firstName << CurrentPtr->lastName
					<< "already in the list. Attempt to add duplicate record failed!" << endl;
			} 
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next; 
		}

		if (PreviousPtr == NULL)
		{
			NewPtr->next = startPtr;
			startPtr = NewPtr;
		}
		else
		{
			PreviousPtr->next = NewPtr;
			NewPtr->next = CurrentPtr;
		}
	}
}

//********************************************************************

NodeType LinkedList::deleteRecord(ofstream &outfile, char fname[13], char lname[13], NodeType Node)
{
	// Given: The output file, the first and last names for deletion and the Node. 
	// Task: Remove the Node from the list 
	// Returns: The Node deleted from the list and the updated list

	NodeType *tempPtr, *PreviousPtr, *CurrentPtr;

	if (strcmp(startPtr->lastName, lname) == 0)
	{
		tempPtr = startPtr;
		startPtr = startPtr->next;
		delete (tempPtr);
		return Node;
	}
	else
	{
		PreviousPtr = startPtr;
		CurrentPtr = startPtr->next;


		while ((CurrentPtr != NULL) && strcmp(CurrentPtr->lastName, lname) != 0)
		{
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next;
		}
		while ((CurrentPtr != NULL) && strcmp(CurrentPtr->firstName, fname) != 0)
		{
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next;
		}


		if (CurrentPtr != NULL)
		{
			tempPtr = CurrentPtr;
			PreviousPtr->next = CurrentPtr->next;
			delete (tempPtr);
			return Node;
		}
		else
		{
			outfile << "Record of " << fname << lname << " not found. Attempt to delete record failed!" << endl;
		}
	}

	return Node;

}

//***********************************************************************

void LinkedList::changeRecord(ifstream &infile, ofstream &outfile, NodeType node)
{
	// Given: The input file, output file and the Node. 
	// Task: change the requested information
	// Returns: The input file, output file and updated list. 

	NodeType *tempPtr, *PreviousPtr, *CurrentPtr;
	char fname[13];
	char lname[13];
	int fieldNum = 0;
	bool foundCustomer;

	char newfname[13];
	char newlname[13];
	char newStreetAdd[21];
	char newcity[3];
	char newstate[3];
	char newZipCode[6];

	infile >> fname; 
	infile >> lname; 
	infile >> fieldNum;

	CurrentPtr = startPtr;

	while ((CurrentPtr != NULL) && strcmp(CurrentPtr->lastName, lname) != 0)
	{
		if (strcmp(CurrentPtr->firstName, fname) == 0 && strcmp(CurrentPtr->lastName, lname) == 0)
		{
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next;
			foundCustomer = true;
		}
		else
		{
			foundCustomer = false;
		}
		CurrentPtr = CurrentPtr->next;
	}

	if (foundCustomer)
	{
		switch (fieldNum)
		{
		case 1:
			infile >> ws;
			infile.getline(newfname, 13);
			strcpy_s(fname, newfname); 
			break;
		case 2:
			infile >> ws;
			infile.getline(newlname, 13);
			strcpy_s(lname, newlname); 
			break;
		case 3:
			infile >> ws;
			infile.getline(newStreetAdd, 13);
			strcpy_s(CurrentPtr->streetAddress, newStreetAdd);

			break;
		case 4:
			infile >> ws;
			infile.getline(newcity, 13);
			strcpy_s(CurrentPtr->city, newcity);

			break;
		case 5:
			infile >> ws;
			infile.getline(newstate, 13);
			strcpy_s(CurrentPtr->state, newstate);

			break;
		case 6:
			infile >> ws;
			infile.getline(newZipCode, 13);
			strcpy_s(CurrentPtr->zipCode, newZipCode);
			break;
		}
	}
	else
	{
		outfile << "Attempt to change non existent record! Attempt failed!" << endl << endl << endl;
	}



}

//**********************************************************************

void LinkedList::printRecords(ofstream &outFile)
{
	// Given: The output file 
	// Task: Print the values in the linked list 
	// Returns: The output file by reference. 

	NodeType *CurrentPtr;
	CurrentPtr = startPtr;

	if (CurrentPtr == NULL)
	{
		outFile << "List is Empty" << endl;
		return;
	}

	outFile << setw(47) << "MAILING LIST" << endl;

	outFile << "Last Name" << setw(15) << "First Name" << setw(11) << "Address"
		<< setw(18) << "City" << setw(14) << "State"
		<< setw(13) << "Zip Code" << endl;
	outFile << formatSigns << endl;

	while (CurrentPtr != NULL)
	{
		outFile << CurrentPtr->lastName << setw(15) << CurrentPtr->firstName
			<< setw(11) << CurrentPtr->streetAddress << setw(14) << CurrentPtr->city
			<< setw(5) << CurrentPtr->state << setw(13) << CurrentPtr->zipCode << endl;

		CurrentPtr = CurrentPtr->next;
	}
	outFile << endl << endl;

}

//********************************** FUNCTION HEADER *****************************
void Header(ofstream &Outfile)
{
	// Recieves - the output file
	// Task - Prints the output preamble
	// Returns - Nothing

	Outfile << setw(30) << "AkinTunde Akinyemi";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2017";
	Outfile << setw(20) << "Assignment #2" << endl;
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
