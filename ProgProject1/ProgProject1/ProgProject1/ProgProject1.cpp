//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: ProgProject1.cpp    Assignment #1    Grade: _____              *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 24400  11                   Due Date:  February 11, 2016             *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process:  This program is designed to calculate the parking fee for               *
//*            drivers wishing to park on a university campus. It will read            *
//*            the input data for one vehicle at a time. It is then to                 *
//*            calculate the parking fee and print out a ticket for the driver		   *
//*            The program is to select the proper parking rate based on the           * 
//*            hours the vehicle is parked and calculate the parking fee for	       * 
//*            that driver. Finally it is to print the customer's parking              * 
//*            ticket														           * 
//*																			           *
//*                                                                                    *
//*  User Defined                                                                      *
//*  Modules:  readData -reads the customer's vehicle type, entry and exit times and   * 
//*                      assigns them to variables.                                    *
//*				                                                                       *
//*                                                                                    * 
//*																			           *
//*		       calculateParkingFee - calculates the parking fee for every vehicle      *
//*                                  based on the the garage's various rates and       *
//*									 duration of stay.     				               *
//*																			           *
//*             printTicket - creates and then prints to RESULTS.txt a parking ticket  * 
//*                           that includes the vehicle type, entry and exit times,    * 
//*                           the total time spent in hours and finally                * 
//*							  the amount paid.										   *
//*																			           *
//*                                                                                    *
//*																			           *
//*																			           *
//*																			           *
//*                                                                                    *
//**************************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void readData(ifstream &myFile, ofstream &outFile);
void calculateParkingFee(char &vehicleType, float &entryTime, float &exitTime, ofstream &outFile);

void printTicket(char &vehicleType, float &entryTime, float &exitTime, float &parkingFee,
	float &totalTime, ofstream &outFile);

void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);


int main()
{
	// Recieves - Nothing 

	// Task - Creates Output and Input Files and then Calls all functions needed to create the 
	// parking ticket

	// Returns - Zero

	ifstream inFile("DATA1.TXT", ios::in);
	ofstream outFile("RESULTS.TXT", ios::out);
	outFile.setf(ios::fixed);

	//**************************************************
	Header(outFile);
	readData(inFile, outFile);
	Footer(outFile);
	//**************************************************
	outFile.close();
	return 0;
}

//********************************************************

void readData(ifstream &inFile, ofstream &outFile)
{
	// Recieves - The input and output files. 
	// Task - Reads and then assigns the vehicular data for each customer to a variable. 
	//        Then calls the method that calculates the parking fee based on the type of 
	//        vehicle 
	// Returns - The input and output files by reference. 

	char vehicleType;
	float entryTime;
	float exitTime;
	while (inFile.is_open())  // Only read the data if the file is open. 
	{
		while (inFile.good())  // While the file is open without errors, read the data. 
		{
			inFile >> vehicleType;   // Assign the first, second and third lines to variables. 
			inFile >> entryTime;
			inFile >> exitTime;
			switch (vehicleType)
			{
			case 'C':   // Car 
				calculateParkingFee(vehicleType, entryTime, exitTime, outFile);
				// Calculate the parking fee for every car. 
				break;
			case 'T':   // Truck
				calculateParkingFee(vehicleType, entryTime, exitTime, outFile);
				// Calculate the parking fee for every truck. 
				break;
			case 'S':   // Senior Citizen 
				calculateParkingFee(vehicleType, entryTime, exitTime, outFile);
				// Calculate the parking fee for every senior citizen. 
				break;
			}
		}
		inFile.close();   // Close the input file. 
	}

}

char getVehicleType(char vehicleType)
{
	return vehicleType;
}

//*******************************************************************

