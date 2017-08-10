
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of student ID numbers              * 
//*           and test scores from an input file. After reading in all the data into   * 
//*           appropriate arrays the program is to print a list of student ID          * 
//*           numbers and scores. Then it will print a list of all students in groups  *
//*           according to the letter grade they received. Next it will find the       *
//*           highest and lowest scores and print them along with the student ID of    * 
//*           the student who recieved those respective scores. It will also compute   * 
//*           the average test score of all tests and print it out.                    * 
//*                                                                                    *
//*  User Defined                                                                      *
//*  Modules:  readData -reads all of the student ID's and test scores from the input  *
//*				         file into arrays                                              *
//*                            												           *
//*		       printArrays - prints two arrays to the output file, one of the student  * 
//*                          ID's and the other of the student scores                  * 
//*																			           *
//*            printByGrade - prints out a list of studentID #'s to the output file    *
//*                           based on their scores in the course.                     *                        
//*																			           *
//*            getLowScore - finds the lowest score of all the students and returns    * 
//*                          it                                                        * 
//*																			           *
//*			   getHighScore - finds the highest score of all the students and returns  *
//*                           it                                                       *
//*                                                                                    * 
//*            calculateAverage - calculates the average of all student scores and     *
//*                               returns it.                                          * 
//*                                                                                    * 
//*																			           *
//*                                                                                    *
//**************************************************************************************


#include <iomanip>
#include <fstream>

using namespace std;

void readData(ifstream &inFile, int studentID[], float studentScores[], int &elementsUsed);
void printArrays(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed);
void printByGrade(ofstream &outFile, int studentID[], float studentScores[], 
	int &elementsUsed, float lowRange, float highRange);
int getLowScore(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed);
int getHighScore(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed);
float calculateAverage(float studentScores[], int &elementsUsed);
void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);

int main()
{
	ifstream inFile("DATA2.TXT", ios::in); // Open the Input File. 
	ofstream outFile("RESULTS.TXT", ios::out); // Create the Output File. 
	outFile.setf(ios::fixed); // Set preciscion of Output File. 

	int elementsUsed = 0; 
	int lowestScoreLocation;
	int highestScoreLocation;
	float averageTestScore; 
	int studentID[50]; 
	float studentScores[50];

	//**************************************************
		// Create the Header for the output file. 
	Header(outFile);

		// Read Student Records into two arrays, one for ID's one for Test Scores. 
	readData(inFile, studentID, studentScores, elementsUsed);

		// Create labels for the test scores and student ID columns. 
	outFile << "The orginal list of test scores is:" << endl;
	outFile << setw(1) << "Student ID #  " << setw(15) << "Test Score" << endl;

		// Print the student ID #s and the student scores. 
	printArrays(outFile, studentID, studentScores, elementsUsed);

		// Print student ID's of A students.
	outFile << "Students receiving a grade of A are: ";
	printByGrade(outFile, studentID, studentScores, elementsUsed, 90.00, 100.04);

		// Print student ID's of B students.
	outFile << "Students receiving a grade of B are: ";
	printByGrade(outFile, studentID, studentScores, elementsUsed, 80.00, 89.99);

		// Print student ID's of C students.
	outFile << "Students receiving a grade of C are: ";
	printByGrade(outFile, studentID, studentScores, elementsUsed, 70.00, 79.99);

		// Print student ID's of D students.
	outFile << "Students receiving a grade of D are: ";
	printByGrade(outFile, studentID, studentScores, elementsUsed, 60.00, 69.99);

		// Print student ID's of F students.
	outFile << "Students receiving a grade of F are: ";
	printByGrade(outFile, studentID, studentScores, elementsUsed, 0.00, 59.99);
	outFile << endl; 

		// Get the index of the lowest score in the student scores array. 
	lowestScoreLocation = getLowScore(outFile, studentID, studentScores, elementsUsed);

		// Print out the lowest score and the corresponding student ID # with labels
	outFile << "The lowest test score was " << studentScores[lowestScoreLocation] << " achieved by student #"
		<< studentID[lowestScoreLocation] << endl << endl;

		// Get the index of the highest score in the student scores array. 
	highestScoreLocation = getHighScore(outFile, studentID, studentScores, elementsUsed);

		// Print out the highest score and the corresponding student ID # with labels
	outFile << "The highest test score was " << studentScores[highestScoreLocation] << " achieved by student #"
		<< studentID[highestScoreLocation] << endl << endl;

		// Calculate the average test score for all students in the course 
	averageTestScore = calculateAverage(studentScores, elementsUsed);

		// Print out the average test score with a label. 
	outFile << "The average test score for the group is " << averageTestScore;

		//Create the footer for the output file. 
	Footer(outFile);

	//**************************************************

		// Close the Output file. 
	outFile.close();

	return 0;
}

