//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: DSProject1.cpp    Assignment #1    Grade: _____                *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 3600                        Due Date:  January 24, 2017              *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of airline passenger records from  * 
//*           an input file into appropriate arrays. After reading in all the data into* 
//*           appropriate arrays the program assigns seating to passengers taking into * 
//*           account thier requested seating and if such is unavaible, the next       * 
//*           viable option.                                                           * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*       readData -         readss all of the passenger info and store it in an       *
//*				             array of passenger details.                               *
//*                            												           *
//*		  seperateByFlight - seperates all airline customers by the flight they have   * 
//*                          requsted and stores those passenger's details in seperate * 
//*                          arrays for each flight                                    * 
//*																			           *
//*       assignSeating -    assigns the seating for a flight by considering each      *
//*                          passengers requested section and seat as well as the      * 
//*                          actual availiblity of seats on the flight. Passengers     * 
//*                          who cannot be seated are placed on a waiting list         *
//*		                                                                               *
//*      print         -     prints the seating chart for each flight                  *
//*                                                                                    * 
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#define sentinel -999

using namespace std;

struct PassengerInfo
{
	int boardingNumber;
	int flightNumber;
	char reqSection;
	int reqRowNumber;
	char reqSeatColumn;
};

struct WaitingLists
{
	int list1010[50];
	int list1020[50];
	int list1030[50];
	int list1040[50];
	int list1015[50];
	int list1025[50];
	int list1035[50];
	int list1045[50];
};

struct ElementsUsed
{
	int numFlight1010 = 0;
	int numFlight1020 = 0;
	int numFlight1030 = 0;
	int numFlight1040 = 0;
	int numFlight1015 = 0;
	int numFlight1025 = 0;
	int numFlight1035 = 0;
	int numFlight1045 = 0;

	int waitingList1010 = 0;
	int waitingList1020 = 0;
	int waitingList1030 = 0;
	int waitingList1040 = 0;
	int waitingList1015 = 0;
	int waitingList1025 = 0;
	int waitingList1035 = 0;
	int waitingList1045 = 0;
};

struct FlightNumbers
{
	PassengerInfo flight1010[100];
	PassengerInfo flight1020[100];
	PassengerInfo flight1030[100];
	PassengerInfo flight1040[100];
	PassengerInfo flight1015[100];
	PassengerInfo flight1025[100];
	PassengerInfo flight1035[100];
	PassengerInfo flight1045[100];
};


void readData(ifstream &infile, PassengerInfo passengerDetails[], int &EU);

void seperateByFlight(FlightNumbers &passengersByFlight, PassengerInfo passengerDetails[],
	ElementsUsed &usedElements, int &EU);

void assignSeating(int seatingChart[8][10][3], PassengerInfo flightToBeSeated[],
	WaitingLists &theWaitingList, ElementsUsed &usedElements, int flightIndex, int &FEU);

void print(ofstream &outfile, int seatingChart[8][10][3], WaitingLists &theWaitingList,
	ElementsUsed &usedElements);

void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);


int main()
{
	ifstream inFile("data1.TXT", ios::in); // Open the Input File. 
	ofstream outFile("RESULTS.TXT", ios::out); // Create the Output File. 
	outFile.setf(ios::fixed); // Set preciscion of Output File. 

	FlightNumbers passengersByFlight;
	ElementsUsed usedElements;
	PassengerInfo passengerDetails[230];
	WaitingLists theWaitingList;
	int seatingChart[8][10][3];
	int EU = 0;
	//**************************************************

		// Print the Header for the output file 
	Header(outFile);

		// Intialize the seating chart to -999, denoting all intial empty seats.  
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			for (int j = 0; j < 3; j++)
			{
				seatingChart[i][k][j] = -999;
			}
		}
	}
		// Read the flight passenger records 
	readData(inFile, passengerDetails, EU);

		// Seperate the passengers by their requested flights. 
	seperateByFlight(passengersByFlight, passengerDetails, usedElements, EU);

		// Assign the seating for flight 1010
	assignSeating(seatingChart, passengersByFlight.flight1010, theWaitingList, usedElements, 0, usedElements.numFlight1010);
		// Assign the seating for flight 1020
	assignSeating(seatingChart, passengersByFlight.flight1020, theWaitingList, usedElements, 1, usedElements.numFlight1020);
		// Assign the seating for flight 1030
	assignSeating(seatingChart, passengersByFlight.flight1030, theWaitingList, usedElements, 2, usedElements.numFlight1030);
		// Assign the seating for flight 1040
	assignSeating(seatingChart, passengersByFlight.flight1040, theWaitingList, usedElements, 3, usedElements.numFlight1040);
		// Assign the seating for flight 1015
	assignSeating(seatingChart, passengersByFlight.flight1015, theWaitingList, usedElements, 4, usedElements.numFlight1015);
		// Assign the seating for flight 1025
	assignSeating(seatingChart, passengersByFlight.flight1025, theWaitingList, usedElements, 5, usedElements.numFlight1025);
		// Assign the seating for flight 1035
	assignSeating(seatingChart, passengersByFlight.flight1035, theWaitingList, usedElements, 6, usedElements.numFlight1035);
		// Assign the seating for flight 1045
	assignSeating(seatingChart, passengersByFlight.flight1045, theWaitingList, usedElements, 7, usedElements.numFlight1045);

		// Print the seating chart for each flight. 
	print(outFile, seatingChart, theWaitingList, usedElements);

		//Print the footer for the output file. 
	Footer(outFile);

	//*******************************************************

		// Close the Output file. 
	outFile.close();
	return 0;
}

