#include "ComputerSimulator.h"
/// Member  Functions
/// Public
//constructor and destructor

//brief: constructs the computer
//return: none
//precons: none
ComputerSimulator::ComputerSimulator() 
{
	this->mAccumulator = 0;
	this->mInstructionCounter = 0;
	this->mInstructionRegister = 0;
	this->mOperand = 0;
	this->mOperationCode = 0;
}

// brief: destroys the computer
// return: none
// precons: none
ComputerSimulator::~ComputerSimulator(){/*Empty*/}

// brief: loads instructions and runs them
// return: none
// precons: none
void ComputerSimulator::runComputer()
{
	this->getInstructions();
	this->runProgram();
}

/// Private

// brief: prints initial prompt for instruction input
// return: none
// precons: none
void ComputerSimulator::printPrompt()
{
	cout << "*** Welcome to Simpletron! ***" << endl;
	cout << "*** Please enter your program one instruction ***" << endl;
	cout << "*** (or data word) at a time. I will type the ***" << endl;
	cout << "*** location number and a question mark (?). ***" << endl;
	cout << "*** You then type the word for that location. ***" << endl;
	cout << "*** Type the sentinel -99999 to stop entering ***" << endl;
	cout << "*** your program. ***" << endl;
}

// brief: gets a list of instructions and inputs them into memory
// return: none
// precons: none
void ComputerSimulator::getInstructions()
{
	this->printPrompt();
	int temp = 0, counter = 0;
	do
	{
		if (counter < 10) // keeps memory num as two digit
			cout << 0;
		cout << counter << " ? "; // prompt for input
		cin >> temp;
		if (temp < 10000 && temp > -10000) // only inserts into memory if less than 5 digits
		{
			this->mMemory[counter] = temp;
			++counter;
		}
		else if (temp != -99999)
		{
			cout << "*** Invalid Input ***" << endl;
		}
	} while (temp != -99999 && counter < TOTAL_MEMORY); // sentinel/counter
	cout << "*** Program Loading Completed ***" << endl;
}

// brief: dumps registers and memory to screen
// return: none
// precons: none
void ComputerSimulator::regiserAndMemoryDump()
{
	cout << "REGISTERS:" << endl;
	cout << "Accumulator: " << setw(5) << setfill('0') << std::internal << std::showpos << this->mAccumulator  << endl;
	cout << "InstructionCounter: " << setw(2) << noshowpos << this->mInstructionCounter << endl;
	cout << "InstructionRegister: "  << setw(5) << showpos << this->mInstructionRegister << endl;
	cout << "OperationCode: " << setw(2) << noshowpos << this->mOperationCode << endl;
	cout << "Operand: " << setw(2) << noshowpos << this->mOperand << endl;
	
	cout << endl << "MEMORY:" << endl;
	cout << "   " << setfill(' ');
	for (int i = 0; i < 10; i++)
	{
		cout << setw(5) << i << " ";
	}
	for (int i = 0; i < TOTAL_MEMORY; i++)
	{
		if (i % 10 == 0)
		{
			cout << endl << setw(3) << setfill(' ') << noshowpos << (i / 10) * 10 << " ";
		}
		cout << setw(5) << setfill('0') << showpos << this->mMemory[i] << ' ';
	}
	cout << endl;

}

// brief: runs through the current instruction
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::runInstructions()
{
	if (mOperand < TOTAL_MEMORY)
	{
		switch (this->mOperationCode)
		{
		case READ:
			read();
			break;
		case WRITE:
			write();
			break;
		case LOAD:
			load();
			break;
		case STORE:
			store();
			break;
		case ADD:
			add();
			break;
		case SUBTRACT:
			subtract();
			break;
		case DIVIDE:
			divide();
			break;
		case MULTIPLY:
			multiply();
			break;
		case MODULUS:
			modulus();
			break;
		case BRANCH:
			branch();
			break;
		case BRANCHNEG:
			branchNeg();
			break;
		case BRANCHZERO:
			branchZero();
			break;
		case HALT:
			halt();
			break;
		default: // breaks out and calls a memory dump with an invalid instruction
			cout << "*** Invalid Operation Code ***" << endl;
			cout << "*** Simpletron Execution Abnormally Terminated ***" << endl;
			halt();
			break;
		}
	} //if(mOperand < TOTAL_MEMORY)

	else
	{
		cout << "*** Invalid Memory Location ***" << endl;
		cout << "*** Simpletron Execution Abnormally Terminated ***" << endl;
		halt();
	}
}

