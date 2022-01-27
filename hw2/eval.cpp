#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool toPostfix(string original, string& postfix);
int determinePres(char ch);

string removeSpaces(string original);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
int evaluate(string infix, string& postfix, bool& result)
{
	infix = removeSpaces(infix); //removes spaces from the infix string
	if (!toPostfix(infix, postfix)) //converts the infix string to postfix and checks to make sure it's a valid expression
		return 1;

	stack<char> operand;
	int size = postfix.size();
	char ch;

	char operand2;
	char operand1;
	for (int i = 0; i < size; i++)
	{
		ch = postfix[i];
		if (ch == 'F' || ch == 'T') //push the operands onto a stack
			operand.push(ch); 
		else if (ch == '!') //unary operator simply reverses the values
		{
			operand1 = operand.top();
			operand.pop();
			if (operand1 == 'F')
				operand.push('T');
			else
				operand.push('F');
		}
		else
		{
			operand2 = operand.top(); //binary operators with with two operands
			operand.pop();
			operand1 = operand.top();
			operand.pop();
			if (ch == '&')
			{
				if (operand1 == 'T' && operand2 == 'T') //if they're both true it's true
					operand.push('T');
				else
					operand.push('F');
			}
			else if (ch == '^')
			{
				if (operand1 == operand2) //if they're the same it's false; otherwise true
					operand.push('F');
				else
					operand.push('T');
			}
			else
				return 1;
		}
	}

	if (operand.top() == 'T') //convert the chars to their bool values
		result = true;
	else if (operand.top() == 'F')
		result = false;

	return 0; //sucessfully run
}

bool toPostfix(string original, string& postfix) //converts an infix boolean expression to postfix notation
{  
	//the function should properly handle all invalid infix inputs
	postfix = "";
	stack<char> operators;
	int size = original.size();
	char ch;

	int numBinary = 0;
	int numOperand = 0;
	for (int i = 0; i < size; i++)
	{
		ch = original[i];
		switch (ch)
		{
		case 'T':
		case 'F':
			if (original[i + 1] == '(')
				return false;
			postfix += ch;
			numOperand++; //used to make sure operators are good
			break;
		case '(':
			operators.push(ch);
			break;
		case ')':
			if (i < (size - 1) && (original[i + 1] == 'T' || original[i + 1] == 'F'))
				return false;
			while (!operators.empty() && operators.top() != '(')
			{
				postfix += operators.top();
				operators.pop();
			}
			if (!operators.empty() && operators.top() == '(')
			{
				operators.pop();
				break;
			}				
			return false; //returns false if there's no matching '(' for the ')', which there should always be
		case '^':
		case '&':
			numBinary++;
			[[__fallthrough]] //even though this is present, g32 still gives me a warning that it "may fall through." I want it to fall through, man!
		case '!':
			while (!operators.empty() && operators.top() != '(' && (determinePres(ch) <= determinePres(operators.top())))
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.push(ch);
			break;
		default:
			return false; //called if there's invalid chars in the string
		}
	}
	if (numOperand != (numBinary + 1)) //this will always hold true for proper inputs. Catches a bunch of stuff!
		return false;
	while (!operators.empty())
	{
		if (operators.top() == '(') //catches exceptions in the form of unmatched open parentheses
			return false;
		postfix += operators.top();
		operators.pop();
	}
	return true;
}

int determinePres(char ch) //function used to determine operand heirarchy. Also used to catch errors in infix notation
{
	switch (ch)
	{
	case '^':
		return 0;
	case '&':
		return 1;
	case '!':
		return 2;
	default:
		return -1;
	}
}

string removeSpaces(string original) //removes all spaces from a given string
{
	string revised = "";
	int size = original.size();
	for (int i = 0; i < size; i++)
	{
		if (original[i] == ' ')
			continue;
		revised += original[i];
	}
	return revised;
}