#pragma once

#include <stack>
#include <string>

using std::stack;
using std::string;

class Compiler
{
public:
	Compiler();
	~Compiler();

	// evaluates an infix expression and returns an integer
	int evalutateExpression(string & expression);

private:
	// takes an infix expression in string format and 
	// turns it into a postfix expression in string format
	string infixToPostfix(string  & infixExpresssion);

	// returns whether the input char is an operator or not
	// Note: operators it checks for are expression valid ones
	bool isOperator(char toCheck);

	// retruns true if op1 has a greater than or equal to presedence  of op2 
	// and false otherwise
	// PRECON: only use with valid operators
	bool precedenceExpression(char op1, char op2);



	// evaluates a postfix expression down to a single integer
	int evaluatePostfix(string & expression);
};

