//*************************** Program Identification ***********************************
//*                                                                                    *
//*  Program File Name: DsProject4.cpp    Assignment #3    Grade: _____                *
//*																			           *
//*  Program Author: ______________________________							           *
//*                    AkinTunde Akinyemi                                              *
//*																			           *
//*  Course:  CSC 3600                        Due Date:  March 20th, 2017              *
//*                                                                                    *
//**************************************************************************************

//*************************** Program Description **************************************
//*                                                                                    *
//*                                                                                    *
//*  Process: This program takes a mathematical expression in infix notation, converts * 
//*           it to postfix notation and then evaluates the postfix expression. The    * 
//*           porgram is to use stacks and pointer implementation.                     * 
//*                                                                                    *  
//*  User Defined                                                                      *
//*  Modules:                                                                          * 
//*                                                                                    * 
//*      IsEmpty -    checks if the stack is empty                                     *
//*                            												           *
//*		 IsFull  -    checks if the stack is full.                                     * 
//*																			           *
//*      Push   -    Pushes a node onto the stack                                      *
//*		                                                                               *
//*      Pop    -    Pops a node off the stack                                         *
//*                                                                                    * 
//*      GetTop     -    returns the top pointer                                       *
//*                                                                                    * 
//*      Print  -    prints the stack contents                                         *
//*                                                                                    * 
//*      EvalPostfix - evaluates the postfix expression                                * 
//*                                                                                    * 
//*      Eval  -    Evaluates two digits based on operator                             * 
//*                                                                                    * 
//*      highprecendence - determines which of two operators has higher precedence     * 
//*                                                                                    * 
//*      isoperator    - determines if a char is an operator                           * 
//*                                                                                    * 
//*      isoperand   - determines if a char is an operand                              * 
//*                                                                                    * 
//*      operatorweight  - adds weight to operators.                                   * 
//*                                                                                    * 
//**************************************************************************************


#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

struct NodeType
{
	char currentChar;
	string infix;
	string postfix;
	NodeType * next;
};

class StackClass
{
public:
	StackClass() { TopPtr = NULL; }
	void Push(NodeType);
	void Pop(NodeType &);
	bool IsEmpty() { return (TopPtr == NULL); }
	char GetTop() { return TopPtr->currentChar; }
	bool IsFull();
	void Print(ofstream &outfile);
	int evalPostfix(ofstream &outfile, string &postfix);

private:
	NodeType *TopPtr;
};


bool highprecendence(char a, char b);
bool isoperator(char arg);
bool isoperand(char arg);
int operatorweight(char arg);
int eval(int op1, int op2, char operate);
void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);


//****************************************************************
int main()
{
	ifstream infile("stack_in.TXT", ios::in); // Open the Input File. 
	ofstream outfile("RESULTS.TXT", ios::out); // Create the Output File. 
	outfile.setf(ios::fixed); // Set preciscion of Output File. 


	NodeType Item;
	StackClass stk;
	string infixDisplay;
	int value = 0;

		// Read in the infix expression 
	getline(infile, Item.infix);
	infixDisplay = Item.infix;

		// Step character by character through the expression 
	while (Item.infix != "X")
	{
			// Print out the Conversion heading. 
		outfile << setw(60) << "Conversion Display " << endl;
		outfile << "Infix Expresssion" << setw(30) << "Postfix Expression" << setw(30) << "Stack Contents" << endl;

			// Scan the infix string one by one. 
		for (int i = 0; i < Item.infix.length(); i++)   
		{
			Item.currentChar = Item.infix[i];
				//If left paren is found, push onto the stack. 
			if (Item.infix[i] == '(')
			{
				stk.Push(Item);
			}
				// If a right paren is seen, pop off operators one at a time until a matching left paren is found. 
			else if (Item.infix[i] == ')')
			{
				while (stk.GetTop() != '(')
				{
					Item.postfix = Item.postfix + stk.GetTop();
					stk.Pop(Item);
				}
				stk.Pop(Item);
			}
				// If an operand is seen, place it directly into the postfix expression. 
			else if (isoperand(Item.infix[i]))
			{
				Item.postfix += Item.infix[i];
			}
				// If an operator is seen pop or push the stack depending on precedence. 
			else if (isoperator(Item.infix[i]))
			{
					// If the stack is empty and the precedence matches pop the stack. 
				while (!stk.IsEmpty() && !highprecendence(Item.infix[i], stk.GetTop()))
				{
					Item.postfix += stk.GetTop();
					stk.Pop(Item);
				}
				stk.Push(Item);
			}

				// Print the conversion display. 
			outfile << infixDisplay << setw(30) << Item.postfix;
			for (int i = 0; i < infixDisplay.length(); i++)
			{
				infixDisplay[i] = infixDisplay[i + 1];
			}
			stk.Print(outfile);
		}

			// Pop the remaining operators from the stack 
		while (!stk.IsEmpty())
		{
			Item.postfix += stk.GetTop();
			stk.Pop(Item);
		}
		outfile << endl << endl;

			// Print the evaluation display headers. 
		outfile << setw(60) << "Evaluation Display " << endl;
		outfile << "Postfix Expresssion" << setw(58) << "Stack Contents" << endl;

			// Evaluate the postfix expression. 
		value = stk.evalPostfix(outfile, Item.postfix);

			// Print the orginal expression and it's answer 
		outfile << "Original Expression and The Answer:" << endl;
		outfile << Item.infix << " = " << setw(2) << value << endl;

			// Read in the next infix expression & reset the postfix. 
		getline(infile, Item.infix);
		infixDisplay = Item.infix;
		Item.postfix = { 0 };
		outfile << endl << endl << endl;
	}

}
//*************************************************************************

