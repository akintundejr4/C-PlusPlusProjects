//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: DsProject3.cpp    Assignment #3    Grade: _____                *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 3600                        Due Date:  February 22nd, 2017           *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of customer  records to simulate a * 
//*           grocery store checkout line. The program will deal with adding, deleting * 
//*           and printing informaion about the customers.                             * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*      IsEmpty -    checks if the list is empty                                      *
//*                            												           *
//*		 IsFull  -    checks if the list is full.                                      * 
//*																			           *
//*      First   -    returns the front node.                                          *
//*		                                                                               *
//*      Last    -    returns the rear node.                                           *
//*                                                                                    * 
//*      Add     -    adds a node to the list                                          *
//*                                                                                    * 
//*      Remove  -    removes a node from the list                                     *
//*                                                                                    * 
//*      getProcessTime - gets the total processing time for a line                    * 
//*                                                                                    * 
//*      PrintQ  -    Prints the arrival and departure lists                           * 
//*                                                                                    * 
//*                                                                                    * 
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <iostream>

#define formatSigns "================================================================================"


using namespace std;

struct NodeType
{
	int arrivalTime;
	char customerName[21];
	int processingTime;

	NodeType *next;
};

class QueueClass
{
public:
	QueueClass();
	~QueueClass();
	bool IsEmpty() { return ((front == NULL) ? true : false); }
	bool IsFull();
	NodeType *First();
	NodeType *Last();
	bool Add(NodeType Node);
	bool Remove(NodeType &Node);
	int getProcessTime();

private:
	int count;
	NodeType *front;
	NodeType *rear;
};

void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);
void PrintQ(ofstream &outfile, QueueClass &List1, QueueClass &List2);

int main()
{
	ifstream infile("queue_in.TXT", ios::in); // Open the Input File. 
	ofstream outfile("RESULTS.TXT", ios::out); // Create the Output File. 
	outfile.setf(ios::fixed); // Set preciscion of Output File. 


	NodeType Node;
	QueueClass Line1, Line2, Line3;
	QueueClass arrivalList;
	QueueClass departureList;
	bool wasEmpty = false;
	int procTime1;   // Total processing times. 
	int procTime2;
	int procTime3;
	int currentTime = 1;

	//**************************************************

		// Print the Header for the output file 
	Header(outfile);

		// Read in the data. 
	infile >> Node.arrivalTime;
	infile >> ws;
	infile.getline(Node.customerName, 21);
	infile >> Node.processingTime;

		// Run the grocery simulation while the store is not closed. 
	while (Node.arrivalTime != -99)
	{
		arrivalList.Add(Node);

		if (Line1.IsEmpty())
		{
			Line1.Add(Node);
			wasEmpty = true;
		}
		else if (Line2.IsEmpty())
		{
			Line2.Add(Node);
			wasEmpty = true;

		}
		else if (Line3.IsEmpty())
		{
			Line3.Add(Node);
			wasEmpty = true;
		}

		if (!wasEmpty)
		{
			while (currentTime <= Node.arrivalTime)
			{
				if (currentTime == Node.arrivalTime)
				{
					procTime1 = Line1.getProcessTime();
					procTime2 = Line2.getProcessTime();
					procTime3 = Line3.getProcessTime();

					if (procTime1 < procTime2 && procTime1 < procTime3)
					{
						Line1.Add(Node);
					}
					else if (procTime2 < procTime1 && procTime2 < procTime3)
					{
						Line2.Add(Node);
					}
					else if (procTime3 < procTime1 && procTime3 < procTime2)
					{
						Line3.Add(Node);
					}
					else if (procTime1 == procTime2)
					{
						Line1.Add(Node);
					}
					else if (procTime1 == procTime3)
					{
						Line1.Add(Node);
					}
					else if (procTime2 == procTime3)
					{
						Line2.Add(Node);
					}
				}

				NodeType *front1 = Line1.First();
				NodeType *front2 = Line2.First();
				NodeType *front3 = Line3.First();

				while (front1 != NULL)
				{
					if (currentTime == front1->arrivalTime + front1->processingTime)
					{
						departureList.Add(*front1);

						Line1.Remove(*front1);
						break;
					}
					front1 = front1->next;
				}
				while (front2 != NULL)
				{
					
					if (currentTime == front2->arrivalTime + front2->processingTime)
					{
						departureList.Add(*front2);
						Line2.Remove(*front2);
						break;
					}
					front2 = front2->next;
				}

				while (front3 != NULL)
				{
					if (currentTime == front3->arrivalTime + front3->processingTime)
					{
						departureList.Add(*front3);
						Line3.Remove(*front3);
						break;
					}
					front3 = front3->next;
				}
				currentTime++;
			}

		}
		infile >> Node.arrivalTime;
		infile >> ws;
		infile.getline(Node.customerName, 21);
		infile >> Node.processingTime;
		wasEmpty = false;
	}


		// Print the arrival and departure lists with headings. 
	outfile << "The Order of Customer Arrival Is" << setw(70) << "The Order of Customer Departure Is" << endl; 
	outfile << formatSigns  << setw(20) << formatSigns << endl; 
	PrintQ(outfile, arrivalList, departureList);


		//Print the footer for the output file. 
	Footer(outfile);

	//*******************************************************

		// Close the Output file. 
	outfile.close();
	return 0;
}
//***************************************************************

