//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: ProgProject5.cpp    Assignment #5    Grade: _____              *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 24400  11                   Due Date:  November 4, 2016              *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of student records from an input   * 
//*           file into appropriate arrays. After reading in all the data into         * 
//*           appropriate arrays the program is to print a list of student names and   * 
//*           and all their test scores. After the information is printed, the         * 
//*           program is to sort the listing of students and their test scores listing * 
//*           the students in alphabetical order A to Z by last name. The program is   * 
//*           then to calculate the student's test average and determine a course      * 
//*           grade for each student using the standard 10 point spread. The program   * 
//*           is then to print the student information along with the students average * 
//*           and course grade. The course grade is to be one of the following five    * 
//*           standard letter grades of A, B, C, D or F. Using the test score average  * 
//*           as the "key", the program is then to sort the student info in the order  * 
//*           of highest test average to lowest test average. The program is then to   * 
//*           print a final list of the students, their test scores, average's and     * 
//*           course grade.                                                            * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*       readData -         reads all of the student names and test scores from the   *
//*				             input file into arrays                                    *
//*                            												           *
//*		  printArrays -      prints five arrays to the output file, those being the    * 
//*                          student's first and last names, the student scores, the   * 
//*                          student test averages and the student course grades.      * 
//*																			           *
//*       sortByName -       sorts the student records based on last names from        *
//*                          A to Z.                                                   *  
//*		                                                                               *
//*      calculateAverages - calculates the test average for each student.             *
//*                                                                                    * 
//*      sortByAverage -     sorts the student records based on test averages          * 
//*                          from highest to lowest                                    * 
//*																			           *
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#define sentinel "No            " 

using namespace std;

void readData(ifstream &infile, char *firstNames[], char *lastNames[], float studentScores[50][4],
	int &EU, int &REU, int &CEU);

void printArrays(ofstream &outFile, bool &hasTestAverages, char *firstNames[], char *lastNames[],
	char courseGrades[], float testAverages[], float studentScores[50][4], int &EU, int &REU, int &CEU);

void sortByName(char *firstNames[], char *lastNames[], float studentScores[50][4],
	int &EU, int &REU, int &CEU);

void calculateAverages(bool &hasTestAverages, float testAverages[],
	float studentScores[50][4], int &REU, int &CEU);

void sortByAverage(char *firstNames[], char *lastNames[], float studentScores[50][4], float testAverages[],
	int &REU, int &CEU);

void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);