void readData(ifstream &infile, PassengerInfo passengerDetails[], int &EU)
{
	// Given:   The input file, an array of PassengerDetails and it's elements used. 
	// Task:    read the data from the input file into the array. 
	// Returns: the input file, the array of passenger details and its elements used 
	//          all by reference. 

	int Num1, Num2, Num3;
	char char1, char2;

	infile >> Num1 >> Num2 >> char1 >> Num3 >> char2;

	while (Num1 != sentinel)
	{
		passengerDetails[EU].boardingNumber = Num1;
		passengerDetails[EU].flightNumber = Num2;
		passengerDetails[EU].reqSection = char1;
		passengerDetails[EU].reqRowNumber = Num3;
		passengerDetails[EU].reqSeatColumn = char2;
		EU++;
		infile >> Num1 >> Num2 >> char1 >> Num3 >> char2;
	}
}

void seperateByFlight(FlightNumbers &passengersByFlight, PassengerInfo passengerDetails[], 
	ElementsUsed &usedElements, int &EU)
{
	// Given:   The structure containing arrays for each flight, the array of passenger details, the struct holding 
	//          the used elements for each indivdual flight and the elements used in the passenger details array.  
	// Task:    seperate the passengers by requested flight. 
	// Returns: the structure of flights seperated into arrays, the array of passenger detials, the struct of 
	//          used elements and the elements used in the passenger detail array all by reference. 

	for (int t = 0; t < EU; t++)
	{
		switch (passengerDetails[t].flightNumber)
		{
		case 1010:
			passengersByFlight.flight1010[usedElements.numFlight1010++] = passengerDetails[t];
			break;
		case 1020:
			passengersByFlight.flight1020[usedElements.numFlight1020++] = passengerDetails[t];
			break;
		case 1030:
			passengersByFlight.flight1030[usedElements.numFlight1030++] = passengerDetails[t];
			break;
		case 1040:
			passengersByFlight.flight1040[usedElements.numFlight1040++] = passengerDetails[t];
			break;
		case 1015:
			passengersByFlight.flight1015[usedElements.numFlight1015++] = passengerDetails[t];
			break;
		case 1025:
			passengersByFlight.flight1025[usedElements.numFlight1025++] = passengerDetails[t];
			break;
		case 1035:
			passengersByFlight.flight1035[usedElements.numFlight1035++] = passengerDetails[t];
			break;
		case 1045:
			passengersByFlight.flight1045[usedElements.numFlight1045++] = passengerDetails[t];
			break;
		}
	}
}

