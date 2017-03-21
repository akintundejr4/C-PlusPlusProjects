//***************************************************************************
//*                                                                         *
//*   File Name:  StacksTwo.cpp            Author: Renee Van Dyke           *
//*                                                                         *
//*   Course: CSC 360                      Date: February 23, 2005          *
//*                                                                         *
//*   PURPOSE: This program demonstrates how a stack ADT is employed.       *
//*            It implements the stacks as a linked list using a class as   *
//*            the primary data structure.  It included the operations of   *
//*            PUSH and POP.                                                *
//*                                                                         *
//***************************************************************************
#include <fstream.h>
#include <iomanip.h>
#include <stdlib.h>

//********************   Creating the stack class
				// Create the node
struct NodeType
{
   int data;
   NodeType * next;
};

				// Define the stack
class StackClass 
{  
	public:
	  StackClass(){TopPtr = NULL;}      
	  void Push( NodeType );
	  void Pop (NodeType & );
      bool RetrieveTop(NodeType &);
	  bool IsEmpty()  {return (TopPtr == NULL);}
	  NodeType * GetTop(){ return TopPtr; }
 	  bool IsFull();
	  void Print();
  	private:
  	  NodeType *TopPtr;
};

//***********************    main function   *******************
int main()
{
   NodeType  Item;
   StackClass  Stack;
   int i, value = 100 ;
   

   for (i=0; i<20; i++)
   {
	  if( (i%3)==0 )
	  {
        value -= i+3;
        Item.data = value;
		cout << "Item.data to be placed on stack is " << Item.data << endl<< endl;
		cout << "     *****     Calling PUSH     *****" << endl << endl;
		Stack.Push(Item);
		cout << "Items on the stack are: " << endl << endl;
		Stack.Print();
	  }
	  else if ( ( (i%4)==0 ) ||  ( (i%6)==0 )  )
	  {
 	   cout << "     *****     Calling POP     *****" << endl << endl;
  	   Stack.Pop(Item);
	   cout << "Item.data removed from the stack is " << Item.data << endl << endl;
	   cout << "Items on the stack are: " << endl << endl;
       Stack.Print();
	  }
      else
	  {
        value += i+7;
	    Item.data = value;
		cout << "Item.data to be placed on stack is " << Item.data << endl << endl;
		cout << "     *****     Calling PUSH     *****" << endl << endl;
		Stack.Push(Item);
		cout << "Items on the stack are: " << endl << endl;
		Stack.Print();
	  }

	  cin.ignore();
	  cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" 
		   << endl << endl;
   }

   Stack.Print();
   cout << endl;
   
   while (Stack.GetTop() != NULL)
   {
	   Stack.Pop(Item);
	   cout << "################################################" << endl << endl;
	   cout << Item.data << " removed from the stack. " << endl << endl;
	   if( Stack.GetTop() != NULL)
	   {
	       cout << "Items on the stack are now: " << endl << endl;
	       Stack.Print();
	   }
	   else
	   {
		   cout << "Stack is now empty." << endl << endl;
	   }

	   cin.ignore();
   }

   cout << "################################################" << endl << endl;

   return 0;
}
//********************    The Print stack function    ********************
void StackClass::Print()
{
  NodeType *current;

  current = TopPtr;

  while (current != NULL)
  {
   cout << current->data << endl;
   current = current->next;
  }

  return;
}
//********************    Test if stack is full      **********************
bool StackClass::IsFull() 
{
   NodeType  *p;
   p = new NodeType;
   if (p == NULL)
   {
     delete p;
     cout << "Out of Memory. " 
          << endl;
     return true;
   }
   return false;
}
//********************    Return FIRST element        *********************
bool StackClass::RetrieveTop(NodeType &DataOut) 
{
   if (IsEmpty() )
   {
     cout << "Stack is Empty. " << endl;
     return false;
   }
   else
   {
     DataOut.data = TopPtr -> data; 
     return true;
   }
}
// *******************    The PUSH Function           *********************
void StackClass::Push( NodeType  DataIn)
{
   if (IsFull () )
   {
     cout << " Add operation failed! " << endl;
     return;
   }

   NodeType *p ;          // create node for
   p = new NodeType;     // new element

   p -> data = DataIn.data; 			
   p -> next = TopPtr;
   TopPtr = p;
              
   return;
}
// *******************   The POP Function            **********************
void StackClass::Pop( NodeType &DataOut)
{
    NodeType *p ;
    if (IsEmpty() )
	{
      cout << " Stack is empty. " << endl;
      cout << " Delete Operation Failed. " << endl;
      delete p;
      return;
    }		
 	             // Save element in the first node
    DataOut.data = TopPtr->data; 
                // Adjust Stack Top
    p = TopPtr;	  
    TopPtr = TopPtr -> next;

    delete p;
    return;
}
//*************************************************************************

