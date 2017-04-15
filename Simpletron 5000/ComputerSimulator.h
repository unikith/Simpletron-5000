#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::showpos;
using std::noshowpos;
using std::setfill;
using std::internal;

#define TOTAL_MEMORY 1000
#define MAX_SIZE 99999
#define EXIT_CODE -999999
#define READ 10
#define WRITE 11
#define NEWLINE 12
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define MODULUS 34
#define EXPONENTIATION 35
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

class ComputerSimulator
{
public:
	ComputerSimulator();
	~ComputerSimulator();

	void runComputer();

private:
	int mMemory[TOTAL_MEMORY] = { 0 }; // represents the memory of simpletron
	int mAccumulator; // accumulator register
	int mInstructionCounter; // tracks location in memory of current instruction
	int mOperationCode; // two digit code for operation
	int mOperand; // two digit code for operand location
	int mInstructionRegister; // register for instructions
	
	void printPrompt();
	void getInstructions();
	void regiserAndMemoryDump();
	void runInstructions();
	void splitInstructionWord();
	void runProgram();

	// functions for SML operations
	void read();
	void write();
	void newLine();
	void load();
	void store();
	void add();
	void subtract();
	void divide();
	void multiply();
	void modulus();
	void exponentiation();
	void branch();
	void branchNeg();
	void branchZero();
	void halt();
};
