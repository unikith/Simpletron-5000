#include "Compiler.h"



Compiler::Compiler()
{
}


Compiler::~Compiler()
{
}

// evaluates an infix expression and returns an integer
int Compiler::evalutateExpression(string & expression)
{
	string postfix = infixToPostfix(expression);
	return evaluatePostfix(postfix);
}


// This fucntion takes an infix expression in string format 
// and turns it into a postfix expression in string format
string Compiler::infixToPostfix(string  & infixExpresssion)
{
	string postfix = "";
	stack<char> theStack;

	theStack.push('(');
	infixExpresssion.append(")");
	int infixCounter = 0;
	char currentChar = '\0';

	while (!theStack.empty())
	{
		currentChar = infixExpresssion[infixCounter];
		if (isdigit(currentChar))
		{
			postfix.append(string(1, currentChar));
		}
		else if (currentChar == '(')
		{
			theStack.push(currentChar);
		}
		else if (isOperator(currentChar))
		{
			while (precedenceExpression(theStack.top(), currentChar))
			{
				postfix.append(string(1, theStack.top()));
				theStack.pop();
			}
			theStack.push(currentChar);
		}
		else if(currentChar == ')')
		{
			while (theStack.top() != '(')
			{
				postfix.append(string(1, theStack.top()));
				theStack.pop();
			}
			theStack.pop();
		}
		infixCounter++;
	}

	return postfix;
}

bool Compiler::isOperator(char toCheck)
{
	// utilizes fall through
	switch (toCheck)
	{ 
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '^':
		return true;
	default:
		return false;
	}
}

bool Compiler::precedenceExpression(char op1, char op2)
{
	int pres1 = 0, pres2 = 0;
	// useses fall through and gives an int value to the presedence
	// tiers
	switch (op1)
	{
	case '+':
	case '-':
		pres1 = 1;
		break;
	case '*':
	case '/':
	case '%':
		pres1 = 2;
		break;
	case ')':
	case '(':
		pres1 = 0;
		break;
	default:
		pres1 = 0;
		break;
	}

	switch (op2)
	{
	case '+':
	case '-':
		pres2 = 1;
		break;
	case '*':
	case '/':
	case '%':
		pres2 = 2;
		break;
	case ')':
	case '(':
		pres2 = 0;
		break;
	default:
		pres2 = 0;
		break;
	}
	if (pres1 >= pres2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// evaluates a postfix expression down to a single integer
int Compiler::evaluatePostfix(string & expression)
{
	return 0;
}