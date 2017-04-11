//***************************************************************
//*  File Name: QS_2004.cpp              Author: Renee Van Dyke
//*  Course: CSC 407                     Date: April 1, 2004
//***************************************************************
#include <iostream.h> 
#include <fstream.h> 
#include <iomanip.h>
#include <string.h>

struct InventoryType 
{
 int StockNum; 
};
			// Prototypes
void QuickSort  (InventoryType [], int, int);
void PrintArray (InventoryType [], int);
void ReadData (ifstream, InventoryType [], int &);

ofstream outfile("quick_out", ios::out);
int count=0;
int pass=0;

int main() 
{  
	outfile.setf(ios::left);
	ifstream infile("Quick_in.txt",ios::in);
	int First = 0, Last, ElementsUsed= 0;
    InventoryType Array[50];

    ReadData(infile, Array, ElementsUsed);

	outfile << "   Original Array" << endl << endl;
	outfile << "Item   " << endl;
	outfile << "Number " << endl;
    
	PrintArray (Array, ElementsUsed);
    
	First = 0;
	Last = ElementsUsed-1;


	outfile << "Array Sorted by Item Number" << endl << endl;
	outfile << "Item    " << endl;
	outfile << "Number  " << endl;
   
	QuickSort (Array, First, Last);

    PrintArray (Array, ElementsUsed);

	outfile << "*** End of Output *** " << endl;
  return 0;
}
//*************************************************************************
void QuickSort (InventoryType Array[], int First, int Last )
{
    int I, J, MID, Pivot_Value;
	InventoryType Temp; 
	I = First;
	J = Last;     
    MID = (First+Last)/2;    // Find the middle indexed 
	Pivot_Value = Array[MID].StockNum; // Find the Pivot Point


    while (I <= J)
	{
	  while (Array[I].StockNum < Pivot_Value)
		  ++I;
      while (Array[J].StockNum > Pivot_Value)
          --J;  
 	  if(I <= J)  
	  {
 	    Temp = Array[I];      //  switch  Num[I] and Num[J]
		Array[I] = Array[J];
		Array[J] = Temp;  
        ++I;
 		--J;
	  }
	}

	if( J >= First )
	{
      QuickSort(Array, First, J);        //  Partition left subarray
	}

	if( I <= Last  )
	{
      QuickSort(Array, I, Last);         //  Partition right subarray 
	}

}
//*************************************************************************
void PrintArray(InventoryType Array[], int EU) 
{ int i;

  outfile.setf(ios::fixed);
  outfile.setf(ios::left);
  outfile.precision(2);
  
  //outfile << " " << endl;
  //outfile << " EU = " << EU<< endl;

  for (i=0; i<EU; i++)
  { 
//	outfile.unsetf(ios::left);      
    outfile << setw(5)  << Array[i].StockNum << endl;
  }  
  outfile << endl<< endl;
}
//**********************************************************************
void ReadData (ifstream infile, InventoryType A[], int &eu)
{
	int Num;

	eu = 0;
	infile >> Num;


	while ( Num > 0)
	{
      A[eu].StockNum = Num;
	  eu++;

	  infile >> Num;
	 
	}
	return;
}
//**********************************************************************