void assignSeating(int seatingChart[8][10][3], PassengerInfo flightToBeSeated[], WaitingLists &theWaitingList, 
	ElementsUsed &usedElements, int flightIndex, int &FEU)
{
	// Given:   The seating chart, the array containigng the passengers of the flight to be seated, the struct 
	//          containing arrays of waiting lists, the struct that holds the used elements for each flight, 
	//          the index of the flight being seated and the actual EU of the flight to be seated. 
	// Task:    seat the passengers of the flight, if seat is unavailable, proceed to the next option. 
	// Returns: the seating chart, the array for the flight that was seated, the struct of waiting lists,  
	//          the struct of used elements, the flight index and the actually used elements of the seated 
	//          flight all by reference.  

	char reqSection = ' ';
	char reqColumn = ' ';

	int reqRow = 0;
	int transReqRow = 0;
	int transReqColumn = 0;
	int maxFirstClassRows = 3;
	int maxCoachRows = 10;
	int maxColumns = 3;

	bool wasPassengerSeated;
	bool rowIsFull;
	bool columnIsFull;
	bool sectionIsFull;

	for (int i = 0; i < FEU; i++)
	{
		reqSection = flightToBeSeated[i].reqSection;
		reqRow = flightToBeSeated[i].reqRowNumber;
		reqColumn = flightToBeSeated[i].reqSeatColumn;
		wasPassengerSeated = false;

		switch (reqRow)
		{
		case 1:
			transReqRow = 0;
			break;
		case 2:
			transReqRow = 1;
			break;
		case 3:
			transReqRow = 2;
			break;
		case 4:
			transReqRow = 3;
			break;
		case 5:
			transReqRow = 4;
			break;
		case 6:
			transReqRow = 5;
			break;
		case 7:
			transReqRow = 6;
			break;
		case 8:
			transReqRow = 7;
			break;
		case 9:
			transReqRow = 8;
			break;
		case 10:
			transReqRow = 9;
			break;

		}
		switch (reqColumn)
		{
		case 'L':
			transReqColumn = 0;
			break;
		case 'M':
			transReqColumn = 1;
			break;
		case 'R':
			transReqColumn = 2;
			break;
		}

		if (reqSection == 'F')
		{
			if (seatingChart[flightIndex][transReqRow][transReqColumn] == -999)
			{
				seatingChart[flightIndex][transReqRow][transReqColumn] = flightToBeSeated[i].boardingNumber;
				wasPassengerSeated = true;
				rowIsFull = false;
				columnIsFull = false;
				sectionIsFull = false;

			}
			else
			{
				for (int l = 0; l < maxColumns; l++)
				{
					if (seatingChart[flightIndex][transReqRow][l] == -999)
					{
						seatingChart[flightIndex][transReqRow][l] = flightToBeSeated[i].boardingNumber;
						wasPassengerSeated = true;
						rowIsFull = false;
						break;
					}
				}
				if (rowIsFull == true)
				{
					for (int n = 0; n < maxFirstClassRows; n++)
					{
						if (seatingChart[flightIndex][n][transReqColumn] == -999)
						{
							seatingChart[flightIndex][n][transReqColumn] = flightToBeSeated[i].boardingNumber;
							wasPassengerSeated = true;
							columnIsFull = false;
						}
					}
				}
				if (columnIsFull == true)
				{
					for (int n = 0; n < maxFirstClassRows; n++)
					{
						for (int p = 0; p < maxColumns; p++)
						{
							if (seatingChart[flightIndex][n][p] == -999 && sectionIsFull == true)
							{
								seatingChart[flightIndex][n][p] = flightToBeSeated[i].boardingNumber;
								sectionIsFull = false;
								wasPassengerSeated = true;
							}
						}
					}
				}
			}

		}
		else if (reqSection == 'C') 
		{
			if (seatingChart[flightIndex][transReqRow][transReqColumn] == -999)
			{
				seatingChart[flightIndex][transReqRow][transReqColumn] = flightToBeSeated[i].boardingNumber;
				wasPassengerSeated = true;
				rowIsFull = false;
				columnIsFull = false;
				sectionIsFull = false;

			}
			else 
			{
				for (int l = 0; l < maxColumns; l++)
				{
					if (seatingChart[flightIndex][transReqRow][l] == -999)
					{
						seatingChart[flightIndex][transReqRow][l] = flightToBeSeated[i].boardingNumber;
						wasPassengerSeated = true;
						rowIsFull = false;
						break;
					}
				}

				if (rowIsFull == true)
				{
					for (int n = 3; n < maxCoachRows; n++)
					{
						if (seatingChart[flightIndex][n][transReqColumn] == -999)
						{
							seatingChart[flightIndex][n][transReqColumn] = flightToBeSeated[i].boardingNumber;
							columnIsFull = false;
							wasPassengerSeated = true;
							break;
						}
					}
				}

				if (columnIsFull == true)
				{
					for (int n = 3; n < maxCoachRows; n++)
					{
						for (int p = 0; p < maxColumns; p++)
						{
							if (seatingChart[flightIndex][n][p] == -999 && sectionIsFull == true)
							{
								seatingChart[flightIndex][n][p] = flightToBeSeated[i].boardingNumber;
								sectionIsFull = false;
								wasPassengerSeated = true;
							}
						}
					}
				}
			}
		}

		if (wasPassengerSeated == false)
		{
			switch (flightIndex)
			{
			case 0:
				theWaitingList.list1010[usedElements.waitingList1010++] = flightToBeSeated[i].boardingNumber;
				break;
			case 1:
				theWaitingList.list1020[usedElements.waitingList1020++] = flightToBeSeated[i].boardingNumber;
				break;
			case 2:
				theWaitingList.list1030[usedElements.waitingList1030++] = flightToBeSeated[i].boardingNumber;
				break;
			case 3:
				theWaitingList.list1040[usedElements.waitingList1040++] = flightToBeSeated[i].boardingNumber;
				break;
			case 4:
				theWaitingList.list1015[usedElements.waitingList1015++] = flightToBeSeated[i].boardingNumber;
				break;
			case 5:
				theWaitingList.list1025[usedElements.waitingList1025++] = flightToBeSeated[i].boardingNumber;
				break;
			case 6:
				theWaitingList.list1035[usedElements.waitingList1035++] = flightToBeSeated[i].boardingNumber;
				break;
			case 7:
				theWaitingList.list1045[usedElements.waitingList1045++] = flightToBeSeated[i].boardingNumber;
				break;
			}
		}


	}
}


