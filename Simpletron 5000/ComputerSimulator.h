#pragma once

#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::showpos;
using std::noshowpos;
using std::setfill;

#define TOTAL_MEMORY 1000
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
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
	void load();
	void store();
	void add();
	void subtract();
	void divide();
	void multiply();
	void branch();
	void branchNeg();
	void branchZero();
	void halt();
};
