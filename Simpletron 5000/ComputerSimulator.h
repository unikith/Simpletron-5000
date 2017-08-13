#pragma once

#include <iomanip>
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::setw;
using std::showpos;
using std::noshowpos;
using std::setfill;

#define TOTAL_MEMORY 100
#define MAX_WORD_SIZE 9999
#define MIN_WORD_SIZE -9999
#define EXIT_CODE -99999
#define MEMORY_DIGITS 3
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define MODULUS 34
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

class ComputerSimulator
{
public:
	ComputerSimulator(const char * fileName);
	~ComputerSimulator();

	void runComputerWithManualInput();

	void runComputerWithFileInput();

private:
	int mMemory[TOTAL_MEMORY] = { 0 }; // represents the memory of simpletron
	int mAccumulator; // accumulator register
	int mInstructionCounter; // tracks location in memory of current instruction
	int mOperationCode; // two digit code for operation
	int mOperand; // two digit code for operand location
	int mInstructionRegister; // register for instructions
	ifstream mLoadFile; // file that contains instructions
	
	void printPrompt();
	void getInstructions();
	bool loadInstructions();
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
	void modulus();
	void branch();
	void branchNeg();
	void branchZero();
	void halt();
};
