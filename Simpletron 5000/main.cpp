///////////////////////////////////////////////////////////////////
/// Programmer : James Nelson
/// Project : Build a complier for a restricted form of basic, 
///				for a simulated computer called simpletron.
/// Note : From "C++ How to Program" by Dietel and Deitel
///			problem from sec. 8 and 19
///////////////////////////////////////////////////////////////////

#include "Compiler.h"
#include "ComputerSimulator.h"

int main(void)
{

	ComputerSimulator Simpletron("ComputerInstructions.txt");
	Simpletron.runComputerWithFileInput();

	return 0;
}