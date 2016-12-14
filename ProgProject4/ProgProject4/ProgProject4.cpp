//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: ProgProject4.cpp    Assignment #4    Grade: _____              *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 24400  11                   Due Date:  October 21, 2016              *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of student records from an input   * 
//*           file into appropriate arrays. After reading in all the data into         * 
//*           appropriate arrays the program is to print a list of student ID          * 
//*           numbers and all their test scores. After the information is printed, the * 
//*           program is to sort the listing of studentsa nd their test scores listing * 
//*           the students in numeric order by ID Number high to low & print the list  * 
//*           again. The program is then to calculate the student's test average and   * 
//*           determine a course grade for each student using the 10 point spread.     * 
//*           program is then to print the student information along with the students * 
//*           average and course grade. The course grade is to be one of the following * 
//*           five standard letter grades of A, B, C, D or F. Using the test score     * 
//*           average as the "key", the program is then to sort the student info in    * 
//*           the order of highest test average to lowest test average. The program is * 
//*           then to print a final list of the students, their test scores, average's * 
//*           and course grade.                                                        * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*       readData -         reads all of the student ID's and test scores from the    *
//*				             input file into arrays                                    *
//*                            												           *
//*		  printArrays -      prints four arrays to the output file, those being the    * 
//*                          student ID's, the student scores, the student test        * 
//*                          averages and the student course grades.                   * 
//*																			           *
//*       sortByID -         exchange sorts the student records based on IDs from      *
//*                          highest to lowest.                                        *  
//*		                                                                               *
//*      calculateAverages - calculates the test average for each student.             *
//*                                                                                    * 
//*      sortByAverage -     exchange sorts the student records based on test averages * 
//*                          from highest to lowest                                    * 
//*																			           *
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <iostream>

using namespace std;

void readData(ifstream &inFile, int studentID[], float studentScores[50][4], 
	          int &EU, int &REU, int &CEU);

void printArrays(ofstream &outFile, bool &hasTestAverages, int studentID[], char courseGrades[], 
	             float testAverages[], float studentScores[50][4], int &EU, int &REU, int &CEU);

void sortByName(int studentID[], float studentScores[50][4], int &EU, int &REU, int &CEU);

void calculateAverages(bool &hasTestAverages, float testAverages[],
	                   float studentScores[50][4], int &REU, int &CEU);

void sortByAverage(int studentID[], float studentScores[50][4], float testAverages[], 
	               int &REU, int &CEU);

void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);

int main()
{
	ifstream inFile("DATA4.TXT", ios::in); // Open the Input File. 
	ofstream outFile("RESULTS.TXT", ios::out); // Create the Output File. 
	outFile.setf(ios::fixed); // Set preciscion of Output File. 

	int REU = 0; int CEU = 0; int EU = 0;
	bool hasTestAverages = false;
	int studentID[50];
	float studentScores[50][4];
	float testAverages[50];
	char courseGrades[] = { 'A', 'B', 'C', 'D', 'F' }; 
	char lines[] = "--------";
	//**************************************************

		//Print the Header for the output file. 
	Header(outFile);

		// Read student records. 
	readData(inFile, studentID, studentScores, EU, REU, CEU);

		// Print labels for the student records.  
	outFile << setw(2) << "The original student data is:" << endl;

	outFile << setw(8) << "StudentID" << setw(8) << "Test 1" << setw(11) << "Test 2"
		    << setw(11) << "Test 3" << setw(11) << "Test 4" << endl;

	outFile << setw(5) << lines << setw(10) << lines << setw(11) << lines << setw(11)
		    << lines << setw(11) << lines << endl;

		//Print the orginal student records. 
	printArrays(outFile, hasTestAverages, studentID, courseGrades,
		testAverages, studentScores, EU, REU, CEU);

		// Sort student records from high to low based on student IDs. 
	sortByName(studentID, studentScores, EU, REU, CEU);

		// Print labels for newly sorted student records. 
	outFile << setw(2) << "The list of students sorted by ID Number high to low is:" << endl;

	outFile << setw(8) << "StudentID" << setw(8) << "Test 1" << setw(11) << "Test 2"
	    	<< setw(11) << "Test 3" << setw(11) << "Test 4" << endl;

	outFile << setw(5) << lines << setw(10) << lines << setw(11) << lines
		    << setw(11) << lines << setw(11) << lines << endl;

		// Print the student records now high to low based on student IDs.  
	printArrays(outFile, hasTestAverages, studentID, courseGrades, 
		testAverages, studentScores, EU, REU, CEU);

		// Calculate the average test score for each student. 
	calculateAverages(hasTestAverages, testAverages, studentScores, REU, CEU); 

		// Print labels for student records, now with test averages and course grades.
	outFile << setw(2) << "The list of students with their test average and course grade is:" << endl; 
    outFile << setw(58) << "Test" << setw(13) << "Course" << endl;

	outFile << setw(8) << "StudentID" << setw(8) << "Test 1" << setw(11) << "Test 2"
		    << setw(11) << "Test 3" << setw(11) << "Test 4" << setw(11) << "Average" 
		    << setw(9) << "Grade" << endl;

	outFile << setw(5) << lines << setw(10) << lines << setw(11) << lines
		    << setw(11) << lines << setw(11) << lines << setw(11) << lines 
		    << setw(11) << lines << endl;
		
		// Print the student records now with averages and course grades. 
	printArrays(outFile, hasTestAverages, studentID, courseGrades, 
		testAverages, studentScores, EU, REU, CEU);

		// Sort student records from high to low based on test averages. 
	sortByAverage(studentID, studentScores, testAverages, REU, CEU); 

		// Print labels for student records, now sorted by test averages. 
	outFile << setw(2) << "The list of students sorted by test average high to low is:" << endl;
	outFile << setw(58) << "Test" << setw(13) << "Course" << endl;

	outFile << setw(8) << "StudentID" << setw(8) << "Test 1" << setw(11) << "Test 2"
		<< setw(11) << "Test 3" << setw(11) << "Test 4" << setw(11) << "Average"
		<< setw(9) << "Grade" << endl;

	outFile << setw(5) << lines << setw(10) << lines << setw(11) << lines
		<< setw(11) << lines << setw(11) << lines << setw(11) << lines
		<< setw(11) << lines << endl;

		// Print newly sorted by test average student records
	printArrays(outFile, hasTestAverages, studentID, courseGrades, 
		testAverages, studentScores, EU, REU, CEU);

		//Print the footer for the output file. 
	Footer(outFile);

    //**************************************************

		// Close the Output file. 
	outFile.close();

	return 0;
}

