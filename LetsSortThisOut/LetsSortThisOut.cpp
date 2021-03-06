
//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads  an unknown number of student ID numbers              * 
//*           and test scores from an input file. After reading in all the data into   * 
//*           appropriate arrays the program is to print a list of student ID          * 
//*           numbers and scores. After the arrays are printed, the program is to sort * 
//*           the listing of both arrays based on test scores from high to low and     *
//*           print the sorted arrays a second time. Then the program is to sort both  * 
//*           lists from low to high based on student ID number and print both lists.  * 
//*           Finallly, the program finds the lowest & highest scores and who recieved * 
//*           them and also finds the average score for all tests and prints them.     *
//*                                                                                    *
//*  User Defined                                                                      *
//*  Modules:  readData -reads all of the student ID's and test scores from the input  *
//*				         file into arrays                                              *
//*                            												           *
//*		       printArrays - prints two arrays to the output file, one of the student  * 
//*                          ID's and the other of the student scores                  * 
//*																			           *
//*            bubbleSort -  bubble sorts a list of studentID #'s and test scores      *
//*                          based on the test scores from high to low.                *                        
//*		                                                                               *
//*            exchangeSort -exchange sorts a list of studentID #'s and test scores    *
//*                          based on student ID #'s from low to high.                 * 
//*                                                                                    * 
//*                                                                                    * 
//*            getLowScore - finds the lowest score of all the students and returns    * 
//*                          it's index in the array.                                  * 
//*																			           *
//*			   getHighScore - finds the highest score of all the students and returns  *
//*                           it's index in the array.                                 *
//*                                                                                    * 
//*            calculateAverage - calculates the average of all student scores and     *
//*                               returns it.                                          * 
//*                                                                                    * 
//*																			           *
//*                                                                                    *
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>

using namespace std;

void readData(ifstream &inFile, int studentID[], float studentScores[], int &elementsUsed);
void printArrays(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed);
void bubbleSort(int studentID[], float studentScores[],int &elementsUsed);
void exchangeSort(int studentID[], float studentScores[], int &elementsUsed);
int getLowScore(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed);
int getHighScore(ofstream &outFile, int studentID[], float studentScores[], int &elementsUsed);
float calculateAverage(float studentScores[], int &elementsUsed);
void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);

int main()
{
	ifstream inFile("DATA3.TXT", ios::in); // Open the Input File. 
	ofstream outFile("RESULTS.TXT", ios::out); // Create the Output File. 
	outFile.setf(ios::fixed); // Set preciscion of Output File. 

	int elementsUsed = 0;
	int lowestScoreLocation;
	int highestScoreLocation;
	float averageTestScore;
	int studentID[50];
	float studentScores[50];

	//**************************************************

		//Print the Header for the output file. 
	Header(outFile);

		// Read Student Records into two arrays, one for ID's one for Test Scores. 
	readData(inFile, studentID, studentScores, elementsUsed);

		// Print labels for the test scores and student ID columns. 
	outFile << "The orginal list of student IDs and test scores is:" << endl <<endl;
	outFile << setw(1) << "Student ID #  " << setw(15) << "Test Score" << endl;

		// Print the original student ID #s and the student scores. 
	printArrays(outFile, studentID, studentScores, elementsUsed);

		// Sort arrays by high to low test scores using bubble sort .
	bubbleSort(studentID, studentScores, elementsUsed); 

		// Print labels for the bubble sorted array columns. 
	outFile << "The student data sorted highest to lowest by test scores are:" 
	<< endl << endl; 
	outFile << setw(1) << "Student ID #  " << setw(15) << "Test Score" << endl;

		// Print bubble sorted arrays. 
	printArrays(outFile, studentID, studentScores, elementsUsed);

		// Sort arrays by low to high student IDs using exchange sort.
	exchangeSort(studentID, studentScores, elementsUsed);

		// Print labels for the exchange sorted array columns. 
	outFile << "The student data sorted lowest to highest by student IDs are:"
		<< endl << endl;
	outFile << setw(1) << "Student ID #  " << setw(15) << "Test Score" << endl;

		// Print exchange sorted arrays. 
	printArrays(outFile, studentID, studentScores, elementsUsed);

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

		//Print the footer for the output file. 
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
	// Task:  print the orginal list of students and their test scores.
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

void bubbleSort(int studentID[], float studentScores[], int &elementsUsed)
{
	// Given:   parallel arrays of studentID's and scores and the elements used in those arrays. 
	// Task:    bubble sort the arrays based on student scores from high to low. 
	// Returns: the two arrays of ID's and scores and the elements used in each by reference.

	int i, n; 
	float temp, temp2; // Two temps for the two parallel arrays. 
	for (i = 0; i < elementsUsed - 1; i++)            
	{
		for (n = elementsUsed - 1; n > i; n--)         
		{
			if (studentScores[n] > studentScores[n - 1])              
			{
				temp = studentScores[n];
				temp2 = studentID[n];

				studentScores[n] = studentScores[n - 1];
				studentID[n] = studentID[n - 1]; 

				studentScores[n - 1] = temp;
				studentID[n - 1] = temp2; 
			}
		} 
	}

}

//**************************************************************

void exchangeSort(int studentID[], float studentScores[], int &elementsUsed)
{
	// Given:   parallel arrays of studentID's and scores and the elements used in those arrays. 
	// Task:    exchange sort the arrays based on student ID numbers from low to high. 
	// Returns: the two arrays of ID's and scores and the elements used in each by reference.


	float temp, temp2; // Two temps for the two parallel arrays. 
    int N, M, Min; 

	for (M = 0; M < elementsUsed - 1; M++)
	{
		Min = M;
		for (N = elementsUsed - 1; N > M; N--)
		{
			if (studentID[N] < studentID[Min])
			{
				Min = N;
			}
		}
			temp = studentID[M];
			temp2 = studentScores[M];

			studentID[M] = studentID[Min];
			studentScores[M] = studentScores[Min];

			studentID[Min] = temp;
			studentScores[Min] = temp2;
		
	}
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