QueueClass::QueueClass()
{
	// Given: Nothing. 
	// Task: initialize the front & rear pointers to null and count pointer to zero
	// Returns: Nothing

	front = NULL;
	rear = NULL;
	count = 0;

}

//***************************************************************

QueueClass::~QueueClass()
{
	// Given: Nothing. 
	// Task: serve as a destructor to the Queue Class 
	// Returns: Nothing

	NodeType *next;
	while (front != NULL)
	{
		next = front->next;
		delete front;
		front = next;
	}
}

//***************************************************************

bool QueueClass::IsFull()
{
	// Given: Nothing 
	// Task: Determine if the list is full. 
	// Returns: A boolean indicating if the list is full or not. 

	NodeType  *p;
	p = new (NodeType);

	if (p == NULL)
	{
		delete p;
		cout << "Out of Memory. " << endl;
		return true;
	}
	return false;
}

//***************************************************************

NodeType * QueueClass::First()
{
	// Given: Nothing 
	// Task: Return the front node. 
	// Returns: The front node in the list. 

	if (IsEmpty())
	{
		cout << "Queue is Empty. " << endl;
		return NULL;
	}
	return front;

}
//***************************************************************

NodeType * QueueClass::Last()
{
	// Given: Nothing
	// Task: Return the rear node. 
	// Returns: The rear node in the list. 

	if (IsEmpty())
	{
		cout << "Queue is Empty. " << endl;
		return NULL;
	}
	return rear;

}
//***************************************************************


bool QueueClass::Add(NodeType Node)
{
	// Given: The Node to add to the list. 
	// Task: Add the Node to the list 
	// Returns: A boolean for success or failure of addition. 

	NodeType *NewPtr;

	NewPtr = new (NodeType);
	NewPtr->processingTime = Node.processingTime;
	NewPtr->arrivalTime = Node.arrivalTime;
	strcpy_s(NewPtr->customerName, Node.customerName);
	NewPtr->next = 0;

	if (IsFull())
	{
		return false;
	}

	if (front == NULL)
	{
		front = NewPtr;
	}
	else
	{
		rear->next = NewPtr;  
	}

	rear = NewPtr;;
	count++;
	return true;

}

//********************************************************************

bool QueueClass::Remove(NodeType &Node)
{
	// Given: The Node to remove. 
	// Task: Remove the Node from the list 
	// Returns: A boolean for failed or succeded deletion and the Node 
	//          by reference. 

	NodeType *temp;

	if (IsEmpty())
	{
		return false;
	}

	Node.processingTime = front->processingTime;
	Node.arrivalTime = front->arrivalTime;
	strcpy_s(Node.customerName, front->customerName);
	count--;

	temp = front;
	front = front->next;
	delete temp;

	return true;

}

//***********************************************************************


void PrintQ(ofstream &outfile, QueueClass &List1, QueueClass &List2)
{
	// Given: The output file, the arrival list and the departure list. 
	// Task: Print the lists
	// Returns: the arrival and departure lists by reference. 

	NodeType *current1, *current2;

	current1 = List1.First();
	current2 = List2.First(); 

	if (current1 == NULL || current2 == NULL)
	{
		outfile << "There is no list to print. "
			<< endl;
	} 
	else
	{
		while (current1 != NULL && current2 != NULL)
		{
			outfile << setw(27) << current1->customerName << setw(27) 
				    << current2->customerName << endl; 
			current1 = current1->next;
			current2 = current2->next;

		}
	}

}

//***********************************************************************

int QueueClass::getProcessTime()
{
	// Given: Nothing
	// Task: Calculate the total process time per checkout line. 
	// Returns: The total process time per checkout line.  

	int processTime = 0;

	NodeType *CurrentPtr;
	CurrentPtr = front;

	while (CurrentPtr != NULL)
	{
		processTime += CurrentPtr->processingTime;
		CurrentPtr = CurrentPtr->next;
	}

	return processTime;
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
	Outfile << setw(20) << "Assignment #3" << endl;
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