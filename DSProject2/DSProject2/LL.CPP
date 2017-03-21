//*****************************************************************
//*                                                               *
//*  File: LL.CPP					Author: Renee Van Dyke        *
//*                                                               *
//*  Course: CSC 360				Date: February 16, 2004       *
//*                                                               *
//*  Purpose: This program is designed to demostrate the use of   *
//*           structures in a Linked List. The program repeatedly *
//*           adds, deletes, and prints the contents of the       *
//*           Linked List until the quit operation is performed.  *
//*                                                               *
//*****************************************************************
#include <fstream.h>
#include <iomanip.h>
#include <stdlib.h>

		// Define a Node type
struct NodeType
{
   int data;
   NodeType *next;
};

		// Create the Function Prototypes
void InsertNode (NodeType *& , int );  
int PrintNode (NodeType *&);
NodeType DeleteNode(NodeType *& , int);


int main()
{		// declare the required variables
   char Operation;
   int Number, value, ptr;
   ifstream infile ("dataLL.txt", ios::in);
   NodeType *StartPtr=NULL;
   NodeType Node;
   
		// Read the first Operations code
   infile >> ws >>Operation;
	
		// while there is data to process 
   while (Operation != 'Q')
   {
     cout << "========================" << endl << endl;
     cout << "Operation Code is: " << Operation << endl << endl;

			// Select the operation to be performed
     switch (Operation)
	 {
					//  Add a value to the list
	 case 'I': infile >> value;
		       cout << "Insert " << value << " into the linked list." << endl << endl;
               InsertNode(StartPtr, value);
			   break;
					//  Delete a value from the list
     case 'D': infile >> value;
               cout << "Delete " << value << " from the linked list." << endl << endl;
               Node = DeleteNode(StartPtr, value);
			   if(Node.data > 0)
			   {
                  cout << "Node with value of "<< Node.data
			  	       << " deleted." << endl << endl;
			   }
			   else
			   {
				   cout << "The Node with a data value of " << value
					    << " is not in the list. " << endl;
			   }
			   break;
					//  Print the values in the list
	 case 'P': cout << "The values in the Linked List are now:" << endl << endl;
               ptr = PrintNode(StartPtr);
               cout << endl;
			   break;
	 }
	 cin.ignore();
     infile >> ws >> Operation;
   }
	return 0;
}

//***********************************************************
// int DeleteNode(NodeType *&SPtr, int Num)
NodeType DeleteNode(NodeType *&SPtr, int Num)
{
	// Given: A list of values and the key value to be removed
	// Task: Remove the value from the list 
	// Returns: The value deleted from the list and the updated list

  NodeType *tempPtr, *PreviousPtr, *CurrentPtr;
  NodeType Node;

  Node.data = -1;
  Node.next = NULL;

  if (Num == SPtr->data)
  {
   Node.data = Num;
  
   tempPtr = SPtr;
   SPtr = SPtr->next;
   free(tempPtr);

   return Node;
  }
  else
  {
    PreviousPtr = SPtr;
	CurrentPtr = SPtr->next;
	while ( (CurrentPtr != NULL) && (CurrentPtr->data != Num) )
	{
      PreviousPtr = CurrentPtr;
	  CurrentPtr = CurrentPtr -> next;
	}
    if(CurrentPtr !=NULL)
	{
     Node.data = Num;

     tempPtr = CurrentPtr;
     PreviousPtr->next = CurrentPtr->next;
     free(tempPtr);
     return Node;
	}
  }
 return Node;
}

//**********************************************************
void InsertNode (NodeType *&SPtr , int Num )
{
    // Given: A list of values and the key value to be added
	// Task: Add the value from the list 
	// Returns: The value deleted from the list and the updated list

   NodeType *newPtr, *PreviousPtr, *CurrentPtr;
    
   newPtr = new (NodeType);

   if ( newPtr == NULL)
   {
	   cout << "Node " << Num << " not inserted." << endl;
	   cout << " No memory available.";
   }
   else
   {
    newPtr -> data = Num;
	newPtr -> next = NULL;
	PreviousPtr = NULL;
	CurrentPtr = SPtr;

	while ( (CurrentPtr != NULL) && (Num > CurrentPtr->data) )
	{
	  PreviousPtr = CurrentPtr;
	  CurrentPtr = CurrentPtr -> next;
	}

	if(PreviousPtr == NULL)
	{
     newPtr -> next = SPtr;
	 SPtr = newPtr;
	}
    else
	{
     PreviousPtr -> next = newPtr;
	 newPtr -> next = CurrentPtr;
	}
   }
   return;
}
//**********************************************************
int PrintNode (NodeType *&SPtr)
{
    // Given: A list of values 
	// Task: Print the values in the list 
	// Returns: The an indicator of success

   NodeType  *CurrentPtr;
    
   CurrentPtr = SPtr;

   if ( CurrentPtr == NULL)
   {
	   cout << "List is Empty" << endl;
	   return -1;
   }

   while ( (CurrentPtr->next != NULL) )
	{
     cout << setw(5) << CurrentPtr->data;
	 CurrentPtr = CurrentPtr -> next;
	}
    cout << setw(5) << CurrentPtr->data << endl;

   return 1;
}
//***************************