bool highprecendence(char a, char b)
{
	// Given: Two characters 
	// Task: Check for operator precedence. 
	// Returns: true or false (1 or 0) depedning on if 
	//          char a is greater than or less than char b   

	int weighta = operatorweight(a);
	int weightb = operatorweight(b);

	if (weighta >= weightb)
	{
		return 1;
	} 
	return 0;
}
//*************************************************************************

bool isoperator(char arg)
{
	// Given: One character
	// Task: Check whether the character is an operator. 
	// Returns: true or false (1 or 0) if it is or is not an operator. 

	if (arg == '*' || arg == '/' || arg == '+' || arg == '-')
	{
		return(1);
	}
	else
	{
		return(0);
	} 
}
//*************************************************************************

bool isoperand(char arg)
{
	// Given: One character
	// Task: Check whether the character is an operand. 
	// Returns: true or false (1 or 0) if it is or is not an operand

	if (arg >= '0' && arg <= '9') return 1;
	if (arg >= 'a' && arg <= 'z') return 1;
	if (arg >= 'A' && arg <= 'Z') return 1;
	return 0;
}
//*************************************************************************

int operatorweight(char arg)
{
	// Given: One character
	// Task: Add weight to the operator
	// Returns: 1 for addition and subtraction, 2 for multiplication and division. 

	int weight = 0;
	switch (arg)
	{
	case '*':
	case '/':
		weight = 2;
		break;
	case '+':
	case '-':
		weight = 1;
		break;
	}
	return(weight);
}

//*************************************************************************

int eval(int op1, int op2, char operate)
{
	// Given: two integers and an operator
	// Task: peform the given operation using the integers
	// Returns: returns the value when a specific operator
	//		    operates on two operands
	switch (operate)
	{
	case '*': return op2 * op1;
	case '/': return op2 / op1;
	case '+': return op2 + op1;
	case '-': return op2 - op1;
	default: return 0;
	}
}

//********************************************************************
void StackClass::Print(ofstream &outfile)
{
	// Given: The output file. 
	// Task:  Print the stack contents. 
	// Returns: The output file by reference. 

	NodeType *current;
	current = TopPtr;

	int i = 0;

	while (current != NULL)
	{
		if (i == 0)
		{
			outfile << setw(30) << current->currentChar;
		}
		else
		{
			outfile << setw(2) << current->currentChar;
		}
		current = current->next;
		i++;
	}
	outfile << endl;
}

int StackClass::evalPostfix(ofstream &outfile, string &postfix)
{
	// Given: The output file and postfix string. 
	// Task: Evaluate the postfix expression. 
	// Returns: The value, output file and postfix string by reference. 

	int i = 0; char ch;	int val; stack<int> s;
	string postfixDisplay = postfix;

	while (i < postfix.length())
	{
		ch = postfix[i];
		int spacing = 0;

		for (stack<int> dump = s; !dump.empty(); dump.pop())
		{
			if (spacing == 0)
			{
				outfile << setw(59) << dump.top();
			}
			else
			{
				outfile << setw(4) << dump.top();
			}
			spacing++;
		}
		outfile << endl;

		if (isdigit(ch))
		{
			s.push(ch - '0');
		}
		else
		{
			if (!s.empty())
			{
				int op1 = s.top();
				s.pop();
				int op2 = s.top();
				s.pop();
				val = eval(op1, op2, ch);
				s.push(val);
			}
		}

		outfile << postfixDisplay;
		for (int i = 0; i < postfixDisplay.length(); i++)
		{
			postfixDisplay[i] = postfixDisplay[i + 1];
		}
		i++;

	}
	return val;
}

//**********************************************************************
bool StackClass::IsFull()
{
	// Given: Nothing
	// Task: Test if the stack is full. 
	// Returns: A boolean denoting if it is full or not. 

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


// ***************************************************************
void StackClass::Push(NodeType DataIn)
{
	// Given: The Node to add to the stack. 
	// Task: Push the Node to the stack. 
	// Returns: The updated stack. 

	if (IsFull())
	{
		cout << " Add operation failed! " << endl;
		return;
	}

	NodeType *p;         
	p = new NodeType;     

	p->currentChar = DataIn.currentChar;

	p->next = TopPtr;
	TopPtr = p;

	return;
}
// ******************************************************************
void StackClass::Pop(NodeType &DataOut)
{
	// Given: The Node to pop off the stack. 
	// Task:  Pop the node off the stack. 
	// Returns: The node and updated stack by reference. 

	NodeType *p;

		// Save element in the first node
	DataOut.currentChar = TopPtr->currentChar;

		// Adjust Stack Top
	p = TopPtr;
	TopPtr = TopPtr->next;

	delete p;
	return;
}



//********************************** FUNCTION HEADER *****************************
void Header(ofstream &Outfile)
{
	// Recieves - the output file
	// Task - Prints the output preamble
	// Returns - Nothing

	Outfile << setw(30) << "AkinTunde Akinyemi";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2017";
	Outfile << setw(20) << "Assignment #4" << endl;
	Outfile << setw(35) << "----------------------------------------";
	Outfile << setw(35) << "----------------------------------------" << endl << endl;
	return;
}
//******************************* END OF FUNCTION HEADER *************************

//********************************** FUNCTION FOOTER *****************************
void Footer(ofstream &Outfile)
{
	// Recieves - the output file
	// Task - Prints the output salutation
	// Returns - Nothing

	Outfile << endl;
	Outfile << setw(35) << "----------------------------------------" << endl;
	Outfile << setw(35) << "|         END OF PROGRAM OUTPUT        |" << endl;
	Outfile << setw(35) << "----------------------------------------" << endl;
	return;
}
//******************************* END OF FUNCTION FOOTER ***********************