void calculateParkingFee(char &vehicleType, float &entryTime, float &exitTime, ofstream &outFile)
{
	// Recieves - The vehicle type, the entry time, the exit time and the output file. 
	// Task - Calculates the parking fee based on the type of vehicle and when it entered and 
	// exited the parking garage. 
	// Returns - the vehicle type, entry and exit times and the output file by reference. 


	float entryTimeInHours = entryTime / 60;
	float exitTimeInHours = exitTime / 60;
	// Divided the whole minutes given in the input file by 60 to get hours. 

	float parkingFee;

	float totalTime = ceil(exitTimeInHours - entryTimeInHours);
	// this is the total time spent in the parking garage. 
   // ceil rounds up, so 1.1 would become 2. This is done because
  // every minute over the hour counts as an entire hour towards the fee. 

	switch (vehicleType)
	{
	case 'C':   // Going through each type of vehicle, Car, Truck or Senior citizen. 
		if (totalTime <= 2)
			// If the duration of the car's stay was less then or equal to 2 hours. First two hours. 
		{
			if (totalTime <= 1)   // If the customer stayed less then or exactly 1 hour. 
			{
				parkingFee = 0.20;  // The fee would only be $0.20. Based on the given rates
			}
			else
			{
				parkingFee = 0.40;
				// Else if they stayed more than 1 hour but less than or equal to 2 hours,
			   //  the fee would only be $0.40. 2*.20. 
			}
		}
		else if (totalTime > 2 && totalTime <= 5)
			// Next 3 hours. The rate increases for stays over the first two hours.
		{
			parkingFee = (totalTime - 2) * 0.15 + .40;
			// Subtract the first two hours to get an accurate total time, then
		   // multiply by the rate for the next 3. 
		  //$0.40 signifies the charge for those first two  hours. T
		}
		else if (totalTime > 5)  // If they stayed more than 5 hours the rate increases again. 
		{
			parkingFee = (totalTime - 5) * .05 + .85;
			// Subtract 5 to get an accurate total time because anything over 5 hours
		   // has a higher pay rate.  the $0.85 is the charge for those first 5 hours. 
		}
		break;
	case 'T':
		if (totalTime <= 1)  // Flat rate for all stays underneath or equal to 1 hour. 
		{
			parkingFee = 0.40;
		}
		else if (totalTime > 1 && totalTime <= 4) // Rate increases over the next 3 hours. 
		{
			parkingFee = (totalTime - 1) * 0.25 + .40;
			// Subtract the first hour for an accurate total time then 
		   // multiply by the higher rate of $0.25. 
		  // .40 signifies the charge for that first hour.  
		}
		else if (totalTime > 4)
			// Rate increases over the next 12 hours, beyond the first 4. 
		{
			parkingFee = (totalTime - 4) * .10 + .65;
			// Charged $0.10 for every hour over 4 hours. 
		}
		break;

	case 'S':
		parkingFee = totalTime * 0.12;
		// Flat fee for all senior citizens, no increases based on stay length. 
		break;
	}
	printTicket(vehicleType, entryTime, exitTime, parkingFee, totalTime, outFile);
	// Print the ticket for each vehicle. 
}

