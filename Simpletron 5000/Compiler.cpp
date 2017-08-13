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
	return string();
}


// evaluates a postfix expression down to a single integer
int Compiler::evaluatePostfix(string & expression)
{
	return 0;
}