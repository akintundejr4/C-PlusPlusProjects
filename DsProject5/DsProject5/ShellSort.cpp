//***************************************************************
//*  File Name: ShellSort.cpp            Author: Renee Van Dyke
//*  Course: CSC 36000                   Date: March 1, 2017
//***************************************************************
#include <iostream> 
#include <fstream> 
#include <iomanip>

using namespace std;

			// Prototypes
void ShellSort ( int [], int );
void PrintArray(int [], int, int);

ofstream outfile("shell_out", ios::out);

int main() 
{   int ElementsUsed;
	int Array[21] = { 71, 87, 45, 72, 39, 92, 1,
		              40, 11, 63,  9, 19,  2, 13, 
					  26, 22, 37, 53, 59, 68, 15};
    ElementsUsed = 21;
	cout << "Original Array" << endl;
	outfile << "Original Array" << endl;
    PrintArray (Array, ElementsUsed, 7);
    ShellSort (Array, ElementsUsed);
	cout << "Final Array" << endl;
	outfile << "Final Array" << endl;
    PrintArray (Array, ElementsUsed, 7);
  return 0;
}
//***********************************
void PrintArray(int Array[], int EU, int k) 
{ 
  int i;
 
  for (i =0; i<EU; i++)
  {
	if(i%k==0)
	  cout << setw(2) << " * ";
    outfile << setw(3) << Array[i] ;
	cout << setw(3) << Array[i] ;
  }  
  outfile << endl<< endl;
  cout << endl<< endl;
  cin.ignore();
}
//******************************************************
void ShellSort ( int array[], int ElementsUsed) 
{
	 int count = 0;
     int NumOfStages = 3;
     int KValues[3] = {7, 3, 1};         
     int i, j, k, Temp, Stage;
     bool  Found;

     for ( Stage = 0; Stage < NumOfStages;  Stage++) 
	 {
       k = KValues[Stage];
       for (i=k; i<ElementsUsed; i++)  
	   {
         Temp = array[i];
         j = i-k;
         Found = false;
         while (( j >= 0) && ( !Found) ) 
		 {
           if (Temp < array[j]) 
		   {
             array[j+k] = array[j];
             j -= k;
		   }
           else
		     Found = true;
		 }   // end while
         array[j+k] = Temp;
		 
		 outfile << "Array" << endl;
 	     cout << "Pass " << ++count << " thru the Array "<< endl;
		 PrintArray (array, ElementsUsed, k); // NOT PART OF SORT
	   }
	 }
}  // end Shell Sort
//*********************************************************