//*************************************************************
void printTicket(char &vehicleType, float &entryTime, float &exitTime, float &parkingFee, 
				 float &totalTime, ofstream &outFile)
{
	// Recieves - the vehicle type, the entry and exit times, the parking fee, the total time 
	//            and the output file. 
	// Task -     Prints the parking ticket for every vehicle in the input file DATA1. 
	// Returns -  the vehicle type, the entry and exit times, the parking fee, 
	//            the total time and the output file by reference. 


	int r, c;  // r is  for rows 
			   // c is  for columns. This is the creation of the $ border. 

	outFile << "The input data was: " << endl;
	outFile << vehicleType << " " << setprecision(1) << entryTime
		<< " " << setprecision(1) << exitTime << endl;
	outFile << endl;
	for (r = 0; r < 10; ++r)
	{
		if (r == 1)
		{
			outFile << '$' << setw(1) << setw(25) << '$' << endl;
			outFile << "$" << setw(15) << "   MISSOURI WESTERN   " << setw(3) << '$' << endl;
			outFile << '$' << setw(15) << "   UNIVERSITY   " << setw(9) << '$' << endl;
			outFile << '$' << setw(1) << setw(25) << '$' << endl;

			for (c = 0; c < 26; ++c)
			{
				// Loop that prints out a single line of dollar signs below the words 
				// "Missouri Western University". 
				outFile << "$";
			}
			outFile << endl << "$" << setw(17) << "     PARKING FEE     " << setw(4) << "$" << endl;
			outFile << setw(1) << '$' << setw(25) << '$' << endl;
			outFile << '$' << setw(10) << "Customer " << setw(15) << '$' << endl;
			switch (vehicleType)  // Every single vehicle will have its own ticket, hence the switch case. 
			{
				/**
				   this entire code block uses setw() and endlines to print the full ticket information
				   for every vehicle.  setw() is used to ensure that dollar signs and text is formatted
				   corrrectly and lined up correctly as well. Spaces are used in each title string to
				   ensure that all labels are lined up correctly and accurately spaced from the left
				   and right borders.
				**/

			case 'C':   // printing ticket for Cars. 
				outFile << '$' << setw(10) << " Category:   Car" << setw(9) << '$' << endl;
				outFile << '$' << setw(1) << setw(25) << '$' << endl;
				if (totalTime <= 9)
				{
					// if the total hours spent is only a single digit, use only 5
					// spaces on the right border.
					outFile << '$' << setw(6) << " Time:       " <<
						setprecision(0) << totalTime << " hours" << setw(5) << '$' << endl;
				}
				else
				{
					// If it is two digits, I take away a space from the right border that is not needed.
					outFile << '$' << setw(6) << " Time:       " << setprecision(0)
						<< totalTime << " hours" << setw(4) << '$' << endl;
				}
				outFile << setw(1) << '$' << setw(25) << '$' << endl;
				// A new row of $ signs to make room for the next ticket. 
				outFile << '$' << setw(8) << "Amount " << setw(17) << '$' << endl;
				outFile << '$' << setw(12) << " Paid:       $" << setprecision(2)
					<< parkingFee << setw(7) << '$' << endl;
				outFile << '$' << setw(1) << setw(25) << '$';


				break;
			case 'T':  // Printing ticket
				outFile << '$' << setw(10) << " Category:   Truck" << setw(7) << '$' << endl;
				outFile << '$' << setw(1) << setw(25) << '$' << endl;
				if (totalTime <= 9)
				{
					// if the total hours spent is only a single digit, 
					// use only 5 spaces on the right border. 
					outFile << '$' << setw(6) << " Time:       " << setprecision(0) 
						<< totalTime << " hours" << setw(5) << '$' << endl;
				}
				else
				{
					// If it is two digits, I take away a space from the right border that is not needed. 
					outFile << '$' << setw(6) << " Time:       " << setprecision(0)
						<< totalTime << " hours" << setw(3) << '$' << endl;
				}
				outFile << setw(1) << '$' << setw(25) << '$' << endl;
				outFile << '$' << setw(8) << "Amount " << setw(17) << '$' << endl;
				outFile << '$' << setw(12) << " Paid:       $" << setprecision(2) 
					<< parkingFee << setw(7) << '$' << endl;
				outFile << '$' << setw(1) << setw(25) << '$';
				break;
			case 'S':  // Printing ticket for Senior Citizens. 
				outFile << '$' << setw(10) << " Category:   SC" << setw(10) << '$' << endl;
				outFile << '$' << setw(1) << setw(25) << '$' << endl;
				if (totalTime <= 9)
				{
					outFile << '$' << setw(6) << " Time:       " << 
						setprecision(0) << totalTime << " hours" << setw(5) << '$' << endl;
				}
				else
				{
					outFile << '$' << setw(6) << " Time:       " << 
						setprecision(0) << totalTime << " hours" << setw(4) << '$' << endl;
				}
				outFile << setw(1) << '$' << setw(25) << '$' << endl;
				outFile << '$' << setw(8) << "Amount " << setw(17) << '$' << endl;
				outFile << '$' << setw(12) << " Paid:     $" << 
					setprecision(2) << parkingFee << setw(9) << '$' << endl;
				outFile << '$' << setw(1) << setw(25) << '$';
				break;
			}
			outFile << endl;
		}

		for (c = 0; c < 26; ++c)   // 25 dollar signs across the top and bottom rows. 
		{
			if (r == 0 || r == 9)
			{
				outFile << "$";    // initially, 9 dollar signs on the left border. 
			}
			else
			{
				if (c == 0 || c == 9)
					outFile << "$";   // 9 dollar signs on the right border 
				else
					outFile << "   ";    // Print the spaces in between the left and right borders. 
			}
		}
		outFile << endl;
	}
	outFile << endl << endl;   // Giving space for each ticket to be seperated from one another. 

}

//********************************** FUNCTION HEADER *********************************
void Header(ofstream &Outfile)
{
	// Recieves - the output file
	// Task - Prints the output preamble
	// Returns - Nothing

	Outfile << setw(30) << "AkinTunde Akinyemi";
	Outfile << setw(17) << "CSC 24400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Fall 2016";
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