int main()
{
	ifstream inFile("DATA5.TXT", ios::in); // Open the Input File. 
	ofstream outFile("RESULTS.TXT", ios::out); // Create the Output File. 
	outFile.setf(ios::fixed); // Set preciscion of Output File. 

	int REU = 0; int CEU = 0; int EU = 0;
	char *firstNames[50] = { 0 };
	char *lastNames[50] = { 0 };
	bool hasTestAverages = false;
	float studentScores[50][4];
	float testAverages[50];
	char courseGrades[] = { 'A', 'B', 'C', 'D', 'F' };
	char lines[] = "--------";
	//**************************************************

		//Print the Header for the output file. 
	Header(outFile);

		// Read the student records. 
	readData(inFile, firstNames, lastNames, studentScores, EU, REU, CEU);

		// Print labels for the student records.  
	outFile << setw(2) << "The original student data is:" << endl;
	outFile << "    Student Name" << endl;
	outFile << setw(5) << "First" << setw(13) << "Last" << setw(22) << "Test 1" << setw(11) << "Test 2"
		<< setw(11) << "Test 3" << setw(11) << "Test 4" << endl;
	outFile << setw(5) << lines << setw(14) << lines << setw(19) << lines << setw(11)
		<< lines << setw(11) << lines << setw(11) << lines << endl;

		//Print the orginal student records. 
	printArrays(outFile, hasTestAverages, firstNames, lastNames, courseGrades,
		testAverages, studentScores, EU, REU, CEU);

		// Sort student records from A to Z based on last name. 
	sortByName(firstNames, lastNames, studentScores, EU, REU, CEU);

		// Print labels for newly sorted student records. 
	outFile << setw(2) << "The list of students sorted A thru Z by Last Name is:" << endl;
	outFile << "    Student Name" << endl;
	outFile << setw(5) << "First" << setw(13) << "Last" << setw(22) << "Test 1" << setw(11) << "Test 2"
		<< setw(11) << "Test 3" << setw(11) << "Test 4" << endl;
	outFile << setw(5) << lines << setw(14) << lines << setw(19) << lines << setw(11)
		<< lines << setw(11) << lines << setw(11) << lines << endl;

		// Print the student records now A to Z based on last name.  
	printArrays(outFile, hasTestAverages, firstNames, lastNames, courseGrades,
		testAverages, studentScores, EU, REU, CEU);

		// Calculate the average test score for each student. 
	calculateAverages(hasTestAverages, testAverages, studentScores, REU, CEU);

		// Print labels for student records, now with test averages and course grades.
	outFile << setw(2) << "The list of students with their test average and course grade is:" << endl;
	outFile << "    Student Name" << endl;
	outFile << setw(5) << "First" << setw(13) << "Last" << setw(22) << "Test 1" << setw(11) << "Test 2"
		<< setw(11) << "Test 3" << setw(11) << "Test 4" << setw(12) << "Average"
		<< setw(9) << "Grade" << endl;
	outFile << setw(5) << lines << setw(14) << lines << setw(19) << lines
		<< setw(11) << lines << setw(11) << lines << setw(11) << lines
		<< setw(11) << lines << setw(11) << lines << endl;

		// Print the student records now with averages and course grades. 
	printArrays(outFile, hasTestAverages, firstNames, lastNames, courseGrades,
		testAverages, studentScores, EU, REU, CEU);

		// Sort student records from high to low based on test averages. 
	sortByAverage(firstNames, lastNames, studentScores, testAverages, REU, CEU);

		// Print labels for student records, now sorted by test averages. 
	outFile << setw(2) << "The list of students sorted by test average high to low is:" << endl;
	outFile << "    Student Name" << endl;
	outFile << setw(5) << "First" << setw(13) << "Last" << setw(22) << "Test 1" << setw(11) << "Test 2"
		<< setw(11) << "Test 3" << setw(11) << "Test 4" << setw(12) << "Average"
		<< setw(9) << "Grade" << endl;
	outFile << setw(5) << lines << setw(14) << lines << setw(19) << lines
		<< setw(11) << lines << setw(11) << lines << setw(11) << lines
		<< setw(11) << lines << setw(11) << lines << endl;

		// Print newly sorted by test average student records
	printArrays(outFile, hasTestAverages, firstNames, lastNames, courseGrades,
		testAverages, studentScores, EU, REU, CEU);

		//Print the footer for the output file. 
	Footer(outFile);

	//**************************************************

		// Close the Output file. 
	outFile.close();
	
	return 0;
}

//**************************************************************

void readData(ifstream &infile, char *firstNames[], char *lastNames[], float studentScores[50][4],
	int &EU, int &REU, int &CEU)
{
	// Given:   The input file, two array's of first names and last names, a 2D array of 
	//          student scores and the elements used in each respective array.  
	// Task:    read the data from the input file into the arrays. 
	// Returns: the input file, the two array's of first and last names, the array of student scores and the 
	//          elements used in each all by reference. 

	char *newPtr;
	char tempName[15] = { 0 };
	int MaxScores = 4;
	int i;  EU = 0;

	infile >> ws;
	infile.getline(tempName, 15);

	while (strcmp(tempName, sentinel) != 0)
	{
		newPtr = new char[15];
		strcpy(newPtr, tempName);
		firstNames[EU] = newPtr;

		infile >> ws;
		infile.getline(tempName, 15);

		newPtr = new char[15];
		strcpy(newPtr, tempName);
		lastNames[EU] = newPtr;

		for (i = 0; i < MaxScores; ++i)
		{
			infile >> studentScores[REU][i];
		}

		REU++;  EU++;
		infile >> ws;
		infile.getline(tempName, 15);
	}
	CEU = i;

}

//**************************************************************

