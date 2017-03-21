//********************************************************************************
//*                                                                              *
//*   File: Q3.cpp                        Author: Renee Van Dyke                 *
//*                                                                              *
//*   Course: CSC 36000                   Date: February 23, 2007                *
//*                                                                              *
//*   Purpose: This program sets up a queue using an array implementation.  NO   *
//*            pointers are used. The queue is a private member of an OBJECT     *
//*            that is a member of the class of objects named QueueClass.        *
//*                                                                              *
//*                                                                              *
//********************************************************************************
#include <fstream.h>
#include <iomanip.h>
#include <string.h>

#define MaxSize  100
#define Sentinel "ZZZZ                "

struct NODETYPE 
{
  char Name[21];
  int  age;
};
//=============================================================================
class QueueClass 
{
   public:
     	QueueClass ();
     	bool IsEmpty(){return(count == 0);}
     	bool IsFull() {return(count == MaxSize);}
     	bool First( NODETYPE &dataout); 
     	bool Last( NODETYPE &dataout);
       	int QueueCount(){return count;}
     	bool Add(NODETYPE datain);
     	bool Delete( NODETYPE &dataout);
        void Print();
   private:
     	int front;
     	int rear;
     	int size;
       	int count;
        NODETYPE ArrayOfNodes[MaxSize];	   
};
//*****************************************************************************
int main()
{
	char temp[21];
	NODETYPE Node;
    QueueClass Queue;
    ifstream infile("Qdata.txt", ios::in);

	infile >> ws;
	infile.getline(temp, 21);		// Read the first name

	while (strcmp(temp,Sentinel) != 0)		// If the name is valid then ...
	{
       strcpy(Node.Name,temp);		// copy the name into the node
	   infile >> Node.age;			// read the person's age into the node
       Queue.Add(Node);				// add the node to the linked list
	  
	   cout << "The Queue now consist of: " << endl;
	   Queue.Print();
	   cin.ignore();
	   
	   infile >> ws;
	   infile.getline(temp, 21);	// read the next name
    }    
							// print the output heading
	cout << "The final list of new students include: " << endl << endl;
	cout << "    Name                   Age    " << endl;
	cout << "   ------                 -----   " << endl;
	Queue.Print();			// print the information in the linked list
       
    cin.ignore();
							// delete the first six nodes in the list
    for (int i=0; i<5; i++)
	{
		Queue.Delete(Node);		// Delete the node 

        cout << endl << endl << " The deleted node was " << Node.Name 
			 << endl << endl << endl << endl;
		cin.ignore();
								// print the new list
        cout << endl << endl << "The new queue contents are: " << endl << endl;
        Queue.Print();
		cout << endl << endl << endl;
		cin.ignore();
	}

	cout << endl;
  return 0;
}
//*****************************************************************************
void QueueClass::Print()
{
	cout.unsetf(ios::fixed);
  for (int i=front; i<= rear; i++)
  { 
     cout << setw(22) << ArrayOfNodes[i].Name 
		  << setw(7) << ArrayOfNodes[i].age << endl;
  }  
}
//*****************************************************************************
bool QueueClass::Last(NODETYPE &dataOut) 
{
   if ( IsEmpty() ) 
   {
   	      cout << "Queue is empty." <<endl;
   	      cout << "No last element returned." 
               << endl;	
   	      return false;
   }
   else
   {
          dataOut = ArrayOfNodes[rear]; 
 	      return true;
   }
}
//*****************************************************************************
bool QueueClass::First(NODETYPE &dataOut )
{  
 if ( IsEmpty() ) 
 {
     cout << "Queue is empty." <<endl;
     cout << "No first element returned." << endl;	
     return false;
 }
 else
 {
     dataOut = ArrayOfNodes[front];  
     return true;
 }
}
//*****************************************************************************
bool QueueClass::Delete(NODETYPE &dataOut) 
{
   if ( IsEmpty() ) 
      return false;
 	  
   dataOut = ArrayOfNodes[front]; 

   front++;

   if (front == MaxSize)
     front = 0;

   if (count == 1)
     rear = front = -1;

   count--;

   return true;
}
//*****************************************************************************
bool QueueClass::Add(NODETYPE dataIn) 
{
   if ( IsFull() ) 
     return false;

   rear++;
   if (rear == MaxSize)
     rear = 0;

   ArrayOfNodes[rear] = dataIn;

   if ( IsEmpty() )
      front = 0;

   count++;

   return true;
}
//*****************************************************************************
QueueClass::QueueClass ( )
{
   size = MaxSize;
   front = rear = -1;
   count = 0;
}
//*****************************************************************************
