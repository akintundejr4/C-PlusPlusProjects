//****************************************************************
//*                                                              *
//*  File Name: Queue_LL.cpp         Author: Renee Van Dyke      *
//*                                                              *
//*  Course: CSC 36000               DATE:  February 15, 2012    *
//*                                                              *
//*                                                              *
//*                                                              *
//*                                                              *
//****************************************************************
#include <fstream.h>
#include <iomanip.h>
#include <string.h>


struct NodeType 
{
	int  ServiceTime;
    char Name[26];
    NodeType *next;
};
//******************************************
class LinkedQueueClass 
{
   public:
		LinkedQueueClass();
		~LinkedQueueClass();
		bool IsEmpty() 
                {return ((front==NULL) ? true : false);}
		bool IsFull(); 
		NodeType * First(); 
		NodeType * Last();
		bool Add(NodeType );
		bool Remove(NodeType &);
		void PrintQ();           // This function is to trace the
   private:						 // contents of the queue.
		int count;
       	NodeType *front;
        NodeType *rear;
 		};
//*******************************************
int main()
{  
	NodeType Node;
    LinkedQueueClass  Queue;
    bool flag;
    char code;

	ifstream infile ("LLdata.txt",ios::in);
	ofstream outfile ("Q_Results",ios::out);
                     
    infile >> code;
	cout << "Code = " << code << endl;
    while ( code != 'Q' )
    {
       switch (code)
       {  
		 case 'A': infile.getline(Node.Name,26);
			       cout << "name read was  " << Node.Name << endl;
				   cin.ignore();
								// Add the node to the Queue
                   flag = Queue.Add(Node);

                   if (flag)
					   Queue.PrintQ();
				   else
					   cout << Node.Name << " not added to queue." 
					        << endl;
                   break;
         case 'D': 	 
                   flag = Queue.Remove(Node);
                              
				   if (flag)
					   Queue.PrintQ();
				   else
					   cout << Node.Name << " not in Queue" 
					        << endl;
                              break;
       }
       infile >> code;
	   cout << "Code read was " << code << endl;
	   cin.ignore();
    }
       cout << endl << endl;          
    return 0; 
}                
//***********************************************
void LinkedQueueClass::PrintQ()
{
   NodeType *current;

   current = front;

   if (current == NULL)
	   cout << "There is no list to print. "
	        << endl;
   else
   {   cout << "Contents of the QUEUE are: " 
            << endl << endl;
	   while (current != NULL)
	   {
           cout << setw(27) << current->Name << endl;
           current = current->next;
	   }
   }
   cout << endl << endl;
}
//***********************************************
LinkedQueueClass::LinkedQueueClass()
{
 	   front = NULL;
   	   rear = NULL;
	   count = 0;
}
//**********************************************
LinkedQueueClass::~LinkedQueueClass()
{
	   NodeType *next;
   	   while (front != NULL) 
	   {
   	      next = front-> next;
          delete front;
          front = next;
       }
}
//**********************************************
bool LinkedQueueClass::Add( NodeType NewNode)
{
   NodeType *NewPtr;

   NewPtr = new (NodeType); 
   NewPtr -> ServiceTime = NewNode.ServiceTime;
   strcpy(NewPtr -> Name, NewNode.Name);
   NewPtr -> next = 0;

   if (IsFull () )
      return false;
           	     
   if (front == NULL)
   {
     front = NewPtr;
   }
   else
      rear-> next = NewPtr;   // queue is not empty
              
   rear = NewPtr;;
   count++;
   return true ;
}
//**********************************************
bool LinkedQueueClass::Remove(NodeType &Node )
{
   NodeType *temp;

   if ( IsEmpty() )
      return false ;
                                    // Save the info 
   Node.ServiceTime = front->ServiceTime;
   strcpy(Node.Name, front->Name); 	
   count--;
                   // Delete the node
   temp = front;
   front = front->next;
   delete temp;
   return true ;
}
//**********************************************
NodeType * LinkedQueueClass::First() 
{
  if ( IsEmpty() )
  {
     cout << "Queue is Empty. " << endl;
     return NULL;
  }
  return front;
}
//**********************************************
NodeType * LinkedQueueClass::Last() 
{
   if ( IsEmpty() )
   {
      cout << "Queue is Empty. " << endl;
      return NULL;
   }
   return rear;
}
//**********************************************
bool LinkedQueueClass::IsFull() 
{
   NodeType  *p;
   p = new (NodeType);

   if (p == NULL)
   {
      delete p;
      cout << "Out of Memory. " << endl;
      return true;
   }
   return false;
}
//**********************************************
