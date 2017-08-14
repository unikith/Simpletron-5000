#include "ComputerSimulator.h"
/// Member  Functions
/// Public
//constructor and destructor

//brief: constructs the computer
//return: none
//precons: none
ComputerSimulator::ComputerSimulator(const char * fileName) : mLoadFile(fileName)
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
ComputerSimulator::~ComputerSimulator()
{
	this->mLoadFile.close();
}



// brief: loads instructions and runs them
// return: none
// precons: none
void ComputerSimulator::runComputerWithManualInput()
{
	this->getInstructions();
	this->runProgram();
}

void ComputerSimulator::runComputerWithFileInput()
{
	if (this->loadInstructions())
	{
		this->runProgram();
	}
	else
	{
		cout << "*** Error Loading Program***" << endl;
	}
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
	cout << "*** Type the sentinel " << EXIT_CODE << " to stop entering ***" << endl;
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
		//if (counter < 10) // keeps memory num as two digit
		//	cout << 0;
		cout.width(MEMORY_DIGITS - 1); // keeps memory num as two digit
		cout.fill('0');

		cout << counter << " ? "; // prompt for input
		cin >> temp;
		if (temp <= MAX_WORD_SIZE && temp >= MIN_WORD_SIZE) // only inserts into memory if less than 5 digits
		{
			this->mMemory[counter] = temp;
			++counter;
		}
		else if (temp != EXIT_CODE)
		{
			cout << "*** Invalid Input ***" << endl;
		}
	} while (temp != EXIT_CODE && counter < TOTAL_MEMORY); // sentinel/counter
	cout << "*** Program loading completed ***" << endl;
}

// loads instructions from the load file associated with the computer at instantiation
//Format must be in form 00 +0000, where 0's can be any digit
bool ComputerSimulator::loadInstructions()
{
	bool success = true;
	cout << "*** Loading Instructions ***" << endl;
	if (mLoadFile.is_open())
	{
		char buffer[9];
		int counter = 0, temp = 0;
		while (!mLoadFile.eof()) 
		{
			mLoadFile.getline(buffer, 9, '\n');

			temp = atoi(buffer + 3); // ignores line numbers

			this->mMemory[counter] = temp;
			++counter;
		}
	}
	else
	{
		cout << "*** File Failed To Load Properly ***" << endl;
		success = false;
	}
	return success;
}

// brief: dumps registers and memory to screen
// return: none
// precons: none
void ComputerSimulator::regiserAndMemoryDump()
{
	cout << "REGISTERS:" << endl;
	cout << "accumulator: " << setw(MEMORY_DIGITS + 2) << setfill('0') << std::internal << std::showpos << this->mAccumulator << endl;
	// istructionCounter is incremented immediatly so this fixes it in the dump
	cout << "instructionCounter: " << setw(MEMORY_DIGITS - 1) << noshowpos << this->mInstructionCounter - 1 << endl;
	cout << "instructionRegister: "  << setw(MEMORY_DIGITS + 2) << showpos << this->mInstructionRegister << endl;
	cout << "operationCode: " << setw(2) << noshowpos << this->mOperationCode << endl;
	cout << "operand: " << setw(MEMORY_DIGITS - 1) << noshowpos << this->mOperand << endl;
	
	cout << endl << "Memory:" << endl;
	for (int i = 0; i < MEMORY_DIGITS; ++i)
	{
		cout << " ";
	}
	cout /*<< "    "*/ << setfill(' ');
	for (int i = 0; i < 10; i++)
	{
		cout << setw(MEMORY_DIGITS + 2) << i << " ";
	}
	for (int i = 0; i < TOTAL_MEMORY; i++)
	{
		if (i % 10 == 0)
		{
			cout << endl << setw(MEMORY_DIGITS - 1) << setfill('0') << noshowpos << /*(i / 10) * 10*/i << " ";
		}
		cout << setw(MEMORY_DIGITS + 2) << setfill('0') << showpos << this->mMemory[i] << ' ';
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
			cout << "*** Simpletron execution abnormally terminated ***" << endl;
			halt();
			break;
		} // end switch
	} //if(mOperand < TOTAL_MEMORY)

	else
	{
		cout << "*** Invalid Memory Location ***" << endl;
		cout << "*** Simpletron execution abnormally terminated ***" << endl;
		halt();
	} // end else
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
	cout << "*** Program execution begins ***" << endl;
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
	if (mAccumulator > MAX_WORD_SIZE || mAccumulator < MIN_WORD_SIZE)
	{
		mAccumulator = 0;
		cout << "*** Accumulator Overflow ***" << endl;
		cout << "*** Simpletron execution abnormally terminated ***" << endl;
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
	if (mAccumulator > MAX_WORD_SIZE || mAccumulator < MIN_WORD_SIZE)
	{
		cout << "*** Accumulator Overflow ***" << endl;
		cout << "*** Simpletron execution abnormally terminated ***" << endl;
		halt();
	}
}

// brief: Divide a word from a specific location in memory into the
//			word in the accumulator(leave result in accumulator).
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::divide()
{
	if (mMemory[this->mOperand] == 0)
	{
		cout << "*** Attempt to divide by zero ***" << endl;
		cout << "*** Simpletron execution abnormally terminated ***" << endl;
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
	if (mAccumulator > MAX_WORD_SIZE || mAccumulator < MIN_WORD_SIZE)
	{
		mAccumulator = 0;
		cout << "*** Accumulator Overflow ***" << endl;
		cout << "*** Simpletron execution abnormally terminated ***" << endl;
		halt();
	}
}

// brief: Modulus a word from a specific location in memory by the
//			word in the accumulator(leave result in accumulator).
// return: none
// precons: current instruction has been divided into operand, and code
void ComputerSimulator::modulus()
{
	if (mMemory[this->mOperand] == 0)
	{
		cout << "*** Attempt to divide by zero ***" << endl;
		cout << "*** Simpletron execution abnormally terminated ***" << endl;
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