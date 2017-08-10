#include <iostream.h>
#include <stdlib.h>
#include <iomanip.h>

				// Define a node structure
struct NodeType 
{
   int  data;
};
//============================================================
                // Define a class to implement the Linked List
class QueueClass 
{
	public:
   		     QueueClass (int MaxSize = 100);
		     ~QueueClass(){ delete [] queueArray; }
 		     bool IsEmpty(){return(count == 0);}
 		     bool IsFull() {return(count == MaxSize);}
		     bool First( int &dataout); 
		     bool Last( int &dataout);
             int QueueCount(){return count;}
		     bool Add( int datain);
		     bool Delete( int &dataout);
    private:
 		     int front;
		     int rear;
		     int MaxSize;
              int count;
  		     NodeType * queueArray;     
};
//************************************************************
int main()
{
   bool Flag;
   QueueClass Queue;
   int i, Num;
						// Print the output heading
   cout << " First      Last"  << endl
        << " Node       Node"  << endl
        << " Value      Value" << endl;	             
   
                         // Add values to the list
   for (i = 1; i <= 10; i++)
   {
				// Add a value to the Linked List
      Flag = Queue.Add(i*27/13);
				// Print the First value in the Linked List
      Flag = Queue.First(Num);
      if (Flag)
	     cout <<setw(4) <<  Num;
      else
	     cout << "No value returned.";
				// Print the Last value in the Linked List
      Flag = Queue.Last(Num);
      if (Flag)
         cout << setw(10) << Num << endl;
      else
         cout << "No value returned." << endl;
   }

   cout << endl;
					// Print the output heading
   cout << " First      Last"  << endl
        << " Node       Node"  << endl
        << " Value      Value" << endl;

   for (i = 1; i < 10; i++)
   {
				// Remove a value to the Linked List
      Flag = Queue.Delete(Num);
				// Print the First value in the Linked List
      Flag = Queue.First(Num);
      if (Flag)
         cout << setw(4) << Num;
      else
	     cout << "No value returned.";
				// Print the Last value in the Linked List
      Flag = Queue.Last(Num);
      if (Flag)
	     cout << setw(10) << Num << endl;
      else
	     cout << "No value returned." << endl;
   }

   return 0;
}
//*************************************************************************
bool QueueClass::Delete(int &dataOut) 
{
			// GIVEN:   The data value to be removed from the linked list
			// TASK:    Remove the value from the linked list
			// RETURNS: The linked list with the value removed
   if ( IsEmpty() ) 
      return false;
 		  
   dataOut = queueArray[front].data;
   front++;

   if (front == MaxSize)
       front = 0;

   if (count == 1)
       rear = front = -1;

   count--;

   return true;
}
//**********************************************************************
bool QueueClass::Add(int dataIn) 
{
			// GIVEN:   The data value to add to the linked list
			// TASK:    Add the value to the linked list
			// RETURNS: The linked list with the new value added
 	if ( IsFull() ) 
 	    return false;
 	 
	rear++;
    if (rear == MaxSize)
        rear = 0;

	queueArray[rear].data = dataIn;

    if ( IsEmpty() )
        front = 0;
    count++;
    return true;
}
//***********************************************************************
bool QueueClass::First(int &dataOut )
{ 
			// GIVEN:   The output file 
			// TASK:    Prints the data value at the front of the linked list
			// RETURNS: An indication that an item was printed or not.

 	if ( IsEmpty() ) 
	{
 		cout << "Queue is empty." <<endl;
 		cout << "No first element returned." << endl;	
 		return false;
	}
    else
	{
        dataOut = queueArray[front].data;
		return true;
	}
}
//************************************************************************
bool QueueClass::Last(int &dataOut) 
{
			// GIVEN:   The output file 
			// TASK:    Prints the data value at the rear of the linked list
			// RETURNS: An indication that an item was printed or not.

    if ( IsEmpty() ) 
	{
 	   cout << "Queue is empty." <<endl;
 	   cout << "No last element returned." << endl;	
 	   return false;
	}
    else
	{
       dataOut = queueArray[rear].data;
	   return true;
	}
} 
//***********************************************************************
QueueClass::QueueClass (int Size)
{ 
  MaxSize = Size;
  front = rear = -1;
  count = 0;
  queueArray = new NodeType [MaxSize];
  if (!queueArray)
  {
    cout << "Not enough memory to allocate queue\n";
    exit (1);
  }
} 
//**********************************************************************
