//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program reads an inventory file, prints its data and sorts the data * 
//*           three different times using three different sort methods.                * 
//*                                                                                    * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*      readData -    reads the data from the input file.                             *
//*                            												           *
//*		 print  -      prints the inventory array contents                             * 
//*																			           *
//*      bubbleSort   -    bubble sorts the inventory array                            *
//*		                                                                               *
//*      shellSort    -    shell shorts the inventory array                            *
//*                                                                                    * 
//*      quickSort     -    quick sorts the inventory array                            *
//*                                                                                    *  
//*                                                                                    * 
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <iostream>

using namespace std;

struct InventoryType
{
	int inventoryNum;
	char itemDescription[26];
	int quantityNum;
	int reorderNum;
	float itemCost;
	float sellingPrice;
};


void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);
void readData(ifstream &infile, InventoryType inventory[], int &EU); 
void print(ofstream &outfile, InventoryType inventory[], int &EU); 
void bubbleSort(InventoryType inventory[], int &EU);
void shellSort(InventoryType inventory[], int &EU);
void quickSort(InventoryType inventory[], int &First, int &Last);


//****************************************************************
int main()
{
	ifstream infile("data5.TXT", ios::in); // Open the Input File. 
	ofstream outfile("RESULTS.TXT", ios::out); // Create the Output File. 

	InventoryType inventory[50];
	int EU = 0;

	//**************************************************

		//Print the Header for the output file. 
	Header(outfile);

		// Read in the data from the inventory file 
	readData(infile, inventory, EU); 

		// Print the Original inventory array. 
	outfile << "The Original Inventory Array:" << endl; 
	print(outfile, inventory, EU); 

		// Sort the inventory array by Quantity on hand using bubble sort. 
	bubbleSort(inventory, EU); 

		//Print the newly sorted inventory array
	outfile << "The inventory array sorted in descending order according to the quantity on hand using the Bubble sort:" << endl;
	print(outfile, inventory, EU);

		//Sort the inventory array by selling price using the shell short.  
	shellSort(inventory, EU); 

		//Print the newly sorted inventory array. 
	outfile << "The inventory array sorted in descending order according to the Selling Price using the Shell Sort:" << endl;
	print(outfile, inventory, EU);

		// Assign the first and last index values for the quicksort. 
	int first = 0; 
	int last = EU - 1; 

		// Sort the inventory array by inventory number using quick sort. 
	quickSort(inventory, first, last); 

		//Print the newly sorted array. 
	outfile << "The inventory array sorted in ascending order according to the Inventory Number using the Quick Sort:" << endl;
	print(outfile, inventory, EU);

		//Print the footer for the output file. 
	Footer(outfile);

	//**************************************************

		// Close the Output file. 
	outfile.close();

}
//*************************************************************************

void readData(ifstream &infile, InventoryType inventory[], int &EU) 
{
	// Given:   the input file, the inventory array and it's elements used. 
	// Task:    read the input file data into the inventory array. 
	// Returns: the input file, inventory array and EU all by reference. 

	infile >> ws;
	infile >> inventory[EU].inventoryNum;
	infile >> ws;
	infile.getline(inventory[EU].itemDescription, 26);
	infile >> ws;
	infile >> inventory[EU].quantityNum;
	infile >> ws;
	infile >> inventory[EU].reorderNum;
	infile >> ws;
	infile >> inventory[EU].itemCost;
	infile >> ws;
	infile >> inventory[EU].sellingPrice;

	while (inventory[EU].inventoryNum > 0)
	{
		EU++;
		infile >> ws;
		infile >> inventory[EU].inventoryNum;
		infile >> ws;
		infile.getline(inventory[EU].itemDescription, 26);
		infile >> ws;
		infile >> inventory[EU].quantityNum;
		infile >> ws;
		infile >> inventory[EU].reorderNum;
		infile >> ws;
		infile >> inventory[EU].itemCost;
		infile >> ws;
		infile >> inventory[EU].sellingPrice;
	}

}


//*************************************************************************