void print(ofstream &outfile, int seatingChart[8][10][3], WaitingLists &theWaitingList, 
	ElementsUsed &usedElements)
{
	// Given:   The output file, the seating chart, the struct of Waiting lists and the struct of used elements.   
	// Task:    print the seating charts for Southern Comfort Airlines. 
	// Returns: the output file, the seating chart, the struct of waitling lists and the struct of used elements
	//          all by reference. 

	for (int i = 0; i < 8; i++)
	{
		outfile << setw(40) << "Southern Comfort Airlines" << endl << endl;
		switch (i)
		{
		case 0:
			outfile << "Flight 1010" << setw(52) << "FROM: Jackson, Mississippi" << endl;
			outfile << setw(59) << "TO: Memphis, Tennessee" << endl;
			break;
		case 1:
			outfile << "Flight 1020" << setw(52) << "FROM: Jackson, Mississippi" << endl;
			outfile << setw(62) << "TO: Little Rock, Arkansas" << endl;
			break;
		case 2:
			outfile << "Flight 1030" << setw(52) << "FROM: Jackson, Mississippi" << endl;
			outfile << setw(62) << "TO: Shreveport, Louisiana" << endl;
			break;
		case 3:
			outfile << "Flight 1040" << setw(52) << "FROM: Jackson, Mississippi" << endl;
			outfile << setw(57) << "TO: Orlando, Florida" << endl;
			break;
		case 4:
			outfile << "Flight 1015" << setw(52) << "FROM: Memphis, Tennessee" << endl;
			outfile << setw(63) << "TO: Jackson, Mississippi" << endl;
			break;
		case 5:
			outfile << "Flight 1025" << setw(52) << "FROM: Little Rock, Arkansas" << endl;
			outfile << setw(60) << "TO: Jackson, Mississippi" << endl;
			break;
		case 6:
			outfile << "Flight 1035" << setw(52) << "FROM: Shreveport, Louisiana" << endl;
			outfile << setw(60) << "TO: Jackson, Mississippi" << endl;
			break;
		case 7:
			outfile << "Flight 1045" << setw(52) << "FROM: Orlando, Florida" << endl;
			outfile << setw(65) << "TO: Jackson, Mississippi" << endl;
			break;
		}

		for (int k = 0; k < 10; k++)
		{
			for (int j = 0; j < 3; j++)
			{
				outfile << setw(10) << seatingChart[i][k][j];
			}
			outfile << endl;
		}
		outfile << endl;
		switch (i)
		{
		case 0:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1010; j++)
			{
				outfile << setw(6) << theWaitingList.list1010[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1010 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl;
			}
			break;
		case 1:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1020; j++)
			{
				outfile << setw(6) << theWaitingList.list1020[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1020 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl;
			}
			break;
		case 2:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1030; j++)
			{
				outfile << setw(6) << theWaitingList.list1030[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1030 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl;
			}
			break;
		case 3:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1040; j++)
			{
				outfile << setw(6) << theWaitingList.list1040[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1040 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl << endl;
			}
			break;
		case 4:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1015; j++)
			{
				outfile << setw(6) << theWaitingList.list1015[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1015 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl << endl;
			}
			break;
		case 5:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1025; j++)
			{
				outfile << setw(6) << theWaitingList.list1025[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1025 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl;
			}
			break;
		case 6:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1035; j++)
			{
				outfile << setw(6) << theWaitingList.list1035[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1035 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl;
			}
			break;
		case 7:
			outfile << "WAITING LIST" << endl << endl;
			for (int j = 0; j < usedElements.waitingList1045; j++)
			{
				outfile << setw(6) << theWaitingList.list1045[j];
			}
			outfile << endl << endl;
			if (usedElements.waitingList1045 == 0)
			{
				outfile << "There is no waiting list for this flight" << endl;
			}
			break;
		}
		outfile << " END OF SEATING CHART" << endl << endl << endl;
		outfile << endl;
	}

}
////********************************** FUNCTION HEADER *****************************
void Header(ofstream &Outfile)
{
	// Recieves - the output file
	// Task - Prints the output preamble
	// Returns - Nothing

	Outfile << setw(30) << "AkinTunde Akinyemi";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2017";
	Outfile << setw(20) << "Assignment #1" << endl;
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