//**************************************************************

void readData(ifstream &infile, int studentID[], float studentScores[50][4],
	          int &EU, int &REU, int &CEU)
{
	// Given:   The input file, an array of studentIDs, a 2D array of student scores and the
	//          elements used in each respective array.  
	// Task:    read the data from the input file into the two arrays. 
	// Returns: the input file, the array of ID's, the array of student scores and the 
	//          elements used in each all by reference. 

	float  Num1;
	int i; int MaxScores = 4; REU = 0;
	infile >> Num1;
	while (Num1 > 0)
	{
		CEU = 0;
		studentID[EU] = Num1;
		for (i = 0; i < MaxScores; ++i)
		{
			infile >> studentScores[REU][i];
		}
		REU++; EU++;
		infile >> Num1;
	}
	CEU = i;
	return;
}

//**************************************************************

void printArrays(ofstream &outFile, bool &hasTestAverages, int studentID[], char courseGrades[], 
	             float testAverages[], float studentScores[50][4], int &EU, int &REU, int &CEU)
{
	// Given:   The output file, a boolean for checking if the averages have been calculated, an array of studentIDs,
	//          an array of course grades, an array of test averages, a 2D array of student scores, and the
	//          elements used in the ID and student score arrays.  
	// Task:    print the arrays of student ID's, test scores, test averages and course grades. 
	// Returns: Nothing. 

	int r, c;
	for (r = 0; r < EU; r++)
	{
		outFile << studentID[r];

		for (c = 0; c < CEU; c++)
		{
			outFile << setw(11) << setprecision(1) << studentScores[r][c];
		}

		if (hasTestAverages)
		{
			outFile << setw(11) << setprecision(2) << testAverages[r];

			if (testAverages[r] >= 90.00)
			{
				outFile << setw(10) << courseGrades[0];
			}
			else if (testAverages[r] >= 80.00 && testAverages[r] <= 89.99)
			{
				outFile << setw(10) << courseGrades[1];
			}
			else if (testAverages[r] >= 70.00 && testAverages[r] <= 79.99)
			{
				outFile << setw(10) << courseGrades[2];
			}
			else if (testAverages[r] >= 60.00 && testAverages[r] <= 69.99)
			{
				outFile << setw(10) << courseGrades[3];
			}
			else if (testAverages[r] <= 59.99)
			{
				outFile << setw(10) << courseGrades[4];
			}
		}
		outFile << endl;
	}
		// Spacing for the next section 
	outFile << endl << endl;
}

//**************************************************************


void sortByName(int studentID[], float studentScores[50][4], int &EU, int &REU, int &CEU)
{
	// Given:   the array of student IDs, the array of student scores & the elements used in each.  
	// Task:    exchange sort the arrays based on student ID numbers from high to low. 
	// Returns: the two arrays of ID's and scores and the elements used in each by reference.

	float temp, temp2; // Two temps for the two parallel arrays. 
	int N, M, Max;

	for (M = 0; M < EU - 1; M++)
	{
		Max = M;
		for (N = EU - 1; N > M; N--)
		{
			if (studentID[N] > studentID[Max])
			{
				Max = N;
			}
		}

		temp = studentID[M];
		studentID[M] = studentID[Max];
		studentID[Max] = temp;

		for (int c = 0; c < CEU; c++)
		{
			temp2 = studentScores[M][c];
			studentScores[M][c] = studentScores[Max][c];
			studentScores[Max][c] = temp2;
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

void sortByAverage(int studentID[], float studentScores[50][4], float testAverages[], int &REU, int &CEU)
{
	// Given:   The array of studentID's, the array of student scores, the array of test averages
	//          and the elements used in the student scores array. 
	// Task:    Sort the student records from high to low based on test averages. 
	// Returns: The array of student IDs, the array of student scores, the array of test averages
	//          and the elements used in the studetn scores array all by reference. 

	float temp, temp2, temp3; // Three temps for the 3 parallel arrays. 
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

		temp = testAverages[M];
		testAverages[M] = testAverages[Max];
		testAverages[Max] = temp;

		temp2 = studentID[M];
		studentID[M] = studentID[Max];
		studentID[Max] = temp2;
		
		for (int c = 0; c < CEU; c++)
		{
			temp3 = studentScores[M][c];
			studentScores[M][c] = studentScores[Max][c];
			studentScores[Max][c] = temp3;
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
	Outfile << setw(20) << "Assignment #4" << endl;
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