//**************************************************************

void readData(ifstream &inFile, int studentID[], float studentScores[], int &elementsUsed)
{
	// Given: The input file, arrays of studentIDs and scores and the # of elements in each array
	// Task:  read the data from the input file into two seperate arrays
	// Returns: the input file, two arrays of ID's and scores and the elements used all by reference. 

	int IDS;
	float Scores;
	elementsUsed = 0;

	inFile >> IDS;
	inFile >> Scores;

	while (IDS > 0 && Scores > 0)
	{
		studentID[elementsUsed] = IDS;
		studentScores[elementsUsed] = Scores;
		elementsUsed++;
		inFile >> IDS;
		inFile >> Scores;

		if (IDS == -9999)
		{
			break;
		}
	} 
}

//**************************************************************

void printArrays(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed)
{
	// Given: the output file, arrays of studentID's and scores and the elements used in the arrays. 
	// Task:  print the full contents of each array to the output file. 
	// Returns: Nothing. 

	int k;
	for (k = 0; k < elementsUsed; ++k)
	{
		outFile << setw(1) << studentID[k] << setw(20) << setprecision(2) << studentScores[k] << endl;
	}

		// Spacing for the next section 
	outFile << endl << endl;
}

//**************************************************************

void printByGrade(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed, float lowRange, float highRange)
{
	// Given: the output file, arrays of studentID's and scores, the elements used in the arrays and
	//         the low and high score range for grades. 
	// Task:  print the studentID #'s filtered by course grade. 
	// Returns: the output file, two arrays of ID's and scores and the elements used in each by reference.


	int i;
	for (i = 0; i < elementsUsed; ++i)
	{
		if (studentScores[i] >= lowRange && studentScores[i] <= highRange)
		{
				// Print out the student ID number of each student based on course grade. 
			outFile << setw(5) << studentID[i];
		}
	}

	outFile << endl; 
}

//**************************************************************

int getLowScore(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed)
{
	// Given: the output file, arrays of studentID's and scores and the elements used in the arrays.
	// Task:  find the lowest score of all the students. 
	// Returns: The lowest scores location.  The output file, 
	//          two arrays of ID's and scores and the elements used in each by reference.

	int i;
	int lowScoreLocation = 0;
	float lowestScore = studentScores[0];
	for (i = 0; i < elementsUsed; i++)
	{
		if (lowestScore > studentScores[i])
		{
			lowestScore = studentScores[i];
			lowScoreLocation = i;
		}
	}

	return lowScoreLocation;
}

//**************************************************************

int getHighScore(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed)
{
	// Given: the output file, arrays of studentID's and scores and the elements used in the arrays.
	// Task:  find the highest score of all the students. 
	// Returns: The highest scores location. The output file, 
	//          two arrays of ID's and scores and the elements used in each by reference.

	int i;
	int highestScoreLocation = 0;
	float highestScore = studentScores[0];
	for (i = 0; i < elementsUsed; i++)
	{
		if (highestScore < studentScores[i])
		{
			highestScore = studentScores[i];
			highestScoreLocation = i;
		}
	}

	return highestScoreLocation;
}

//**************************************************************

float calculateAverage(float studentScores[], int &elementsUsed)
{
	// Given: the array of student scores and the elements used in the array. 
	// Task: calculate the average of all student scores
	// Returns: The calculated average. The array of students scores and the 
	//          elements used by reference. 

	int i;
	float total = 0;
	float averageScore = 0;

	for (i = 0; i < elementsUsed; i++)
	{
			// Add up all of the Scores. 
		total += studentScores[i];
	}
		// Divide the total of all scores by the # of scores in the array. 
	averageScore = total / elementsUsed;

	return averageScore;
}

