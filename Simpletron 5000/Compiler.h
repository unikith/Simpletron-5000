#pragma once


#include <string>

using std::string;


class Compiler
{
public:
	Compiler();
	~Compiler();

	// evaluates an infix expression and returns an integer
	int evalutateExpression(string & expression);

private:
	// This fucntion takes an infix expression in string format and 
	// turns it into a postfix expression in string format
	string infixToPostfix(string  & infixExpresssion);

	// evaluates a postfix expression down to a single integer
	int evaluatePostfix(string & expression);
};