// brief: loads current instruction splits current instruction and 
//			saves parts into proper register
// return: none
// precons: Current instruction is valid
void ComputerSimulator::splitInstructionWord()
{
	this->mInstructionRegister = this->mMemory[this->mInstructionCounter];
	this->mOperationCode = mInstructionRegister / 100;
	this->mOperand = mInstructionRegister % 100;
}

// brief: runs program from memory
// return: none
// precons: Instructions have been loaded into memory
void ComputerSimulator::runProgram() 
{
	cout << "*** Program Execution Begins ***" << endl;
	while (this->mInstructionCounter < TOTAL_MEMORY)
	{
		splitInstructionWord();
		++this->mInstructionCounter;
		runInstructions();
	}
}

// functions for SML operations
// brief: read a word from keyboard into a specific location in memory
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::read()
{
	cin >> mMemory[this->mOperand];
}

// brief: Write a word from a specific location in memory to the screen
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::write()
{
	cout << mMemory[this->mOperand] << endl;
}

// brief: Load a word from a specific location in memory into the accumulator
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::load()
{
	mAccumulator = mMemory[this->mOperand];
}

// brief: Store a word from the accumulator into a specific location in memory.
// return: none
// precons:current instruction has been divided into operand, and code
void ComputerSimulator::store()
{
	mMemory[this->mOperand] = mAccumulator;
}

// brief: Add a word from a specific location in memory to the
//			word in the accumulator(leave result in accumulator).
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::add()
{
	mAccumulator += mMemory[this->mOperand];
	if (mAccumulator > 9999 || mAccumulator < -9999)
	{
		mAccumulator = 0;
		cout << "*** Accumulator Overflow ***" << endl;
		cout << "*** Simpletron Execution Abnormally Terminated ***" << endl;
		halt();
	}
}

// brief: Subtract a word from a specific location in memory from
//			the word in the accumulator(leave result in accumulator).
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::subtract()
{
	mAccumulator -= mMemory[this->mOperand];
}

// brief: Divide a word from a specific location in memory into the
//			word in the accumulator(leave result in accumulator).
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::divide()
{
	if (mMemory[this->mOperand] == 0)
	{
		cout << "*** Attempt to Divide by Zero ***" << endl;
		cout << "*** Simpletron Execution Abnormally Terminated ***" << endl;
		halt();
	}
	else
	{
		mAccumulator /= mMemory[this->mOperand];
	}
}

// brief: Multiply a word from a specific location in memory by the
//			word in the accumulator(leave result in accumulator).
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::multiply()
{
	mAccumulator *= mMemory[this->mOperand];
	if (mAccumulator > 9999 || mAccumulator < -9999)
	{
		mAccumulator = 0;
		cout << "*** Accumulator Overflow ***" << endl;
		cout << "*** Simpletron Execution Abnormally Terminated ***" << endl;
		halt();
	}
}

// brief: Modulus a word from a specific location in memory into the
//			word in the accumulator(leave result in accumulator).
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::modulus()
{
	if (mMemory[this->mOperand] == 0)
	{
		cout << "*** Attempt to Modulus by Zero ***" << endl;
		cout << "*** Simpletron Execution Abnormally Terminated ***" << endl;
		halt();
	}
	else
	{
		mAccumulator %= mMemory[this->mOperand];
	}
}

// brief: Branch to a specific location in memory.
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::branch()
{
	this->mInstructionCounter = this->mOperand;
}

// brief: Branch to a specific location in memory if the accumulator
//			is negative.
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::branchNeg()
{
	if (this->mAccumulator < 0)
		this->mInstructionCounter = this->mOperand;
}

// brief: Branch to a specific location in memory if the accumulator
//			is zero.
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::branchZero()
{
	if (this->mAccumulator == 0)
		this->mInstructionCounter = this->mOperand;
}

// brief: halts program and calls a register and memory dump
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::halt()
{
	this->regiserAndMemoryDump();
	this->mInstructionCounter = TOTAL_MEMORY;
}