void printArrays(ofstream &outFile, bool &hasTestAverages, char *firstNames[], char *lastNames[],
	char courseGrades[], float testAverages[], float studentScores[50][4], int &EU, int &REU, int &CEU)
{
	// Given:   The output file, a boolean for checking if averages have been calculated, two arrays of first,
	//          and last names, an array of course grades, an array of test averages, a 2D array of student
	//          scores and the elements used in the names and student score arrays.  
	// Task:    print the arrays of student names, test scores, test averages and course grades. 
	// Returns: Nothing. 

	int r, c;
	char fullNames[50];
	for (r = 0; r < EU; r++)
	{
		strcpy(fullNames, firstNames[r]);
		strcat(fullNames, lastNames[r]);
		outFile << fullNames;

		for (c = 0; c < CEU; c++)
		{
			outFile << setw(11) << setprecision(2) << studentScores[r][c];
		}

		if (hasTestAverages)
		{
			outFile << setw(11) << setprecision(2) << testAverages[r];

			if (testAverages[r] >= 90.00)
			{
				outFile << setw(9) << courseGrades[0];
			}
			else if (testAverages[r] >= 80.00 && testAverages[r] <= 89.99)
			{
				outFile << setw(9) << courseGrades[1];
			}
			else if (testAverages[r] >= 70.00 && testAverages[r] <= 79.99)
			{
				outFile << setw(9) << courseGrades[2];
			}
			else if (testAverages[r] >= 60.00 && testAverages[r] <= 69.99)
			{
				outFile << setw(9) << courseGrades[3];
			}
			else if (testAverages[r] <= 59.99)
			{
				outFile << setw(9) << courseGrades[4];
			}
		}
		outFile << endl;
	}
		// Spacing for the next section 
	outFile << endl << endl;
}

//**************************************************************


void sortByName(char *firstNames[], char *lastNames[], float studentScores[50][4], int &EU, int &REU, int &CEU)
{
	// Given:   the first and last name arrays, the array of student scores & the elements used in each.  
	// Task:    bubble sort the arrays based on last names numbers from A to Z. 
	// Returns: the two arrays of first and last names, the array of student scores and the elements
	//          used in each by reference.     

	int i, n;
	char *temp1, *temp2;  // Two temps for the two names arrays. 
	float temp3;  // Temp for the student scores array. 

	for (i = 0; i < EU - 1; i++)
	{
		for (n = EU - 1; n > i; n--)
		{
			if (strcmp(lastNames[n], lastNames[n - 1]) < 0)
			{
				temp1 = lastNames[n];
				lastNames[n] = lastNames[n - 1];
				lastNames[n - 1] = temp1;

				temp2 = firstNames[n];
				firstNames[n] = firstNames[n - 1];
				firstNames[n - 1] = temp2;

				for (int c = 0; c < CEU; c++)
				{
					temp3 = studentScores[n][c];
					studentScores[n][c] = studentScores[n - 1][c];
					studentScores[n - 1][c] = temp3;
				}
			}
		}
	}
}


//**************************************************************

void calculateAverages(bool &hasTestAverages, float testAverages[],
	float studentScores[50][4], int &REU, int &CEU)
{
	// Given    the boolean for test averages, the array of test averages, the array of student scores and 
	//          the elements used in the student scores array.  
	// Task:    calculate the test average for each student. 
	// Returns: The boolean for averages, the array of test averages, the array of students scores and the 
	//          elements used in the student scores array all by reference. 

	float totaledScores = 0;
	hasTestAverages = true;
	for (int r = 0; r < REU; r++)
	{
		totaledScores = 0;
		for (int c = 0; c < CEU; c++)
		{
			totaledScores += studentScores[r][c];
		}
		testAverages[r] = totaledScores / 4;
	}

}

//**************************************************************

void sortByAverage(char *firstNames[], char *lastNames[], float studentScores[50][4], float testAverages[],
	int &REU, int &CEU)
{
	// Given:   The arrays of first and last names, the array of student scores, the array of test averages
	//          and the elements used in the student scores array. 
	// Task:    Sort the student records from high to low based on test averages. 
	// Returns: The arrays of first and last names, the array of student scores, the array of test averages
	//          and the elements used in the student scores array all by reference. 

	float temp1;    // Averages 
	char *temp2,   // First names
	char *temp3;  // Last Names
	float temp4; // Scores

	int N, M, Max;

	for (M = 0; M < REU - 1; M++)
	{
		Max = M;
		for (N = REU - 1; N > M; N--)
		{
			if (testAverages[N] > testAverages[Max])
			{
				Max = N;
			}
		}

		temp1 = testAverages[M];
		testAverages[M] = testAverages[Max];
		testAverages[Max] = temp1;

		temp2 = firstNames[M];
		firstNames[M] = firstNames[Max];
		firstNames[Max] = temp2;

		temp3 = lastNames[M];
		lastNames[M] = lastNames[Max];
		lastNames[Max] = temp3;

		for (int c = 0; c < CEU; c++)
		{
			temp4 = studentScores[M][c];
			studentScores[M][c] = studentScores[Max][c];
			studentScores[Max][c] = temp4;
		}
	}
}


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
	Outfile << setw(20) << "Assignment #5" << endl;
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