void print(ofstream &outfile, InventoryType inventory[], int &EU)
{
	// Given:   the output file, the inventory array and its elements used. 
	// Task:    print the contents of the inventory array. 
	// Returns: the output file, the inventory array and it's EU all by reference. 

	outfile << "Inventory" << setw(20) << "Item" << setw(28) << "Quantity" << setw(20) 
		    << "Reorder" << setw(25) << "Cost of" << setw(30) << "Selling" << endl; 
	outfile << "Number" << setw(30) << "Description" << setw(20) << "on hand" << setw(20) 
		    << "Number" << setw(23) << "Item" << setw(31) << "Price" << endl;
	outfile << "-----" << setw(30) << "----------" << setw(21) << "-------" << setw(21)
		    << "--------" << setw(25) << "--------" << setw(31) << "---------" << endl;


	for (int i = 0; i < EU; i++)
	{
		outfile << inventory[i].inventoryNum << setw(46) << inventory[i].itemDescription 
			    << setw(3) << inventory[i].quantityNum << setw(20) << inventory[i].reorderNum 
			    << setw(27) << inventory[i].itemCost << setw(31) << inventory[i].sellingPrice 
			    << endl;
	}

	outfile << endl << endl << endl; 
}

//*************************************************************************


void bubbleSort(InventoryType inventory[], int &EU)
{
	// Given:   The inventory array and its elements used.  
	// Task:    bubble sort the array in descending order based on the quantity on hand. 
	// Returns: The inventory array and it's EU both by reference. 

	int i, n; 
	InventoryType Temp;

	for (i = 0; i < EU - 1; i++)
	{
		for (n = EU - 1; n > i; n--)
		{
			if (inventory[n].quantityNum > inventory[n - 1].quantityNum)
			{
			
				Temp = inventory[n]; 
				inventory[n] = inventory[n - 1]; 
				inventory[n - 1] = Temp; 
			}
		}
	}
}



//*************************************************************************
void shellSort(InventoryType inventory[], int &EU)
{
	// Given:   The inventory array and its elements used.  
	// Task:    shell sort the array in descending order based on the selling price.  
	// Returns: The inventory array and it's EU both by reference. 


	int count = 0;
	int NumOfStages = 3;
	int KValues[3] = { 7, 3, 1 };
	int i, j, k, Stage;
	InventoryType Temp;
	bool  Found;

	for (Stage = 0; Stage < NumOfStages; Stage++)
	{
		k = KValues[Stage];
		for (i = k; i < EU; i++)
		{
			Temp = inventory[i]; 
			j = i - k;
			Found = false;

			while ((j >= 0) && (!Found))
			{
				if (Temp.sellingPrice > inventory[j].sellingPrice)
				{
					inventory[j + k] = inventory[j];
					j -= k;
				}
				else
					Found = true;
			}  

			inventory[j + k] = Temp;

		}
	}
}

//*************************************************************************


void quickSort(InventoryType inventory[], int &First, int &Last)
{
	// Given:   The inventory array, its first element and it's last element.  
	// Task:    quick sort the array in ascending order based on the inventory number
	// Returns: The inventory array and its first & last elements by reference. 


	int I, J, MID, Pivot_Value;
	InventoryType Temp;
	I = First;
	J = Last;
	MID = (First + Last) / 2;    // Find the middle indexed 
	Pivot_Value = inventory[MID].inventoryNum; // Find the Pivot Point


	while (I <= J)
	{
		while (inventory[I].inventoryNum < Pivot_Value)
			++I;
		while (inventory[J].inventoryNum > Pivot_Value)
			--J;
		if (I <= J)
		{
			Temp = inventory[I];      //  switch  inventory[I] and inventory[J]
			inventory[I] = inventory[J];
			inventory[J] = Temp;
			++I;
			--J;
		}
	}

	if (J >= First)
	{
		quickSort(inventory, First, J);        //  Partition left subarray
	}

	if (I <= Last)
	{
		quickSort(inventory, I, Last);         //  Partition right subarray 
	}

}



//*************************************************************************
